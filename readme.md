# CLEO PSP / CLEO ANDROID

Version: 2.0.2

Date: Oct 2024

# Description

CLEO PSP is a version of the top-most popular GTA PC version add-on - CLEO library, which enhances game's script engine with ability to load custom scripts. Use cheats, spawn cars and use lots of cool features.

# Disclaimer and Limitation of Liability

You are using this application at your own risk, you agree to take full responsibility for anything that this application can cause. You are not allowed to install the application or any of the application components if you don't agree with these terms.

## Changes in 2.0.2

- Menu opening behavior is changed, press [start] to open the main menu, press [start] again to open cleo menu, press [circle] to close main menu without opening cleo menu.
- Popup information is hidden, to allow vanilla game experience

## Changes in 2.0.1

- the library has been ported to PSP, supports both LCS and VCS
- added support for plugins

## Requirements

- PSP game series require PPSSPP 1.11.2 or higher (any platform)

## Supported game versions

- LCS ULES00151/ULES00182/ULUS10041 (all builds, meaning v1.05 to v3.00)
- VCS ULES00502/ULES00503/ULUS10160 (all builds, meaning v1.02 to v1.03)

## Scripts

CLEO PSP is using *.csa and *.csi script extensions, *.csa scripts start just after the game loads and *.csi ones only when you directly invoke them via ingame script menu. To open the menu perform a slide from screen top to bottom thru center, arrow popup at start should give a tip, this one is related to the mobile game series only. In order to open the menu on PSP, press [start], and then [start] again, and you will see cleo menu.
In order to install scripts manually, put scripts in `%sdcard%/PSP/PLUGINS/cleo/%game%` where the `%game%` is either "lcs" or "vcs".

## Plugins

CLEO PSP supports custom plugins (*.prx), if you just want to install CLEO PSP plugin then copy the thing in the same folder you would put *.csa/csi script (%game% folder). See developers section if you want to know more about this.

# Developers

## Scripts

A lot of PC CLEO *.cs scripts must be manually rewritten before they can be used with CLEO PSP since *.cs scripts use PC opcodes and PC oriented controls. CLEO PSP is using *.csa and *.csi script extensions, which internally are the same as PC *.cs scripts, while *.csa scripts start when the game loads and *.csi when user directly invokes a script using the menu. 

The name which appears in the menu is a decorated version of an original script file name - game prefix gets cleaned out (e.g. "gtasa."), extension is removed too (".csi"), dots and underlines get replaced with spaces. For instance "gtasa.car_spawner.csi" will appear in the menu as "car spawner". 

You can compile and decompile CLEO PSP scripts with Sanny Builder, in order to do so add the list of CLEO PSP opcode declarations in the corresponding SCM.INI file:

```
; CLEO ANDROID (PSP)
0DD0=2,%1d% = get_label_addr %2p%
0DD1=2,%1d% = get_func_addr_by_cstr_name %2d%
0DD2=1,context_call_func %1d% ; deprecated, use 0DDE instead
0DD3=2,context_set_reg %1d% value %2d% ; deprecated, use 0DDE instead
0DD4=2,%1d% = context_get_reg %2d% ; deprecated, use 0DDE instead
0DD5=1,%1d% = get_platform
0DD6=1,%1d% = get_game_version
0DD7=1,%1d% = get_image_base
0DD8=4,%1d% = read_mem_addr %2d% size %3d% add_ib %4d%
0DD9=5,write_mem_addr %1d% value %2d% size %3d% add_ib %4d% protect %5d%
0DDA=3,%1d% = get_pattern_addr_cstr %2d% index %3d%
0DDB=3,get_game_ver_ex name_hash %1d% ver_hash %2d% ver_code %3d%
0DDC=2,set_mutex_var %1d% to %2d%
0DDD=2,%1d% = get_mutex_var %2d%
0DDE=-1, call_func %1d% add_ib %2d%
0DE0=3,%1d% = get_touch_point_state %2d% mintime %3d%
0DE1=5,%1d% = get_touch_slide_state from %2d% to %3d% mintime %4d% maxtime %5d%
0DE2=1,%1d% = get_menu_button_state
0DE3=2,%1d% = get_menu_button_pressed mintime %2d%
0DE4=2,%1d% = psp_get_control_state %2d%
0DE5=3,%1d% = psp_get_control_pressed %2d% mintime %3d%
0DF2=2,create_menu %1d% items %2d% 
0DF3=0,delete_menu
0DF4=2,%1d% = get_menu_touched_item_index maxtime %2d%
0DF5=1,set_menu_active_item_index %1d%
0DF6=1,%1d% = get_menu_active_item_index
1000=-1, opcode_func
```

