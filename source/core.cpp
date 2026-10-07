#include "ScriptMemory.hpp"
#include <new>
#include "core.h"
#include "ScriptSave.hpp"
#include "core_asm.h"
#include "core_menu.h"
#include "armhook.h"
#include "utils.h"
#include "strutils.h"
#include "text.h"
#include "touch.h"
#include "ui.h"
#include "libres.h"
#include "pattern.h"
#include "plugins.h"
#include "mutex.h"
#include "memutils.h"
#include "unaligned.h"

#include "psplang.h"

namespace core
{
	e_game game;
	e_game GetGame() { return game; }

	enum e_game_version
	{
		VER_NONE,
		VER_GTA3_1_4,
		VER_GTAVC_1_03,
		VER_GTASA_1_00,
		VER_GTASA_1_01,
		VER_GTASA_1_02,
		VER_GTASA_1_03,
		VER_GTASA_1_05,
		VER_GTASA_1_06,
		VER_GTASA_1_05_GER,
		VER_GTASA_1_07,
		VER_GTA3_1_6,
		VER_GTAVC_1_06,
		VER_GTASA_1_08,
		VER_GTALCS_2_2,
		VER_GTA3_1_8_OR_HIGHER,
		VER_GTAVC_1_09_OR_HIGHER,
		VER_GTASA_2_00_OR_HIGHER,
		VER_GTALCS_2_4_OR_HIGHER,
		VER_GTALCS_PSP_1_05_OR_HIGHER,
		VER_GTAVCS_PSP_1_02_OR_HIGHER
	};

	const char *str_game_version[] = {
		"VER_NONE",
		"VER_GTA3_1_4",
		"VER_GTAVC_1_03",
		"VER_GTASA_1_00",
		"VER_GTASA_1_01",
		"VER_GTASA_1_02",
		"VER_GTASA_1_03",
		"VER_GTASA_1_05",
		"VER_GTASA_1_06",
		"VER_GTASA_1_05_GER",
		"VER_GTASA_1_07",
		"VER_GTA3_1_6",
		"VER_GTAVC_1_06",
		"VER_GTASA_1_08",
		"VER_GTALCS_2_2",
		"VER_GTA3_1_8_OR_HIGHER",
		"VER_GTAVC_1_09_OR_HIGHER",
		"VER_GTASA_2_00_OR_HIGHER",
		"VER_GTALCS_2_4_OR_HIGHER",
		"VER_GTALCS_PSP_1_05_OR_HIGHER",
		"VER_GTAVCS_PSP_1_02_OR_HIGHER"
	};

	int game_ver = VER_NONE;
	int GetGameVersion() { return game_ver; }

	std::string package_name;
	const char *GetPackageName() { return package_name.c_str(); }

	std::string package_version_name;
	const char *GetPackageVersionStr() { return package_version_name.c_str(); }

	int	package_version_code;
	int GetPackageVersionCode() { return package_version_code; }

	void preload_scripts();
	void launch_scripts();
	void save_scripts(uint32_t a = 0, uint32_t b = 0); // params not used for SA
	void process_opcodes(ptr handle);

	struct t_script
	{
		std::string name;
		int32_t invokable_id;
		uint8_t *handle; // returned by CTheScripts::StartNewScript
		uint8_t *code; // script code
		uint32_t code_size;
		uint32_t offset; // start ip for script vm, based on ScriptSpace overrun
		bool wait_passed;
		bool invalid = false;
		uint32_t context[32]{};

		t_script() : handle(NULL), code(NULL), offset(0) {}
	};

	// The VM and the save filter share a bounded set of custom scripts.
	struct ScriptList {
		t_script* entries[128]{};
		uint32_t count=0;
		uint32_t size() const { return count; }
		void clear() { count=0; }
		t_script*& operator[](uint32_t i) { return entries[i]; }
		void push_back(t_script* script) { entries[count++]=script; }
	} scripts;

	t_script *get_script_using_handle(uint8_t *handle)
	{
		for (int32_t i = 0; i < scripts.size(); i++)
			if (scripts[i]->handle == handle)
				return scripts[i];
		return NULL;
	}

	int32_t image_base; // image base

	struct t_mutex_var
	{
		uint32_t id, value;
	};

	std::vector<t_mutex_var> mutex_vars;

	// The offsets in the CRunningScript structure differ per game and aren't all naturally
	// aligned, so never dereference them directly - see unaligned.h.
	template <typename T> inline T getfield(ptr structure, uint32_t offset)
	{
		return read_unaligned<T>(structure + offset);
	}

	template <typename T> inline void setfield(ptr structure, uint32_t offset, T val)
	{
		write_unaligned<T>(structure + offset, val);
	}

	template <typename T> inline T select(T val_3, T val_vc, T val_sa, T val_lcs, T val_vcs)
	{
		switch (game)
		{
		case GTA3: return val_3;
		case GTAVC: return val_vc;
		case GTASA: return val_sa;
		case GTALCS: return val_lcs;
		case GTAVCS: return val_vcs;
		}
	}

	// @windowSize
	typedef struct { uint32_t w, h; } _windowSize;
	_windowSize *windowSize;

	// @windowSize LCS
	typedef struct { uint32_t h, w; } _windowSizeLCS;
	_windowSizeLCS *windowSizeLCS;

	// @CTimer::m_snTimeInMilliseconds
	uint32_t *CTimer__m_snTimeInMilliseconds;

	// @ScriptParams
	uint32_t *ScriptParams;
	uint32_t *GetScriptParams() { return ScriptParams; }

	// @CTheScripts::ScriptSpace, @CTheScripts::pActiveScripts
	ptr CTheScripts__ScriptSpace, CTheScripts__pActiveScripts;
	ptr *CTheScripts__ScriptSpace_LCS;

	// @CTheScripts::StartNewScript
	typedef ptr (*fn_CTheScripts__StartNewScript)(uint32_t);
	fn_CTheScripts__StartNewScript CTheScripts__StartNewScript;

	// CTheScripts::StartNewScript takes the head of the idle-script list
	// without checking it: with every native thread busy it dereferences NULL.
	// The list address differs per build, so it is decoded from the function's
	// own argument for RemoveScriptFromList(script, &pIdleScripts): LCS sets it
	// with "lui a1 / addiu a1, a1", VCS with "addiu a1, gp". It must sit near
	// pActiveScripts (within 0x200 bytes); otherwise no script is started.
	uint32_t *CTheScripts__pIdleScripts;
	void find_idle_scripts()
	{
		CTheScripts__pIdleScripts = NULL;
		const uint32_t *code = cast<const uint32_t *>(CTheScripts__StartNewScript);
		if (!code || !CTheScripts__pActiveScripts) return;
		int32_t high = -1;
		uint32_t address = 0;
		for (int i = 0; i < 12 && !address; i++)
		{
			const uint32_t word = code[i];
			if ((word >> 26) == 3 || (word >> 26) == 2) break; // first call: argument is set
			if ((word & 0xFFFF0000u) == 0x3C050000u) high = int32_t(word & 0xFFFF); // lui a1
			else if ((word & 0xFFFF0000u) == 0x24A50000u && high >= 0) // addiu a1, a1
				address = (uint32_t(high) << 16) + uint32_t(int32_t(int16_t(word)));
			else if ((word & 0xFFFF0000u) == 0x27850000u) // addiu a1, gp
				address = libres::getGpValue() + uint32_t(int32_t(int16_t(word)));
		}
		const uint32_t active = cast<uint32_t>(CTheScripts__pActiveScripts);
		if (address && !(address & 3) && (address > active ? address - active : active - address) <= 0x200)
			CTheScripts__pIdleScripts = cast<uint32_t *>(address);
		utils::log("CTheScripts__pIdleScripts: 0x%08X", CTheScripts__pIdleScripts);
	}
	ptr start_new_script(uint32_t offset)
	{
		if (!CTheScripts__pIdleScripts || !*CTheScripts__pIdleScripts)
		{
			utils::log("no free script thread for ip 0x%08X", offset);
			return NULL;
		}
		return CTheScripts__StartNewScript(offset);
	}

