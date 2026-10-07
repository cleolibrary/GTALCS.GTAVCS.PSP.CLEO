#include "libres.h"
#include "utils.h"

using namespace core;

// resolves main game library symbols
namespace libres
{
	void *loadAddress = NULL;
	void *getLoadAddress()
	{
		return loadAddress;
	}	

	std::vector<section_addr_space_t> executableSections;
	const std::vector<section_addr_space_t> &getExecutableSections()
	{
		return executableSections;
	}

	std::string libFileName;
	const char *getLibFileName()
	{
		return libFileName.c_str();
	}


	uint32_t gpValue = 0;
	uint32_t getGpValue()
	{
		return gpValue;
	}	

	std::string disc_id;
	const char *getDiscId()
	{
		return disc_id.c_str();
	}

	std::string disc_version;
	const char *getDiscVersion()
	{
		return disc_version.c_str();
	}
	
	uint32_t disc_version_code;
	uint32_t getDiscVersionCode()
	{
		return disc_version_code;
	}

	struct SFO_Header
	{
		u32 magic; /* Always PSF */
		u32 version; /* Usually 1.1 */
		u32 key_table_start; /* Start position of key_table */
		u32 data_table_start; /* Start position of data_table */
		u32 index_table_entries; /* Number of entries in index_table*/
	};

	struct SFO_IndexTable
	{
		u16 key_table_offset; /* Offset of the param_key from start of key_table */
		u16 param_fmt; /* Type of data of param_data in the data_table */
		u32 param_len; /* Used Bytes by param_data in the data_table */
		u32 param_max_len; /* Total bytes reserved for param_data in the data_table */
		u32 data_table_offset; /* Offset of the param_data from start of data_table */
	};

	bool init(e_game &game, int32_t &image_base)
	{		
		SceUID modules[10];
		int count = 0;
		if (sceKernelGetModuleIdList(modules, sizeof(modules), &count) >= 0)
		{
			SceKernelModuleInfo info;
			for (int i = 0; i < count; ++i)
			{
				info.size = sizeof(SceKernelModuleInfo);
				if (sceKernelQueryModuleInfo(modules[i], &info) < 0)
					continue;

				if (strcmp(info.name, "GTA3") == 0)
				{
					loadAddress = cast<void *>(info.text_addr);					
					image_base = info.text_addr;
					section_addr_space_t addr_space;
					addr_space.addr = 0;
					addr_space.size = info.text_size;
					executableSections.push_back(addr_space);
					gpValue = info.gp_value;
					break;
				}
			}
		}
		if (!loadAddress)
			return false;

		// load file
		uint32_t size;
		void *buf = utils::load_binary_file("disc0:/PSP_GAME/PARAM.SFO", size);
		if (!buf || size < 8)
			return false;

		uint32_t addr = cast<uint32_t>(buf);
		SFO_Header *header = cast<SFO_Header *>(addr);
		if (header->magic != 0x46535000 || header->version != 0x00000101)
			return false;
		SFO_IndexTable *index = cast<SFO_IndexTable *>(addr + sizeof(SFO_Header));

		std::string title;
		for (int i = 0; i < header->index_table_entries; i++)
		{
			if (index[i].param_fmt != 0x0204)
				continue;
			std::string name = cast<char *>(addr + header->key_table_start + index[i].key_table_offset);
			char *val = cast<char *>(addr + header->data_table_start + index[i].data_table_offset);
			if (name == "DISC_ID") disc_id = val; else
			if (name == "DISC_VERSION") disc_version = val; else
			if (name == "TITLE") title = val;
		}		
		free(buf);
		if (disc_id.empty() || disc_version.empty())
			return false;

		uint32_t disk_ver[2] = { 0, 0 };
		sscanf(disc_version.c_str(), "%lu.%lu", &disk_ver[0], &disk_ver[1]);
		disc_version_code = ((disk_ver[0] & 0xFF) << 8) | (disk_ver[1] & 0xFF);
		if (!disc_version_code)
			return false;
		
		if (title == "GTA: Liberty City Stories" || title == "Grand Theft Auto: Liberty City Stories") game = GTALCS; else
		if (title == "Grand Theft Auto: Vice City Stories") game = GTAVCS; else
			return false;

		libFileName = "disc0:/PSP_GAME/SYSDIR/EBOOT.BIN";

		return true;
	}

}

