Example scripts compilation for LCS/VCS requires basic keyword definitions, if your current version of SB doesn't have these already defined then you have to define and add keywords.txt files manually:
- Open SB/data/modes.xml
- Find the mode with id="sa" and see how <keywords> are defined there
- Now find the mode with id="lcs"
- Define the keywords as <keywords>@sb:\data\lcs\keywords.txt</keywords>
- Do the same for id="vcs_psp" using <keywords>@sb:\data\vcs\keywords.txt</keywords>
- Create required keywords.txt files and put the respective definitions there

```
; keywords.txt for lcs
0001=wait
0002=goto
0002=jump
004d=jf
004e=end_thread
0050=gosub
0051=return
00db=if
03a9=thread
```

```
; keywords.txt for vcs
0001=wait
0002=goto
0002=jump
0022=jf
0023=end_thread
0025=gosub
0026=return
0078=if
0238=thread
```

## Opcodes explained

`0DD0=2,%1d% = get_label_addr %2p%`

`0DD1=2,%1d% = get_func_addr_by_cstr_name %2d%`

These two are usually used together, first one gets real address of the target label where string or anything else is written and the second gets exported symbol name in the game's main library by C-style string name. It was done in the way like this (not using long strings) in order for opcode to be universal and also work with games which do not support long string type. When used with PSP game series 0DD1 will return 0.

`0DD2=1,context_call_func %1d%`

`0DD3=2,context_set_reg %1d% value %2d%`

`0DD4=2,%1d% = context_get_reg %2d%`

Deprecated, use 0DDE instead.

`0DD5=1,%1d% = get_platform`

Returns current platform: Android = 1, PSP = 2, primarely used for LCS scripts.

`0DD6=1,%1d% = get_game_version`

Returns internal game version, see sdk -> cleo.h -> eGameVerInternal for the details.

`0DD7=1,%1d% = get_image_base`

Returns image base of the main game library.

`0DD8=4,%1d% = read_mem_addr %2d% size %3d% add_ib %4d%`

`0DD9=5,write_mem_addr %1d% value %2d% size %3d% add_ib %4d% protect %5d%`

Reads and writes memory, add_ib should be set only when raw address specified and it needs to be added to the imagebase in order to access needed memory location.

`0DDA=3,%1d% = get_pattern_addr_cstr %2d% index %3d%`

Searches for the specified byte pattern in main library, if there are few addresses which match this pattern the index is used, see example scripts for the details. Works on both Android and PSP, the search if performed within all executable sections. Max length for the pattern is 32 bytes. Returns 0 if no pattern was found. The thing to keep in mind while using this on PSP - if you are searching for a function start bytes you have to mark first 4 as ?? since PPSSPP can override this for JIT purporses.

`0DDB=3,get_game_ver_ex name_hash %1d% ver_hash %2d% ver_code %3d%`

Returns current game version:
* name_hash is a jenkins hash of an Android package name, on PSP not a hash while an integer part of a title id
* ver_hash is always a jenkins hash of version string, both platforms have this thing
* ver_code is a package version code on Android, on PSP this is a WORD where lower byte is a minor version and higher is a major version of a title.

`0DDC=2,set_mutex_var %1d% to %2d%`

`0DDD=2,%1d% = get_mutex_var %2d%`

Mutex vars are being used as global variables between scripts, mutex id can be any integer value, for example all scripts that use GUI use mutex variable with id 0 which indicates the state of anything being onscreen, if it's value is 0 then script can show GUI, if script is about to show GUI then it sets this var to 1. If mutex variable isn't set then 0 is returned.

`0DDE=-1, call_func %1d% add_ib %2d%`