	// @CRunningScript::GetPointerToScriptVariable SA
	typedef ptr (*fn_SA_CRunningScript__GetPointerToScriptVariable)(ptr thiz, uint8_t);
	fn_SA_CRunningScript__GetPointerToScriptVariable SA_CRunningScript__GetPointerToScriptVariable;

	// @CRunningScript::GetPointerToScriptVariable VC3LCS
	typedef ptr (*fn_VC3LCS_CRunningScript__GetPointerToScriptVariable)(ptr thiz, uint32_t *ip, uint8_t);
	fn_VC3LCS_CRunningScript__GetPointerToScriptVariable VC3LCS_CRunningScript__GetPointerToScriptVariable;

	ptr CRunningScript__GetPointerToScriptVariable(ptr thiz, uint8_t param)
	{
		switch (game)
		{
		case GTA3:
		case GTAVC:
			return VC3LCS_CRunningScript__GetPointerToScriptVariable(thiz, cast<uint32_t *>(thiz + 0x10), param);
		case GTASA:
			return SA_CRunningScript__GetPointerToScriptVariable(thiz, param);
		case GTALCS:
			return VC3LCS_CRunningScript__GetPointerToScriptVariable(thiz, cast<uint32_t *>(thiz + 0x18), param);
		case GTAVCS:
			return VC3LCS_CRunningScript__GetPointerToScriptVariable(thiz, cast<uint32_t *>(thiz + 0x10), param);

		}
	}

	// @CRunningScript::CollectParameters SA
	typedef void (*fn_SA_CRunningScript__CollectParameters)(ptr thiz, uint32_t count);
	fn_SA_CRunningScript__CollectParameters SA_CRunningScript__CollectParameters;

	// @CRunningScript::CollectParameters VC3
	typedef void (*fn_VC3_CRunningScript__CollectParameters)(ptr thiz, uint32_t *ip, uint32_t count);
	fn_VC3_CRunningScript__CollectParameters VC3_CRunningScript__CollectParameters;

	// @CRunningScript::CollectParameters LCS
	typedef int (*fn_LCS_CRunningScript__CollectParameters)(ptr thiz, uint32_t *ip, uint32_t count, uint32_t *p);
	fn_LCS_CRunningScript__CollectParameters LCS_CRunningScript__CollectParameters;

	void CRunningScript__CollectParameters(ptr thiz, uint32_t count)
	{
		switch (game)
		{
		case GTA3:
		case GTAVC:
			VC3_CRunningScript__CollectParameters(thiz, cast<uint32_t *>(thiz + 0x10), count);
			break;
		case GTASA:
			SA_CRunningScript__CollectParameters(thiz, count);
			break;
		case GTALCS:
			LCS_CRunningScript__CollectParameters(thiz, cast<uint32_t *>(thiz + 0x18), count, ScriptParams);
			break;
		case GTAVCS:
			LCS_CRunningScript__CollectParameters(thiz, cast<uint32_t *>(thiz + 0x10), count, ScriptParams);
			break;
		}
	}

	// @CRunningScript::UpdateCompareFlag
	typedef void (*fn_CRunningScript__UpdateCompareFlag)(ptr thiz, bool flag);
	fn_CRunningScript__UpdateCompareFlag CRunningScript__UpdateCompareFlag;

	// inidcates when @CTheScripts::Load executing
	bool bCTheScripts__Load = false;

	// @CTheScripts::Load SA
	// starts custom scripts after game loads saved scripts, custom scripts start in CTheScripts::Init must be disabled
	typedef void (*fn_SA_CTheScripts__Load)();
	fn_SA_CTheScripts__Load _SA_CTheScripts__Load, SA_CTheScripts__Load_;
	void SA_CTheScripts__Load()
	{
		utils::log("CTheScripts::Load()");
		bCTheScripts__Load = true;
		SA_CTheScripts__Load_();
		bCTheScripts__Load = false;
		preload_scripts();
		launch_scripts();
	}

	// @CTheScripts::Load VC3LCS
	typedef void (*fn_VC3_CTheScripts__Load)(uint32_t, uint32_t);
	fn_VC3_CTheScripts__Load _VC3_CTheScripts__Load, VC3_CTheScripts__Load_;
	void VC3_CTheScripts__Load(uint32_t a, uint32_t b)
	{
		utils::log("CTheScripts::Load()");
		bCTheScripts__Load = true;
		VC3_CTheScripts__Load_(a, b);
		bCTheScripts__Load = false;
		preload_scripts();
		launch_scripts();
	}

	// @CTheScripts::Init
	// starts custom scripts after game loads scm
	typedef void (*fn_CTheScripts__Init)();
	fn_CTheScripts__Init _CTheScripts__Init, CTheScripts__Init_;
	void CTheScripts__Init()
	{
		utils::log("CTheScripts::Init()");
		CTheScripts__Init_();
		if (!bCTheScripts__Load)
		{
			preload_scripts();
			launch_scripts();
		}
	}

	// @CTheScripts::Init LCS
	typedef int32_t (*fn_LCS_CTheScripts__Init)(bool b);
	fn_LCS_CTheScripts__Init _LCS_CTheScripts__Init, LCS_CTheScripts__Init_;
	int32_t LCS_CTheScripts__Init(bool b)
	{
		/*typedef int32_t (*fn_LCS_CFileMgr__LoadFile)(const char *fname, uint8_t *buf, int32_t size, const char *mode);
		fn_LCS_CFileMgr__LoadFile LoadFile = getsym<fn_LCS_CFileMgr__LoadFile>("_ZN8CFileMgr8LoadFileEPKcPhiS1_");
		uint8_t *buf = (uint8_t *)malloc(1024 * 1024 * 4);
		int32_t size = LoadFile("data/main.scm", buf, 1024 * 1024 * 4, "rb");
		if (size > 0)
		{
			FILE *f = fopen("/sdcard/main.scm", "wb");
			fwrite(buf, 1, size, f);
			fclose(f);
		}*/

		utils::log("CTheScripts::Init()");
		int32_t res = LCS_CTheScripts__Init_(b);
		CTheScripts__ScriptSpace = *CTheScripts__ScriptSpace_LCS; // dynamic allocation
		preload_scripts();
		launch_scripts();
		return res;
	}

	// @CTheScripts::Save SA
	// removes custom scripts from active scripts list, calls save and adds custom scripts to active list
	typedef void (*fn_SA_CTheScripts__Save)();
	fn_SA_CTheScripts__Save _SA_CTheScripts__Save, SA_CTheScripts__Save_;
	void SA_CTheScripts__Save()
	{
		utils::log("CTheScripts::Save()");
		save_scripts();
	}

	// @CTheScripts::Save VC3LCS
	typedef void (*fn_VC3LCS_CTheScripts__Save)(uint32_t, uint32_t);
	fn_VC3LCS_CTheScripts__Save _VC3LCS_CTheScripts__Save, VC3LCS_CTheScripts__Save_;
	void VC3LCS_CTheScripts__Save(uint32_t a, uint32_t b)
	{
		utils::log("CTheScripts::Save()");
		save_scripts(a, b);
	}

	// @CRunningScript::ProcessOneCommand
	// executes one opcode, returns true when thread switch should occure
	typedef bool (*fn_CRunningScript__ProcessOneCommand)(ptr thiz);
	fn_CRunningScript__ProcessOneCommand _CRunningScript__ProcessOneCommand, CRunningScript__ProcessOneCommand_;
	bool CRunningScript__ProcessOneCommand(ptr thiz)
	{
		process_opcodes(thiz);
		return true;
	}

	// @CText::Get
	// gets gxt entry by name
	ptr CTextHandle = NULL;
	typedef uint16_t *(*fn_CText__Get)(ptr thiz, LPCSTR name);
	fn_CText__Get _CText__Get, CText__Get_;
	uint16_t *CText__Get(ptr thiz, LPCSTR name)
	{		
		//utils::log("CText::Get(): %s", name);
		CTextHandle = thiz;

		if (CTextHandle && !psplang::is_init())
			psplang::init();

		uint16_t *e = name ? text::get_gxt_entry(name) : NULL;
		return e ? e : CText__Get_(thiz, name);
	}

	uint16_t *GetGxtEntry(LPCSTR name, bool useCustom)
	{
		if (!CTextHandle || !name || !name[0] || (game == GTA3 && strlen(name) > 7))
			return NULL;
		uint16_t *e = useCustom ? text::get_gxt_entry(name) : NULL;
		return e ? e : CText__Get_(CTextHandle, name);
	}


	// sceCtrlReadBufferPositive
	int LCSVCS_sceCtrlReadBufferPositive(SceCtrlData *pad_data, int count)
	{
		int res = sceCtrlReadBufferPositive(pad_data, count);
		if (res>0 && pad_data) { touch::psp_input_event(pad_data); ui::handle_psp_controls(); }
		return res;
	}


	// legacy external storage path
	std::string get_storage_dir()
	{		
		char dir[64];
		sprintf(dir, "ms0:/PSP/PLUGINS/cleo/%s/", select("", "", "", "lcs", "vcs"));
		return dir;
	}



	uint32_t VC3LCS_CRunningScript__ProcessOneCommand_call_1,
			 VC3LCS_CRunningScript__ProcessOneCommand_call_2,
			 SA_CRunningScript__ProcessOneCommand_call,
			 SA_CRunningScript__ProcessOneCommand_call_end,
			 VC3SA_NvEventQueueActivity__init_ptr;

	bool init_pattern()
	{
		#define PATTERN_NOT_FOUND {	utils::log("required pattern %d not found!", __LINE__); return false; }
		#define FIND_PATTERN(...) if (!__FindPatternAddress(addr, __VA_ARGS__)) PATTERN_NOT_FOUND;
		
		uint32_t addr;

		// CRunningScript__ProcessOneCommand
		switch (game)
		{
		case GTALCS:
			FIND_PATTERN("2B 20 A4 00 07 00 80 14 00 00 00 00");
			VC3LCS_CRunningScript__ProcessOneCommand_call_1 = addr + 12;
			
			break;
		case GTAVCS:
			FIND_PATTERN("2B 20 A4 00 07 00 80 14 00 00 00 00 ?? ?? ?? ?? 25 20 00 02");
			VC3LCS_CRunningScript__ProcessOneCommand_call_1 = addr + 12;
			break;
		}


		return true;
	}

	void init_fixes()
	{
	}

	bool init_code()
	{
		if (!init_pattern())
			return false;

		if (game == GTALCS)
		{
			uint32_t addr;

			#define READ_ADDR(addr1, addr2) ((static_cast<uint32_t>(*cast<uint16_t *>(addr1)) << 16) | *cast<uint16_t *>(addr2))
			#define READ_ADDR_INDIRECT(addr1, addr2) (READ_ADDR(addr1, addr2) - 0x10000)

			// ScriptParams
			FIND_PATTERN("00 00 00 00 ?? ?? 04 3C ?? ?? 84 8C 08 00 81 04");
			ScriptParams = cast<uint32_t *>(READ_ADDR_INDIRECT(addr + 4, addr + 8));

			// _ZN6CTimer22m_snTimeInMillisecondsE
			FIND_PATTERN("?? ?? 05 3C ?? ?? A5 8C 2B 20 A4 00 07 00 80 14");
			CTimer__m_snTimeInMilliseconds = cast<uint32_t *>(READ_ADDR_INDIRECT(addr, addr + 4));

			// _ZN11CTheScripts11ScriptSpaceE
			FIND_PATTERN("E0 FF BD 27 10 00 BF AF ?? ?? 05 3C ?? ?? A5 8C 18 00 86 8C");
			CTheScripts__ScriptSpace_LCS = cast<ptr*>(READ_ADDR_INDIRECT(addr + 8, addr + 12));

			// _ZN11CTheScripts14pActiveScriptsE
			FIND_PATTERN("25 38 00 01 ?? ?? 08 3C ?? ?? 09 8D 00 00 16 34");
			CTheScripts__pActiveScripts = cast<ptr>(READ_ADDR_INDIRECT(addr + 4, addr + 8));

			// _ZN11CTheScripts14StartNewScriptEi
			FIND_PATTERN("E0 FF BD 27 ?? ?? 05 3C 14 00 B1 AF ?? ?? B1 8C 10 00 B0 AF");
			CTheScripts__StartNewScript = cast<fn_CTheScripts__StartNewScript>(addr);

			// _ZN14CRunningScript17ProcessOneCommandEv
			FIND_PATTERN("E0 FF BD 27 10 00 BF AF ?? ?? 05 3C ?? ?? A5 8C 18 00 86 8C");
			_CRunningScript__ProcessOneCommand = cast<fn_CRunningScript__ProcessOneCommand>(addr); //

			// _ZN5CText3GetEPKc
			// WidescreenFix may already have replaced the first two instructions.
			FIND_PATTERN("18 00 B1 AF 1C 00 B2 AF 10 00 B2 27 25 80 A0 00 25 88 80 00 10 00 A0 A3");
			_CText__Get = cast<fn_CText__Get>(addr - 8);

			// _ZN14CRunningScript26GetPointerToScriptVariableEPjh
			FIND_PATTERN("E0 FF BD 27 10 00 BF AF ?? ?? ?? ?? FF 00 C6 30");
			VC3LCS_CRunningScript__GetPointerToScriptVariable = cast<fn_VC3LCS_CRunningScript__GetPointerToScriptVariable>(addr);

			// _ZN11CTheScripts14SaveAllScriptsEPhPj
			FIND_PATTERN("00 00 07 34 ?? ?? 06 3C ?? ?? C9 8C 21 40 27 01");
			_VC3LCS_CTheScripts__Save = cast<fn_VC3LCS_CTheScripts__Save>(addr - 0x2C);			

			// _ZN14CRunningScript17CollectParametersEPjiPi
			FIND_PATTERN("1C 00 E4 48 1D 00 E5 48 00 00 A5 8C");
			LCS_CRunningScript__CollectParameters = cast<fn_LCS_CRunningScript__CollectParameters>(addr);

			// _ZN11CTheScripts4InitEb
			FIND_PATTERN("60 FF BD 27 60 00 B4 E7 64 00 B6 E7 68 00 B8 E7");
			_LCS_CTheScripts__Init = cast<fn_LCS_CTheScripts__Init>(addr); //

			// sceCtrlReadBufferPositive
			FIND_PATTERN("25 80 80 00 14 00 A4 27 01 00 11 34");
			ptr _sceCtrlReadBufferPositiveutils_call = cast<ptr>(addr + 12);
			
			armhook::hook_mips_func(_VC3LCS_CTheScripts__Save, 8, VC3LCS_CTheScripts__Save, &VC3LCS_CTheScripts__Save_);
			CRunningScript__ProcessOneCommand_ = _CRunningScript__ProcessOneCommand;
			armhook::replace_mips_call(VC3LCS_CRunningScript__ProcessOneCommand_call_1, CRunningScript__ProcessOneCommand);
			armhook::hook_mips_func(_LCS_CTheScripts__Init, 8, LCS_CTheScripts__Init, &LCS_CTheScripts__Init_);
			armhook::hook_mips_func(_CText__Get, 8, CText__Get, &CText__Get_);
			armhook::replace_mips_call(_sceCtrlReadBufferPositiveutils_call, LCSVCS_sceCtrlReadBufferPositive);
		}
		else
		if (game == GTAVCS)
		{
			uint32_t addr;

			#define READ_ADDR_GP(addr) (libres::getGpValue() + *cast<int16_t *>(addr))
			
			// ScriptParams
			FIND_PATTERN("?? ?? 11 3C 00 00 B0 AF ?? ?? 30 26");
			ScriptParams = cast<uint32_t *>(READ_ADDR(addr, addr + 8));

			// _ZN6CTimer22m_snTimeInMillisecondsE
			FIND_PATTERN("?? ?? 86 8F B3 3E 07 3C 2B 28 C5 00");
			CTimer__m_snTimeInMilliseconds = cast<uint32_t *>(READ_ADDR_GP(addr));
			
			// _ZN11CTheScripts11ScriptSpaceE
			FIND_PATTERN("18 00 A4 8F ?? ?? 84 AF");
			CTheScripts__ScriptSpace_LCS = cast<ptr*>(READ_ADDR_GP(addr + 4));

			// _ZN11CTheScripts14pActiveScriptsE
			FIND_PATTERN("08 00 25 AE 10 00 30 AE ?? ?? 85 27");
			CTheScripts__pActiveScripts = cast<ptr>(READ_ADDR_GP(addr + 8));

			// _ZN11CTheScripts14StartNewScriptEi
			FIND_PATTERN("F0 FF BD 27 00 00 B0 AF 04 00 B1 AF ?? ?? 91 8F");
			CTheScripts__StartNewScript = cast<fn_CTheScripts__StartNewScript>(addr);

			// _ZN14CRunningScript17ProcessOneCommandEv
			FIND_PATTERN("F0 FF BD 27 08 00 BF AF ?? ?? 85 8F 10 00 86 8C");
			_CRunningScript__ProcessOneCommand = cast<fn_CRunningScript__ProcessOneCommand>(addr); //
			
			// _ZN5CText3GetEPKc
			FIND_PATTERN("08 00 B1 AF 25 80 A0 00 25 88 80 00 00 00 A0 A3");
			_CText__Get = cast<fn_CText__Get>(addr - 8);

			// GetPointerToScriptVariable
			FIND_PATTERN("00 00 A6 8C ?? ?? 87 8F 01 00 C8 24");
			VC3LCS_CRunningScript__GetPointerToScriptVariable = cast<fn_VC3LCS_CRunningScript__GetPointerToScriptVariable>(addr);

			// _ZN11CTheScripts14SaveAllScriptsEPhPj
			FIND_PATTERN("1C 00 BF AF ?? ?? 06 34");
			_VC3LCS_CTheScripts__Save = cast<fn_VC3LCS_CTheScripts__Save>(addr - 0x1C);

			// _ZN14CRunningScript17CollectParametersEPjiPi
			FIND_PATTERN("1C 00 E4 48 1D 00 E5 48 00 00 A5 8C");
			LCS_CRunningScript__CollectParameters = cast<fn_LCS_CRunningScript__CollectParameters>(addr);

			// _ZN11CTheScripts4InitEb
			FIND_PATTERN("60 00 B7 AF 64 00 BE AF 68 00 BF AF FF 00 84 30");
			_LCS_CTheScripts__Init = cast<fn_LCS_CTheScripts__Init>(addr - 0x34); //

			// sceCtrlReadBufferPositive
			FIND_PATTERN("25 80 80 00 04 00 A4 27 01 00 11 34");
			ptr _sceCtrlReadBufferPositiveutils_call = cast<ptr>(addr + 12);

			armhook::hook_mips_func(_VC3LCS_CTheScripts__Save, 8, VC3LCS_CTheScripts__Save, &VC3LCS_CTheScripts__Save_);
			CRunningScript__ProcessOneCommand_ = _CRunningScript__ProcessOneCommand;
			armhook::replace_mips_call(VC3LCS_CRunningScript__ProcessOneCommand_call_1, CRunningScript__ProcessOneCommand);
			armhook::hook_mips_func(_LCS_CTheScripts__Init, 8, LCS_CTheScripts__Init, &LCS_CTheScripts__Init_);
			armhook::hook_mips_func(_CText__Get, 8, CText__Get, &CText__Get_);
			armhook::replace_mips_call(_sceCtrlReadBufferPositiveutils_call, LCSVCS_sceCtrlReadBufferPositive);
		}
		find_idle_scripts();
		return true;
	}