Calls a game function using specified address, if add_ib is set to 1 then adds an imagebase. Pairs of ['type', value] follow and indicate with which result type and params this function must be called. Specifying result is optional, just as specifing params if function has none.
Type can be one of these: 
'i' - integer param
'f' - float param
'ref' - passes a reference to a variable as param
'resi' - result of integer type
'resf' - result of float type
Let's look how this one works on a simple example:
0DDE: call_func 2@ add_ib 0 __result 'resi' 0@ __pad_index 'i' 0
Here we are performing a call to a function which absolute address is stored in 2@, this is why we don't need to add an imagebase here, so add_ib is set to 0, this function returns integer which get's stored in 0@ and takes one integer param which is set to 0, can be a variable instead if required.

`0DE0=3,%1d% = get_touch_point_state %2d% mintime %3d%`

`0DE1=5,%1d% = get_touch_slide_state from %2d% to %3d% mintime %4d% maxtime %5d%`

Returns result of the requested touch action check, can be 0 or 1. On PSP always returns 0. Touch points is the CLEO PSP engine implemented touch detection system which divides touchscreen into 9 parts called touch points, they can be used to detect timed slides and touches.

Touch point ids:

```
#1 LEFT-TOP     #4 CENTER-TOP     #7 RIGHT-TOP
#2 LEFT-CENTER  #5 CENTER         #8 RIGHT-CENTER
#3 LEFT-BOTTOM  #6 CENTER-BOTTOM  #9 RIGHT-BOTTOM
```

`0DE2=1,%1d% = get_menu_button_state`

`0DE3=2,%1d% = get_menu_button_pressed mintime %2d%`

Returns state of the Android hardware menu button, can be 0 or 1, a lot of devices have no button like this. On PSP always returns 0.

`0DE4=2,%1d% = psp_get_control_state %2d%`

`0DE5=3,%1d% = psp_get_control_pressed %2d% mintime %3d%`

Returns state of the PSP control, can be 0 or 1. On Android always returns 0.
enum ePspControl { 
    SELECT = 0, UP, RIGHT, DOWN, LEFT, LTRIGGER, RTRIGGER, 
    TRIANGLE, CIRCLE, CROSS, SQUARE, HOLD, 
    STICK_UP, STICK_DOWN, STICK_RIGHT, STICK_LEFT
}

`0DF2=2,create_menu %1d% items %2d%`

Creates the menu gui which handles most of the things like drawing and input automatically. With first param being a label like @menu_desc where you describe the menu and second param indicating menu item count, can be set to a higher value than actual items if the menu has last item described as 00 byte. On Android the menu is touch based while on PSP uses controls. To get the point see the example scripts.
Menu flags go as following:

```
enum eMenuFlags
{
    // item names are considered being gxt/fxt entries, if no such entry exists then
    // item name is the name which will be displayed in the menu
    USE_GXT	 = 1 << 0,	
    
    // if gxt/fxt entry won't fit the menu bounds then text will be end-trimmed,
    // sizes: III, VC, SA = 20, LCS = 18, VCS = 19
    TRIM_GXT = 1 << 1
}
```

`0DF3=0,delete_menu`

Removes active menu.

`0DF4=2,%1d% = get_menu_touched_item_index maxtime %2d%`

Returns 0-based menu touched item index if condition is met, on PSP returns selected item index which is the same, if no item was touched or selected then the result is -1, if menu has to be closed then the result is -2.

`0DF5=1,set_menu_active_item_index %1d%`

`0DF6=1,%1d% = get_menu_active_item_index`

Gets and sets active menu index with scrolling menu pages if necessary, on Android this involves only menu pages while on PSP also sets last active item on the corresponding page. Mostly used in order to pass menu states between different launches of the same *.csi script which uses a menu.

`1000=-1, opcode_func`

Opcode function, see plugins section for the details.

Plugins
CLEO PSP provides an ability to load custom library plugins (*.prx) and implements the API which allows to add new opcodes for all games at once, i.e. using single code base. Additionally the API provides basic necessary abilities to simplify an access to the game internals, e.g. allows to perform arm/thumb/mips function hooking.
Plugins allow to add new opcodes just as to add opcode functions, which pretty much are name-based opcodes. In order to be called opcode functions are using single script opcode 1000. Name param which is the first param of the opcode is a long string for III/VC/SA, in LCS/VCS name is represented as a set of 8byte strings with trailing parentheses, the rest of the params rely on opcode function implementation. See plugin example for the details.


  