	// calls all initializers
	void initialize()
	{
		mutex::init();

		utils::log(VERSION_STR);
		utils::log("initialize start");

		// resolve main game lib
		if (libres::init(game, image_base))
		{
			utils::log("game's (index %d) main library resolved (image base 0x%08X)", game, image_base);
		} else 
		{
			utils::log("initialize failed - can't resolve game's main library");
			return;
		}

		game_ver = game == GTALCS ? VER_GTALCS_PSP_1_05_OR_HIGHER : VER_GTAVCS_PSP_1_02_OR_HIGHER;

		// print game version
		utils::log("game ver: %s", str_game_version[game_ver]);

		utils::log("disc: %s ver: %s code: 0x%08X", libres::getDiscId(), libres::getDiscVersion(), libres::getDiscVersionCode());
		package_name = libres::getDiscId();
		package_version_name = libres::getDiscVersion();
		package_version_code = libres::getDiscVersionCode();

		// init armhook
		armhook::init();

		// init code
		if (init_code())
		{
			utils::log("code initialized");
		} else
		{
			utils::log("initialize failed - can't initialize code");
			return;
		}

		// init ui code
		ui::init();
		utils::log("ui code initialized");

		// init text
		text::init();

		utils::log("initialize success");

		plugins::init(get_storage_dir(), get_storage_dir());
	}

	// Script copies and FXT text share the bounded 256 KiB module arena with
	// the UI, text table and strings; files beyond these budgets are skipped
	// with a log line instead of exhausting it.
	constexpr uint32_t scriptCodeBudget = 128 * 1024, textBudget = 32 * 1024;
	uint32_t scriptCodeBytes, textBytes;

	// copies script to the buf and adds it to the list
	bool preload_script(std::string fname, const uint8_t *code, uint32_t code_size, bool is_invokable, uint32_t invokable_id)
	{
		if (!code || !code_size || code_size>UINT32_MAX-8 || scripts.size()==128) return false;
		// copy script to the script code buf
		if (game == GTALCS || game == GTAVCS) // has to be fixed in SB
		{
			if (code_size >= 8)
			{
				uint64_t pad;
				memcpy(&pad, code, sizeof(pad));
				if (!pad)
				{
					code += 8;
					code_size -= 8;
				}
			}
		}
		uint8_t *script_code;
		if (!code_size) return false;
		if (code_size + 8 > scriptCodeBudget - scriptCodeBytes)
		{
			utils::log("Script '%s' skipped: script storage budget (%u bytes) is full", fname.c_str(), scriptCodeBudget);
			return false;
		}
		script_code = new (std::nothrow) uint8_t[code_size + 8];
		if (!script_code) { utils::log("Insufficient module storage for script '%s'",fname.c_str());return false; }
		memcpy(script_code, code, code_size);
		memset(script_code+code_size,0,8);

		// fill script desc and add it to the scripts arr
		t_script *script = new (std::nothrow) t_script();
		if (!script) { delete[] script_code;return false; }
		script->invokable_id = is_invokable ? invokable_id : -1;
		script->name = fname;
		script->code = script_code;
		script->code_size = code_size;
		scriptCodeBytes += code_size + 8;
		script->offset = game == GTASA ? cast<uint32_t>(script->code) : cast<uint32_t>(script->code) - cast<uint32_t>(CTheScripts__ScriptSpace);
		scripts.push_back(script);

		// set invokable script name for menu
		if (is_invokable)
			text::set_gxt_invokable_script_name(invokable_id, fname);
		return true;
	}

	// preloads scripts at start
	void preload_scripts()
	{
		// external storage dir
		std::string dir = get_storage_dir();
		// enum files in data dir
	    std::vector<std::string> files;
	    utils::list_files_in_dir(dir, files);
	    // clear scripts
		for (int i = 0; i < scripts.size(); i++)
		{
			delete[] scripts[i]->code;
			delete scripts[i];
		}
		scripts.clear();
		scriptCodeBytes = 0;
		textBytes = 0;
		// init gxt entries
		text::init();
		// delete menu ui
		ui::delete_menu();
		// init script menu for sa
		switch (game)
		{
			case GTALCS:
				preload_script("menu", lcs_menu_script, sizeof(lcs_menu_script), false, 0);
				break;
			case GTAVCS:
				preload_script("menu", vcs_menu_script, sizeof(vcs_menu_script), false, 0);
				break;
		}
		// check all found files
		uint32_t invokable_count = 0;
		for (int32_t i = 0; i < files.size(); i++)
		{
			// if file has needed extension then this is the script
			std::string fname = files.at(i);
			std::string ext = strutils::get_ext(fname);
			bool is_invokable = ext == "csi";
			if (ext == "csa" || is_invokable)
			{
				// preload script
				uint32_t code_size = 0;
				uint8_t *code = utils::load_binary_file(dir + fname, code_size);
				if (!code || !code_size)
				{
				    utils::log("can't read script '%s'", fname.c_str());
				    continue;
				}
				const bool loaded=preload_script(fname, code, code_size, is_invokable, invokable_count);
				if (loaded && is_invokable)
				    invokable_count++;
				free(code);
				utils::log("script '%s' with size %d preloaded", fname.c_str(), code_size);
			} else
			if (ext == "fxt")
			{
				// load fxt
				uint32_t size = 0;
				LPSTR text_raw = cast<LPSTR>(utils::load_binary_file(dir + fname, size));
				if (!text_raw || !size)
				{
				    utils::log("can't read fxt '%s'", fname.c_str());
				    continue;
				}
				if (size > textBudget - textBytes)
				{
					utils::log("fxt '%s' skipped: text budget (%u bytes) is full", fname.c_str(), textBudget);
					free(text_raw);
					continue;
				}
				textBytes += size;
				LPSTR text = cast<LPSTR>(malloc(size + 1));
				if (!text) { free(text_raw);continue; }
				memcpy(text, text_raw, size);
				text[size] = 0;
				text::load_gxt_entries_from_text(text, size);
				free(text);
				free(text_raw);
				utils::log("fxt '%s' loaded", fname.c_str());
			}
		}
		utils::log("total preloaded scripts %d", scripts.size());
	}

	// launches custom scripts
	void launch_scripts()
	{
		utils::log("launch_scripts start");
		mutex_vars.clear();
		for (int32_t i = 0; i < scripts.size(); i++)
		{
			t_script *script = scripts[i];
			// only normal custom scripts start here
			if (script->invokable_id == -1)
			{
				utils::log("starting script '%s'", script->name.c_str());
				script->handle = start_new_script(script->offset);
				script->wait_passed = false;
			} else // invokable scripts start by special opcode and don't require wait
			{
				script->handle = NULL;
				script->wait_passed = true;
			}
		}
		utils::log("launch_scripts success");
	}

	void save_scripts(uint32_t a,uint32_t b)
	{
		struct ScriptNode { ScriptNode* next; ScriptNode* prev; };
		auto& head=*cast<ScriptNode**>(CTheScripts__pActiveScripts);
		cleo::ScriptSave<ScriptNode> nativeScripts(head,[](ScriptNode* node) {
			return get_script_using_handle(cast<ptr>(node))!=nullptr;
		});
		if (!nativeScripts) { utils::log("Save rejected: malformed or reentrant script list");return; }
		if (game==GTASA) SA_CTheScripts__Save_();
		else VC3LCS_CTheScripts__Save_(a,b);
		// RAII restores the original head, links and execution order.
	}

	void stop_script(ptr handle)
	{
		if (t_script *script = get_script_using_handle(handle))
			script->invalid = true;
	}

	ptr get_real_code_ptr(uint32_t ip)
	{
		if (game != GTASA) ip += cast<uint32_t>(CTheScripts__ScriptSpace);
		return cast<ptr>(ip);
	}

	uint32_t get_ip_using_real_code_ptr(ptr realPtr)
	{
		if (game != GTASA) realPtr -= cast<uint32_t>(CTheScripts__ScriptSpace);
		return cast<uint32_t>(realPtr);
	}

	ptr get_real_label_ptr(ptr handle, uint32_t offset)
	{
		if (t_script *script = get_script_using_handle(handle))
		{
			const int32_t signedOffset=cleo::readUnaligned<int32_t>(&offset);
			const auto* target=cleo::ScriptMemory{script->code,script->code_size}.label(signedOffset);
			return const_cast<ptr>(target);
		}
		return NULL;
	}

	bool read_str_8byte(ptr handle, std::string &str)
	{
		uint32_t *p_ip = cast<uint32_t *>(handle + select(0x10, 0x10, 0x14, 0x18, 0x10));
		ptr code = get_real_code_ptr(*p_ip);
		str.clear();
		if (game != GTAVCS)
		{
			if (auto* script=get_script_using_handle(handle))
				if (!cleo::ScriptMemory{script->code,script->code_size}.contains(code,8)) return false;
			size_t length=0;while (length<8 && code[length]) ++length;
			str.append(cast<const char *>(code),length);
			*p_ip += 8;
		} else
		{
			auto* script=get_script_using_handle(handle);
			if (!script || !cleo::ScriptMemory{script->code,script->code_size}.contains(code,1) || *code != 0x0A) return false;
			const size_t length=cleo::ScriptMemory{script->code,script->code_size}.stringLength(code+1);
			if (length==SIZE_MAX) return false;
			str.append(cast<const char *>(code+1),length);
			*p_ip += str.size() + 2;
		}
		return true;
	}

	bool read_str_long(ptr handle, std::string &str)
	{
		uint32_t *p_ip = cast<uint32_t *>(handle + select(0x10, 0x10, 0x14, 0x18, 0x10));
		ptr code = get_real_code_ptr(*p_ip);
		auto* script=get_script_using_handle(handle);
		if (!script || !cleo::ScriptMemory{script->code,script->code_size}.contains(code,2)) return false;
		if (!cleo::ScriptMemory{script->code,script->code_size}.contains(code,2+code[1])) return false;
		if (*code != select(0x0E, 0x0E, 0x0E, 0x6B, 0x6B))
			return false;
		str.clear();
		str.append(cast<const char *>(code + 2), *(code + 1));
		*p_ip += *(code + 1) + 2;
		return true;
	}

	// implements custom opcodes
	bool custom_opcode(t_script& script, uint16_t op);
	// processes opcodes until opcode after which CRunningScript switch occures
	void process_opcodes(ptr handle)
	{
		// check if this thread handle is from our script
		bool handle_found = false;
		bool wait_passed = false;
		uint8_t *code = NULL;
		const char* name = "native";
		t_script *script = get_script_using_handle(handle);
		if (script)
		{
			code = script->code;
			name = script->name.c_str();
			wait_passed = script->wait_passed;
			handle_found = true;
		}

		//utils::log("%u handle_found %X %d", utils::get_tick_count(), handle, handle_found);

		// after the start custom scripts must be idle for a few seconds
		if (handle_found && !wait_passed)
		{
			uint32_t wait_time = (game == GTASA) ? 3000 : 2000;
			setfield<uint32_t>(handle, select(0x7C, 0x7C, 0xEC, 0x210, 0x200), *CTimer__m_snTimeInMilliseconds + wait_time);
			script->wait_passed = true;
			return;
		}

		// opcodes to replace
		uint16_t OP_J = 2,
				 OP_JT = 0x4C,
				 OP_JF = 0x4D,
				 OP_CALL = 0x50,
				 OP_RET = 0x51,
				 OP_ENDTHREAD = 0x4E,
				 OP_ENDCUSTOMTHREAD = 0x05DC;

		if (game == GTAVCS)
		{
			OP_JT = 0x21;
			OP_JF = 0x22;
			OP_CALL = 0x25;
			OP_RET = 0x26;
			OP_ENDTHREAD = 0x23;
		}

		bool result;
		unsigned budget = 4096;
		do
		{
			ptr ip = getfield<ptr>(handle, select(0x10, 0x10, 0x14, 0x18, 0x10)); // ip, for SA is absolute ptr
			//utils::log("%s %08X %08X %08X", __FUNCTION__, handle, ip + cast<uint32_t>(CTheScripts__ScriptSpace), CTheScripts__ScriptSpace);
			if (game != GTASA) ip += cast<uint32_t>(CTheScripts__ScriptSpace);

			if (script && (script->invalid || !cleo::ScriptMemory{code,script->code_size}.contains(ip,2))) {
				script->invalid = true;
				setfield<uint32_t>(handle,select(0x7C,0x7C,0xEC,0x210,0x200),0xFFFFFFFFu);
				utils::log("Stopped invalid script '%s'",name);
				return;
			}

			bool cond = getfield<uint8_t>(handle, select(0x78, 0x79, 0xE5, 0x20D, 0x209)) != 0; // thread if cond

			// the command stream isn't 4-byte aligned, the opcode can sit on an odd address
			uint16_t op = read_u16(ip);

			if (handle_found)
			{
				//utils::log("%s %X %X op %04X", cast<char *>(handle + select(8, 8, 8, 16, 0x20F)), handle, ip - code, op);
				if (op == OP_J || op == OP_JT || op == OP_JF || op == OP_CALL)
				{
					// Branch operands have a type byte followed by an unaligned int32.
					if (!cleo::ScriptMemory{code,script->code_size}.contains(ip,7)) { script->invalid=true;return; }
					// move to opcode param
					ip += 2;
					// check param type
					if (!(*ip == 1 || ((game == GTALCS || game == GTAVCS) && *ip == 6)))
					{
						utils::log("wrong param type in '%s' at %d, terminating", name, ip - code);
						script->invalid=true;return;
					}
					ip++;
					// read offset as int (ip is odd here: it points past the 1-byte param type)
					int32_t offset_signed = read_i32(ip);
					ip += 4;
					// calc offset from ScriptSpace
					const auto target=cleo::ScriptMemory{code,script->code_size}.label(offset_signed);
					if (!target) { script->invalid=true;return; }
					uint32_t offset=cast<uint32_t>(target);
					// OP_CALL saves thread ip on call stack
					if (op == OP_CALL)
					{
						// Do not let a malformed script overwrite locals through its return stack.
						constexpr unsigned capacity=16;
						if (getfield<uint16_t>(handle,select(0x2C,0x2C,0x38,0x5C,0x204))>=capacity) { script->invalid=true;return; }
						uint16_t si = getfield<uint16_t>(handle, select(0x2C, 0x2C, 0x38, 0x5C, 0x204));
						setfield<uint16_t>(handle, select(0x2C, 0x2C, 0x38, 0x5C, 0x204), si + 1);
						ptr vc3_ip = ip - cast<uint32_t>(CTheScripts__ScriptSpace);
						//utils::log("OP_CALL ret ip %X %X si %d", vc3_ip, ip, si);
						setfield<ptr>(handle, select(0x14, 0x14, 0x18, 0x1C, 0x14) + si * sizeof(uint32_t), select(vc3_ip, vc3_ip, ip, vc3_ip, vc3_ip));
					}
					// set new ip
					if ((op == OP_J) || (op == OP_CALL) || (op == OP_JT && cond) || (op == OP_JF && !cond))
						ip = cast<ptr>(offset);
					// set thread ip
					if (game != GTASA) ip -= cast<uint32_t>(CTheScripts__ScriptSpace);
					setfield<ptr>(handle, select(0x10, 0x10, 0x14, 0x18, 0x10), ip);
					result = false;
				} else
				if (op == OP_RET) // lcs uses it for ret from funcs as well, so let's replace it
				{					
					uint16_t depth=getfield<uint16_t>(handle,select(0x2C,0x2C,0x38,0x5C,0x204));
					if (!depth || depth>16) { script->invalid=true;return; }
					uint16_t si=depth-1;
					setfield<ptr>(handle, select(0x10, 0x10, 0x14, 0x18, 0x10),
							getfield<ptr>(handle, select(0x14, 0x14, 0x18, 0x1C, 0x14) + si * sizeof(uint32_t)));
					setfield<uint16_t>(handle, select(0x2C, 0x2C, 0x38, 0x5C, 0x204), si);
					//utils::log("OP_RET ret ip %X si %d", getfield<ptr>(handle, select(0x10, 0x10, 0x14, 0x18)), si);
					result = false;
				} else
				if (op == OP_ENDTHREAD || op == OP_ENDCUSTOMTHREAD)
				{
					// replacement for thread end opcodes
					utils::log("terminating script '%s'", name);
					setfield<uint32_t>(handle, select(0x7C, 0x7C, 0xEC, 0x210, 0x200), 0xFFFFFFFF); // wait time
					result = true;
				} else
				{
					ptr *p_ip = cast<ptr*>(handle + select(0x10, 0x10, 0x14, 0x18, 0x10));
					*p_ip += 2;
					if (custom_opcode(*script, op) || plugins::handle_opcode(script->handle, cast<uint32_t *>(p_ip), op))
					{
						result = false;
					} else
					{
						*p_ip -= 2;
						result = CRunningScript__ProcessOneCommand_(handle);
					}
				}
			} else
				result = CRunningScript__ProcessOneCommand_(handle);

		} while (!result && (!script || --budget));
	}

	bool custom_opcode(t_script &script, uint16_t op)
	{
		const uint16_t OP_GET_LABEL_ADDR = 0x0DD0,
					   OP_GET_FUNC_ADDR_CSTR = 0x0DD1,
					   OP_CONTEXT_CALL = 0x0DD2,
					   OP_CONTEXT_SET_REG = 0x0DD3,
					   OP_CONTEXT_GET_REG = 0x0DD4,
					   OP_GET_PLATFORM = 0x0DD5,
					   OP_GET_GAME_VER = 0x0DD6,
					   OP_GET_IMAGE_BASE = 0x0DD7,
					   OP_READ_MEM = 0x0DD8,
					   OP_WRITE_MEM = 0x0DD9,
					   OP_SEARCH_MEM = 0x0DDA,
					   OP_GET_GAME_VER_EX = 0x0DDB,
					   OP_SET_MUTEX_VAR = 0x0DDC,
					   OP_GET_MUTEX_VAR = 0x0DDD,
					   OP_CALL_FUNCTION = 0x0DDE,
					   OP_GET_TOUCH_POINT_STATE = 0x0DE0,
					   OP_GET_TOUCH_SLIDE_STATE = 0x0DE1,
					   OP_GET_MENU_BUTTON_STATE = 0x0DE2,
					   OP_GET_MENU_BUTTON_PRESSED = 0x0DE3,
					   OP_GET_PSP_CONTROL_STATE = 0x0DE4,
					   OP_GET_PSP_CONTROL_PRESSED = 0x0DE5,
					   OP_INVOKABLE_SCRIPT_STATS = 0x0DEE,
					   OP_START_INVOKABLE_SCRIPT = 0x0DEF,
					   OP_SHOW_MENU_OPEN_ARROW = 0x0DF0,
					   OP_HIDE_MENU_OPEN_ARROW = 0x0DF1,
					   OP_CREATE_MENU = 0x0DF2,
					   OP_DELETE_MENU = 0x0DF3,
					   OP_GET_MENU_TOUCHED_ITEM_INDEX = 0x0DF4,
					   OP_SET_MENU_ACTIVE_ITEM_INDEX = 0x0DF5,
					   OP_GET_MENU_ACTIVE_ITEM_INDEX = 0x0DF6;

		switch (op)
		{
		case OP_GET_LABEL_ADDR:
		{
			//utils::log("OP_GET_LABEL_ADDR");
			uint32_t *v = cast<uint32_t *>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
			CRunningScript__CollectParameters(script.handle, 1);
			uint32_t offset = ScriptParams[0];
			int32_t  offset_signed = *cast<int32_t *>(&offset);
			offset = (offset_signed >= 0) ? (cast<uint32_t>(script.code) + offset_signed) : (cast<uint32_t>(script.code) - offset_signed);
			*v = offset;
			return true;
		}
		case OP_GET_FUNC_ADDR_CSTR:
		{
			//utils::log("OP_GET_FUNC_ADDR_CSTR");
			uint32_t *v = cast<uint32_t *>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
			CRunningScript__CollectParameters(script.handle, 1);			
			*v = 0;
			//utils::log("func '%s' addr is 0x%X", func_name, *v);
			return true;
		}
		case OP_CONTEXT_CALL:
		{
			//utils::log("OP_CONTEXT_CALL");
			CRunningScript__CollectParameters(script.handle, 1);
			uint32_t func = ScriptParams[0];
			//utils::log("call func 0x%x", func);
			asm_call(script.context, func);
			return true;
		}
		case OP_CONTEXT_SET_REG:
		{
			//utils::log("OP_CONTEXT_SET_REG");
			CRunningScript__CollectParameters(script.handle, 2);
			uint32_t reg = ScriptParams[0];
			uint32_t val = ScriptParams[1];
			if (reg < 32) script.context[reg] = val;
			return true;
		}
		case OP_CONTEXT_GET_REG:
		{
			//utils::log("OP_CONTEXT_GET_REG");
			uint32_t *v = cast<uint32_t *>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
			CRunningScript__CollectParameters(script.handle, 1);
			uint32_t reg = ScriptParams[0];
			*v = reg < 32 ? script.context[reg] : 0;
			return true;
		}
		case OP_GET_PLATFORM:
		{
			//utils::log("OP_GET_PLATFORM");
			uint32_t *v = cast<uint32_t *>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
			*v = 2;
			return true;
		}
		case OP_GET_GAME_VER:
		{
			//utils::log("OP_GET_GAME_VER");
			uint32_t *v = cast<uint32_t *>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
			*v = game_ver;
			return true;
		}
		case OP_GET_IMAGE_BASE:
		{
			//utils::log("OP_GET_IMAGE_BASE");
			uint32_t *v = cast<uint32_t *>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
			*v = image_base;
			return true;
		}
		case OP_READ_MEM:
		{
			//utils::log("OP_READ_MEM");
			uint32_t *v = cast<uint32_t *>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
			CRunningScript__CollectParameters(script.handle, 3);
			uint32_t addr = ScriptParams[0];
			uint32_t size = ScriptParams[1];
			uint32_t correct_ib = ScriptParams[2];
			if (correct_ib)
				addr += image_base;
			*v = 0;
			// The destination is one script variable; unmapped reads would fault.
			if (size > sizeof(*v)) size = sizeof(*v);
			if (memutils::mem_is_readable(cast<const void *>(addr), size))
				memcpy(v, cast<const void *>(addr), size);
			return true;
		}
		case OP_WRITE_MEM:
		{
			//utils::log("OP_WRITE_MEM");
			CRunningScript__CollectParameters(script.handle, 5);
			uint32_t addr = ScriptParams[0];
			uint32_t val = ScriptParams[1];
			uint32_t size = ScriptParams[2];
			uint32_t correct_ib = ScriptParams[3];
			uint32_t protect = ScriptParams[4];
			if (correct_ib)
				addr += image_base;
			if (size > sizeof(val)) size = sizeof(val); // the source is one 32-bit value
			if (memutils::mem_is_readable(cast<const void *>(addr), size))
				memutils::mem_write_arr(cast<uint8_t *>(addr), cast<uint8_t *>(&val), size, protect);
			return true;
		}
		case OP_SEARCH_MEM:
		{
			//utils::log("OP_SEARCH_MEM");
			uint32_t *v = cast<uint32_t *>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
			CRunningScript__CollectParameters(script.handle, 2);
			LPSTR pattern = cast<LPSTR>(ScriptParams[0]);
			uint32_t index = ScriptParams[1];			
			if (!__FindPatternAddressCompact(*v, pattern, index))
				*v = 0;
			//utils::log("pattern '%s' index %d addr is 0x%X", pattern, index, *v);
			return true;
		}
		case OP_GET_GAME_VER_EX:
		{
			//utils::log("OP_GET_GAME_VER_EX");
			uint32_t *id = cast<uint32_t *>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
			uint32_t *ver = cast<uint32_t *>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
			uint32_t *ver_code = cast<uint32_t *>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
			*id = 0;
			if (package_name.size() > 4)
				sscanf(package_name.c_str() + 4, "%lu", id);
			*ver = strutils::str_hash(package_version_name);
			*ver_code = package_version_code;
			return true;
		}
		case OP_SET_MUTEX_VAR:
		{
			//utils::log("OP_SET_MUTEX_VAR");
			CRunningScript__CollectParameters(script.handle, 2);
			uint32_t id = ScriptParams[0];
			uint32_t v = ScriptParams[1];
			if (mutex_vars.size())
				for (int32_t i = 0; i < mutex_vars.size(); i++)
					if (mutex_vars.at(i).id == id)
					{
						mutex_vars.at(i).value = v;
						return true;
					}
			t_mutex_var mv;
			mv.id = id;
			mv.value = v;
			mutex_vars.push_back(mv);
			return true;
		}
		case OP_GET_MUTEX_VAR:
		{
			//utils::log("OP_GET_MUTEX_VAR");
			uint32_t *v = cast<uint32_t *>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
			CRunningScript__CollectParameters(script.handle, 1);
			uint32_t id = ScriptParams[0];
			*v = 0;
			if (mutex_vars.size())
				for (int32_t i = 0; i < mutex_vars.size(); i++)
					if (mutex_vars.at(i).id == id)
					{
						*v = mutex_vars.at(i).value;
						break;
					}
			return true;
		}
		case OP_CALL_FUNCTION:
		{
			//utils::log("OP_CALL_FUNCTION");
			CRunningScript__CollectParameters(script.handle, 2);
			uint32_t addr = ScriptParams[0];
			uint32_t add_ib = ScriptParams[1];
			if (add_ib) addr += image_base;

			int params_i[8];
			memset(params_i, 0, sizeof(params_i));

			float params_f[8];
			memset(params_f, 0, sizeof(params_f));

			bool is_res_float = false;	

			uint32_t params_a[32]; // any
			memset(params_a, 0, sizeof(params_a));

			int params_i_count = 0;
			int params_f_count = 0;
			int params_a_count = 0;

			void *res_ptr = NULL;			

			while (true)
			{				
				// see if this is opcode param list end
				uint32_t *p_ip = cast<uint32_t *>(script.handle + select(0x10, 0x10, 0x14, 0x18, 0x10));
				ptr code = get_real_code_ptr(*p_ip);
				if (*code == 0)
				{
					*p_ip += 1;
					break;
				}

				// read string type
				std::string str;
				if (!read_str_8byte(script.handle, str))
				{
					utils::log("func call param type has to be 8byte string");
					script.invalid=true;return true;
				}
				str = strutils::str_to_lower(str);

				// param type enum
				enum eParamType
				{
					ptNone,
					ptInt,
					ptFloat
				};

				// parse param
				eParamType pt = ptNone;
				uint32_t int_val = 0;
				float float_val = 0.0f;
				if (str == "i")
				{
					CRunningScript__CollectParameters(script.handle, 1);
					int_val = ScriptParams[0];
					pt = ptInt;
				} else
				if (str == "f")
				{
					CRunningScript__CollectParameters(script.handle, 1);
					float_val = *cast<float *>(&ScriptParams[0]);
					pt = ptFloat;
				} else
				if (str == "ref")
				{
					int_val = cast<uint32_t>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
					pt = ptInt;
				} else
				if (str == "resi")
				{
					res_ptr = CRunningScript__GetPointerToScriptVariable(script.handle, 0);
				} else
				if (str == "resf")
				{
					res_ptr = CRunningScript__GetPointerToScriptVariable(script.handle, 0);
					is_res_float = true;
				} else
				{
					utils::log("func call has unknown param type '%s'", str.c_str());
					script.invalid=true;return true;
				}

				// if this is a func param then put it into one of the func param arrays
				if (pt != ptNone)
				{
					// verify func param limit
					if (params_i_count + params_f_count + params_a_count == 32)
					{
						utils::log("func call has more than 32 params");
						script.invalid=true;return true;
					}
					if (pt == ptInt)
					{
						if (params_i_count < 8)
							params_i[params_i_count++] = int_val;
						else
							params_a[params_a_count++] = int_val;							
					} else
					{
						if (params_f_count < 8)
							params_f[params_f_count++] = float_val;
						else {
							void *float_ptr = &float_val;
							params_a[params_a_count++] = *cast<uint32_t *>(float_ptr);
						}
					}
				}
			}

			#define PARAM_TYPES \
				uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, \
				float,    float,    float,    float,    float,    float,    float,    float,    \
				uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, \
				uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, \
				uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t

			#define PARAM_VALS \
				params_i[0],  params_i[1],  params_i[2],  params_i[3],  params_i[4],  params_i[5],  params_i[6],  params_i[7],  \
				params_f[0],  params_f[1],  params_f[2],  params_f[3],  params_f[4],  params_f[5],  params_f[6],  params_f[7],  \
				params_a[0],  params_a[1],  params_a[2],  params_a[3],  params_a[4],  params_a[5],  params_a[6],  params_a[7],  \
				params_a[8],  params_a[9],  params_a[10], params_a[11], params_a[12], params_a[13], params_a[14], params_a[15], \
				params_a[16], params_a[17],	params_a[18], params_a[19], params_a[20], params_a[21], params_a[22], params_a[23]

			if (!is_res_float)
			{
				typedef uint32_t (*func_i_t)(PARAM_TYPES);
				uint32_t res = cast<func_i_t>(addr)(PARAM_VALS);
				if (res_ptr)
					*cast<uint32_t *>(res_ptr) = res;
			} else
			{
				typedef float (*func_f_t)(PARAM_TYPES);
				float res = cast<func_f_t>(addr)(PARAM_VALS);
				if (res_ptr)
					*cast<float *>(res_ptr) = res;
			}

			#undef PARAM_VALS
			#undef PARAM_TYPES			

			return true;
		}
		case OP_GET_TOUCH_POINT_STATE:
		{
			uint32_t *v = cast<uint32_t *>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
			CRunningScript__CollectParameters(script.handle, 2);
			*v = 0;
			return true;
		}
		case OP_GET_TOUCH_SLIDE_STATE:
		{
			uint32_t *v = cast<uint32_t *>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
			CRunningScript__CollectParameters(script.handle, 4);
			*v = 0;
			return true;
		}
		case OP_GET_MENU_BUTTON_STATE:
		{
			uint32_t *v = cast<uint32_t *>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
			*v = (touch::menu_button_pressed()) ? 1 : 0;
			return true;
		}
		case OP_GET_MENU_BUTTON_PRESSED:
		{
			uint32_t *v = cast<uint32_t *>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
			CRunningScript__CollectParameters(script.handle, 1);
			uint32_t mintime = ScriptParams[0];
			*v = (touch::menu_button_pressed_timed(mintime)) ? 1 : 0;
			return true;
		}
		case OP_GET_PSP_CONTROL_STATE:
		{
			uint32_t *v = cast<uint32_t *>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
			CRunningScript__CollectParameters(script.handle, 1);
			uint32_t index = ScriptParams[0];
			*v = (touch::psp_control_pressed((ePspControl)index)) ? 1 : 0;
			return true;
		}
		case OP_GET_PSP_CONTROL_PRESSED:
		{
			uint32_t *v = cast<uint32_t *>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
			CRunningScript__CollectParameters(script.handle, 2);
			uint32_t index = ScriptParams[0];
			uint32_t mintime = ScriptParams[1];
			*v = (touch::psp_control_pressed_timed((ePspControl)index, mintime)) ? 1 : 0;
			return true;
		}
		case OP_INVOKABLE_SCRIPT_STATS:
		{
			uint32_t inv_count = 0;
			if (scripts.size())
				for (int32_t i = 0; i < scripts.size(); i++)
					if (scripts[i]->invokable_id != -1)
						inv_count++;
			uint32_t *p_count = cast<uint32_t *>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
			uint32_t *p_page_count = cast<uint32_t *>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
			*p_count = inv_count;
			*p_page_count = inv_count / 12 + 1;
			return true;
		}
		case OP_START_INVOKABLE_SCRIPT:
		{
			uint32_t *v = cast<uint32_t *>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
			CRunningScript__CollectParameters(script.handle, 1);
			uint32_t id = ScriptParams[0];
			if (scripts.size())
			{
				for (int32_t i = 0; i < scripts.size(); i++)
				{
					t_script *script = scripts[i];
					if (script->invokable_id == id)
					{
						// if script isn't started before
						if (script->handle == NULL)
						{
							utils::log("starting invokable script '%s'", script->name.c_str());
							script->handle = start_new_script(script->offset);
							*v = script->handle ? 0 : -1;
							return true;
						}
						// if script started before and already finished
						uint32_t wait_time = getfield<uint32_t>(script->handle, select(0x7C, 0x7C, 0xEC, 0x210, 0x200));
						if (wait_time == 0xFFFFFFFF)
						{
							utils::log("restarting invokable script '%s'", script->name.c_str());
							// set start ip
							uint32_t *p_ip = cast<uint32_t *>(script->handle + select(0x10, 0x10, 0x14, 0x18, 0x10));
							*p_ip = script->offset;
							// remove wait
							setfield<uint32_t>(script->handle, select(0x7C, 0x7C, 0xEC, 0x210, 0x200), 0);
							*v = 1;
							return true;
						}
						// script is running
						utils::log("invokable script '%s' already running", script->name.c_str());
						*v = 2;
						return true;
					}
				}
			}
			utils::log("invokable script %d not found", id);
			*v = -1;
			return true;
		}
		case OP_SHOW_MENU_OPEN_ARROW:
		{
			//ui::show_arrow();
			return true;
		}
		case OP_HIDE_MENU_OPEN_ARROW:
		{
			//ui::hide_arrow();
			return true;
		}
		case OP_CREATE_MENU:
		{
			CRunningScript__CollectParameters(script.handle, 2);
			uint32_t addr = ScriptParams[0];
			uint32_t item_count = ScriptParams[1];
			// read flags
			uint8_t flags = *cast<uint8_t *>(addr);
			bool bItemsUseGxt = flags & 1;
			bool bGxtTrimToFit = (flags & 2) != 0;
			uint32_t maxItemStrSize = bGxtTrimToFit ? select(20, 20, 20, 18, 19) : 0;
			addr += 4;
			// read title
			std::string title;
			while (*cast<char *>(addr))
			{
				title += *cast<char *>(addr);
				addr++;
			}
			addr++;
			title = psplang::localize(title);
			// read close button title
			std::string titleclose;
			while (*cast<char *>(addr))
			{
				titleclose += *cast<char *>(addr);
				addr++;
			}
			addr++;
			titleclose = psplang::localize(titleclose);
			// read items
			std::vector<wide_string> items;
			while (*cast<char *>(addr) && item_count)
			{
				// read item
				std::string a_item;
				wide_string w_item;				
				while (*cast<char *>(addr))
				{
					a_item += *cast<char *>(addr);
					w_item += *cast<char *>(addr);
					addr++;
				}
				addr++;
				bool bGxtEntryExists = false;
				if (bItemsUseGxt)
				{
					if (uint16_t *wstr = GetGxtEntry(a_item.c_str(), true))
					{
						std::string str = strutils::ansi_from_wstr(wstr);
						if (str.size())
						{
							if (game == GTA3)
							{
								if (!strstr(str.c_str(), "missing"))
								{
									bGxtEntryExists = true;
									w_item = wstr;									
								}
							} else
							{
								bGxtEntryExists = true;
								w_item = wstr;
							}
						}
					}
				}
				if (!bGxtEntryExists)
					w_item = strutils::wstr_from_ansi(psplang::localize(a_item).c_str());	
				if (bGxtEntryExists && maxItemStrSize && w_item.size() > maxItemStrSize)
					w_item.erase(maxItemStrSize);
				items.push_back(w_item);
				item_count--;
			}
			// create menu
			ui::create_menu(title, titleclose, items);
			return true;
		}
		case OP_DELETE_MENU:
		{
			ui::delete_menu();
			return true;
		}
		case OP_GET_MENU_TOUCHED_ITEM_INDEX:
		{
			int32_t *v = cast<int32_t *>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
			CRunningScript__CollectParameters(script.handle, 1);
			uint32_t maxtime = ScriptParams[0];	// touch valid time
			*v = ui::get_menu_touched_item_index(maxtime);
			return true;
		}
		case OP_SET_MENU_ACTIVE_ITEM_INDEX:
		{
			CRunningScript__CollectParameters(script.handle, 1);
			int32_t page_index = ScriptParams[0];
			ui::set_menu_active_item_index(page_index);
			return true;
		}
		case OP_GET_MENU_ACTIVE_ITEM_INDEX:
		{
			int32_t *v = cast<int32_t *>(CRunningScript__GetPointerToScriptVariable(script.handle, 0));
			*v = ui::get_menu_active_item_index();
			return true;
		}
		default:
			return false;
		}
	}
}


