module;
#include "amxxmodule.h"

export module amxxmodule;


export namespace amxxmodule {
	using ucell = ::ucell;
	using cell = ::cell;

	// *** Types ***
	typedef void* (*PFN_REQ_FNPTR)(const char* /*name*/);

	// ***** Module funcs stuff *****
	enum ForwardExecType
	{
		ET_IGNORE = 0,					// Ignore return vaue
		ET_STOP,						// Stop on PLUGIN_HANDLED
		ET_STOP2,						// Stop on PLUGIN_HANDLED, continue on other values, return biggest return value
		ET_CONTINUE,					// Continue; return biggest return value
	};

	enum ForwardParam
	{
		FP_DONE = -1,					// specify this as the last argument only tells the function that there are no more arguments
		FP_CELL,						// normal cell
		FP_FLOAT,						// float; used as normal cell though
		FP_STRING,						// string
		FP_STRINGEX,					// string; will be updated to the last function's value
		FP_ARRAY,						// array; use the return value of prepareArray.
	};

	enum PlayerProp
	{
		Player_Name,		//String
		Player_Ip,			//String
		Player_Team,		//String
		Player_Ingame,		//bool
		Player_Authorized,	//bool
		Player_Vgui,		//bool
		Player_Time,		//float
		Player_Playtime,	//float
		Player_MenuExpire,	//float
		Player_Weapons,		//struct{int,int}[32]
		Player_CurrentWeapon,	//int
		Player_TeamID,			//int
		Player_Deaths,			//int
		Player_Aiming,			//int
		Player_Menu,			//int
		Player_Keys,			//int
		Player_Flags,			//int[32]
		Player_Newmenu,			//int
		Player_NewmenuPage,		//int
	};

	enum LibType
	{
		LibType_Library,
		LibType_Class
	};

	constexpr auto MSGBLOCK_SET = 0;
	constexpr auto MSGBLOCK_GET = 1;
	constexpr auto BLOCK_NOT = 0;
	constexpr auto BLOCK_ONCE = 1;
	constexpr auto BLOCK_SET = 2;

	typedef void (*AUTHORIZEFUNC)(int player, const char* authstring);

	typedef int				(*PFN_ADD_NATIVES)				(const AMX_NATIVE_INFO* /*list*/);
	typedef int				(*PFN_ADD_NEW_NATIVES)			(const AMX_NATIVE_INFO* /*list*/);
	typedef char* (*PFN_BUILD_PATHNAME)			(const char* /*format*/, ...);
	typedef char* (*PFN_BUILD_PATHNAME_R)			(char* /*buffer*/, size_t /* maxlen */, const char* /* format */, ...);
	typedef cell* (*PFN_GET_AMXADDR)				(AMX* /*amx*/, cell /*offset*/);
	typedef void			(*PFN_PRINT_SRVCONSOLE)			(const char* /*format*/, ...);
	typedef const char* (*PFN_GET_MODNAME)				(void);
	typedef const char* (*PFN_GET_AMXSCRIPTNAME)		(int /*id*/);
	typedef AMX* (*PFN_GET_AMXSCRIPT)			(int /*id*/);
	typedef int				(*PFN_FIND_AMXSCRIPT_BYAMX)		(const AMX* /*amx*/);
	typedef int				(*PFN_FIND_AMXSCRIPT_BYNAME)	(const char* /*name*/);
	typedef int				(*PFN_SET_AMXSTRING)			(AMX* /*amx*/, cell /*amx_addr*/, const char* /* source */, int /* max */);
	typedef char* (*PFN_GET_AMXSTRING)			(AMX* /*amx*/, cell /*amx_addr*/, int /*bufferId*/, int* /*pLen*/);
	typedef int				(*PFN_GET_AMXSTRINGLEN)			(const cell* ptr);
	typedef char* (*PFN_FORMAT_AMXSTRING)			(AMX* /*amx*/, cell* /*params*/, int /*startParam*/, int* /*pLen*/);
	typedef void			(*PFN_COPY_AMXMEMORY)			(cell* /*dest*/, const cell* /*src*/, int /*len*/);
	typedef void			(*PFN_LOG)						(const char* /*fmt*/, ...);
	typedef void			(*PFN_LOG_ERROR)				(AMX* /*amx*/, int /*err*/, const char* /*fmt*/, ...);
	typedef int				(*PFN_RAISE_AMXERROR)			(AMX* /*amx*/, int /*error*/);
	typedef int				(*PFN_REGISTER_FORWARD)			(const char* /*funcname*/, ForwardExecType /*exectype*/, ... /*paramtypes terminated by PF_DONE*/);
	typedef int				(*PFN_EXECUTE_FORWARD)			(int /*id*/, ... /*params*/);
	typedef cell(*PFN_PREPARE_CELLARRAY)		(cell* /*ptr*/, unsigned int /*size*/);
	typedef cell(*PFN_PREPARE_CHARARRAY)		(char* /*ptr*/, unsigned int /*size*/);
	typedef cell(*PFN_PREPARE_CELLARRAY_A)		(cell* /*ptr*/, unsigned int /*size*/, bool /*copyBack*/);
	typedef cell(*PFN_PREPARE_CHARARRAY_A)		(char* /*ptr*/, unsigned int /*size*/, bool /*copyBack*/);
	typedef int				(*PFN_IS_PLAYER_VALID)			(int /*id*/);
	typedef const char* (*PFN_GET_PLAYER_NAME)			(int /*id*/);
	typedef const char* (*PFN_GET_PLAYER_IP)			(int /*id*/);
	typedef int				(*PFN_IS_PLAYER_INGAME)			(int /*id*/);
	typedef int				(*PFN_IS_PLAYER_BOT)			(int /*id*/);
	typedef int				(*PFN_IS_PLAYER_AUTHORIZED)		(int /*id*/);
	typedef float			(*PFN_GET_PLAYER_TIME)			(int /*id*/);
	typedef float			(*PFN_GET_PLAYER_PLAYTIME)		(int /*id*/);
	typedef int				(*PFN_GETPLAYERFLAGS) 			(int /* id*/);
	typedef int				(*PFN_GET_PLAYER_CURWEAPON)		(int /*id*/);
	typedef const char* (*PFN_GET_PLAYER_TEAM)			(int /*id*/);
	typedef int				(*PFN_GET_PLAYER_TEAMID)		(int /*id*/);
	typedef int				(*PFN_GET_PLAYER_DEATHS)		(int /*id*/);
	typedef int				(*PFN_GET_PLAYER_MENU)			(int /*id*/);
	typedef int				(*PFN_GET_PLAYER_KEYS)			(int /*id*/);
	typedef int				(*PFN_IS_PLAYER_ALIVE)			(int /*id*/);
	typedef int				(*PFN_GET_PLAYER_FRAGS)			(int /*id*/);
	typedef int				(*PFN_IS_PLAYER_CONNECTING)		(int /*id*/);
	typedef int				(*PFN_IS_PLAYER_HLTV)			(int /*id*/);
	typedef int				(*PFN_GET_PLAYER_ARMOR)			(int /*id*/);
	typedef int				(*PFN_GET_PLAYER_HEALTH)		(int /*id*/);
#ifdef USE_METAMOD
	typedef edict_t* (*PFN_GET_PLAYER_EDICT)			(int /*id*/);
#else
	typedef void* (*PFN_GET_PLAYER_EDICT)			(int /*id*/);
#endif
	typedef void* (*PFN_PLAYER_PROP_ADDR)			(int /*id*/, int /*prop*/);
	typedef int				(*PFN_AMX_EXEC)					(AMX* /*amx*/, cell* /*return val*/, int /*index*/);
	typedef int				(*PFN_AMX_EXECV)				(AMX* /*amx*/, cell* /*return val*/, int /*index*/, int /*numparams*/, cell[] /*params*/);
	typedef int				(*PFN_AMX_ALLOT)				(AMX* /*amx*/, int /*length*/, cell* /*amx_addr*/, cell** /*phys_addr*/);
	typedef int				(*PFN_AMX_FINDPUBLIC)			(AMX* /*amx*/, char* /*func name*/, int* /*index*/);
	typedef int				(*PFN_AMX_FINDNATIVE)			(AMX* /*amx*/, char* /*func name*/, int* /*index*/);
	typedef int				(*PFN_LOAD_AMXSCRIPT)			(AMX* /*amx*/, void** /*code*/, const char* /*path*/, char[64] /*error info*/, int /* debug */);
	typedef int				(*PFN_UNLOAD_AMXSCRIPT)			(AMX* /*amx*/, void** /*code*/);
	typedef cell(*PFN_REAL_TO_CELL)				(REAL /*x*/);
	typedef REAL(*PFN_CELL_TO_REAL)				(cell /*x*/);
	typedef int				(*PFN_REGISTER_SPFORWARD)		(AMX* /*amx*/, int /*func*/, ... /*params*/);
	typedef int				(*PFN_REGISTER_SPFORWARD_BYNAME)	(AMX* /*amx*/, const char* /*funcName*/, ... /*params*/);
	typedef void			(*PFN_UNREGISTER_SPFORWARD)		(int /*id*/);
	typedef	void			(*PFN_MERGEDEFINITION_FILE)		(const char* /*filename*/);
	typedef const char* (*PFN_FORMAT)					(const char* /*fmt*/, ... /*params*/);
	typedef void			(*PFN_REGISTERFUNCTION)			(void* /*pfn*/, const char* /*desc*/);
	typedef	int				(*PFN_AMX_PUSH)					(AMX* /*amx*/, cell /*value*/);
	typedef	int				(*PFN_SET_TEAM_INFO)			(int /*player */, int /*teamid */, const char* /*name */);
	typedef void			(*PFN_REG_AUTH_FUNC)			(AUTHORIZEFUNC);
	typedef void			(*PFN_UNREG_AUTH_FUNC)			(AUTHORIZEFUNC);
	typedef int				(*PFN_FINDLIBRARY)				(const char* /*name*/, LibType /*type*/);
	typedef size_t(*PFN_ADDLIBRARIES)				(const char* /*name*/, LibType /*type*/, void* /*parent*/);
	typedef size_t(*PFN_REMOVELIBRARIES)			(void* /*parent*/);
	typedef void			(*PFN_OVERRIDENATIVES)			(AMX_NATIVE_INFO* /*natives*/, const char* /*myname*/);
	typedef const char* (*PFN_GETLOCALINFO)				(const char* /*name*/, const char* /*def*/);
	typedef int				(*PFN_AMX_REREGISTER)			(AMX* /*amx*/, AMX_NATIVE_INFO* /*list*/, int /*list*/);
	typedef void* (*PFN_REGISTERFUNCTIONEX)		(void* /*pfn*/, const char* /*desc*/);
	typedef void			(*PFN_MESSAGE_BLOCK)			(int /* mode */, int /* message */, int* /* opt */);

	PFN_ADD_NATIVES				g_fn_AddNatives;
	PFN_ADD_NEW_NATIVES			g_fn_AddNewNatives;
	PFN_BUILD_PATHNAME			g_fn_BuildPathname;
	PFN_BUILD_PATHNAME_R			g_fn_BuildPathnameR;
	PFN_GET_AMXADDR				g_fn_GetAmxAddr;
	PFN_PRINT_SRVCONSOLE			g_fn_PrintSrvConsole;
	PFN_GET_MODNAME				g_fn_GetModname;
	PFN_GET_AMXSCRIPTNAME		g_fn_GetAmxScriptName;
	PFN_GET_AMXSCRIPT			g_fn_GetAmxScript;
	PFN_FIND_AMXSCRIPT_BYAMX		g_fn_FindAmxScriptByAmx;
	PFN_FIND_AMXSCRIPT_BYNAME	g_fn_FindAmxScriptByName;
	PFN_SET_AMXSTRING			g_fn_SetAmxString;
	PFN_GET_AMXSTRING			g_fn_GetAmxString;
	PFN_GET_AMXSTRINGLEN			g_fn_GetAmxStringLen;
	PFN_FORMAT_AMXSTRING			g_fn_FormatAmxString;
	PFN_COPY_AMXMEMORY			g_fn_CopyAmxMemory;
	PFN_LOG						g_fn_Log;
	PFN_LOG_ERROR				g_fn_LogErrorFunc;
	PFN_RAISE_AMXERROR			g_fn_RaiseAmxError;
	PFN_REGISTER_FORWARD			g_fn_RegisterForward;
	PFN_EXECUTE_FORWARD			g_fn_ExecuteForward;
	PFN_PREPARE_CELLARRAY		g_fn_PrepareCellArray;
	PFN_PREPARE_CHARARRAY		g_fn_PrepareCharArray;
	PFN_PREPARE_CELLARRAY_A		g_fn_PrepareCellArrayA;
	PFN_PREPARE_CHARARRAY_A		g_fn_PrepareCharArrayA;
	PFN_IS_PLAYER_VALID			g_fn_IsPlayerValid;
	PFN_GET_PLAYER_NAME			g_fn_GetPlayerName;
	PFN_GET_PLAYER_IP			g_fn_GetPlayerIP;
	PFN_IS_PLAYER_INGAME			g_fn_IsPlayerIngame;
	PFN_IS_PLAYER_BOT			g_fn_IsPlayerBot;
	PFN_IS_PLAYER_AUTHORIZED		g_fn_IsPlayerAuthorized;
	PFN_GET_PLAYER_TIME			g_fn_GetPlayerTime;
	PFN_GET_PLAYER_PLAYTIME		g_fn_GetPlayerPlayTime;
	PFN_GET_PLAYER_CURWEAPON		g_fn_GetPlayerCurweapon;
	PFN_GET_PLAYER_TEAMID		g_fn_GetPlayerTeamID;
	PFN_GET_PLAYER_DEATHS		g_fn_GetPlayerDeaths;
	PFN_GET_PLAYER_MENU			g_fn_GetPlayerMenu;
	PFN_GET_PLAYER_KEYS			g_fn_GetPlayerKeys;
	PFN_IS_PLAYER_ALIVE			g_fn_IsPlayerAlive;
	PFN_GET_PLAYER_FRAGS			g_fn_GetPlayerFrags;
	PFN_IS_PLAYER_CONNECTING		g_fn_IsPlayerConnecting;
	PFN_IS_PLAYER_HLTV			g_fn_IsPlayerHLTV;
	PFN_GET_PLAYER_ARMOR			g_fn_GetPlayerArmor;
	PFN_GET_PLAYER_HEALTH		g_fn_GetPlayerHealth;
	PFN_AMX_EXEC					g_fn_AmxExec;
	PFN_AMX_EXECV				g_fn_AmxExecv;
	PFN_AMX_ALLOT				g_fn_AmxAllot;
	PFN_AMX_FINDPUBLIC			g_fn_AmxFindPublic;
	PFN_LOAD_AMXSCRIPT			g_fn_LoadAmxScript;
	PFN_UNLOAD_AMXSCRIPT			g_fn_UnloadAmxScript;
	PFN_REAL_TO_CELL				g_fn_RealToCell;
	PFN_CELL_TO_REAL				g_fn_CellToReal;
	PFN_REGISTER_SPFORWARD		g_fn_RegisterSPForward;
	PFN_REGISTER_SPFORWARD_BYNAME	g_fn_RegisterSPForwardByName;
	PFN_UNREGISTER_SPFORWARD		g_fn_UnregisterSPForward;
	PFN_MERGEDEFINITION_FILE		g_fn_MergeDefinition_File;
	PFN_AMX_FINDNATIVE			g_fn_AmxFindNative;
	PFN_GETPLAYERFLAGS		g_fn_GetPlayerFlags;
	PFN_GET_PLAYER_EDICT			g_fn_GetPlayerEdict;
	PFN_FORMAT					g_fn_Format;
	PFN_GET_PLAYER_TEAM			g_fn_GetPlayerTeam;
	PFN_REGISTERFUNCTION			g_fn_RegisterFunction;
	PFN_REQ_FNPTR				g_fn_RequestFunction;
	PFN_AMX_PUSH					g_fn_AmxPush;
	PFN_SET_TEAM_INFO			g_fn_SetTeamInfo;
	PFN_PLAYER_PROP_ADDR			g_fn_PlayerPropAddr;
	PFN_REG_AUTH_FUNC			g_fn_RegAuthFunc;
	PFN_UNREG_AUTH_FUNC			g_fn_UnregAuthFunc;
	PFN_FINDLIBRARY				g_fn_FindLibrary;
	PFN_ADDLIBRARIES				g_fn_AddLibraries;
	PFN_REMOVELIBRARIES			g_fn_RemoveLibraries;
	PFN_OVERRIDENATIVES			g_fn_OverrideNatives;
	PFN_GETLOCALINFO				g_fn_GetLocalInfo;
	PFN_AMX_REREGISTER			g_fn_AmxReRegister;
	PFN_REGISTERFUNCTIONEX		g_fn_RegisterFunctionEx;
	PFN_MESSAGE_BLOCK			g_fn_MessageBlock;

	auto& MF_AddNatives = g_fn_AddNatives;
	auto& MF_AddNewNatives = g_fn_AddNewNatives;
	auto& MF_BuildPathname = g_fn_BuildPathname;
	auto& MF_BuildPathnameR = g_fn_BuildPathnameR;
	auto& MF_FormatAmxString = g_fn_FormatAmxString;
	auto& MF_GetAmxAddr = g_fn_GetAmxAddr;
	auto& MF_PrintSrvConsole = g_fn_PrintSrvConsole;
	auto& MF_GetModname = g_fn_GetModname;
	auto& MF_GetScriptName = g_fn_GetAmxScriptName;
	auto& MF_GetScriptAmx = g_fn_GetAmxScript;
	auto& MF_FindScriptByAmx = g_fn_FindAmxScriptByAmx;
	auto& MF_FindScriptByName = g_fn_FindAmxScriptByName;
	auto& MF_SetAmxString = g_fn_SetAmxString;
	auto& MF_GetAmxString = g_fn_GetAmxString;
	auto& MF_GetAmxStringLen = g_fn_GetAmxStringLen;
	auto& MF_CopyAmxMemory = g_fn_CopyAmxMemory;
	auto& MF_Log = g_fn_Log;
	auto& MF_LogError = g_fn_LogErrorFunc;
	auto& MF_RaiseAmxError = g_fn_RaiseAmxError;
	auto& MF_RegisterForward = g_fn_RegisterForward;
	auto& MF_ExecuteForward = g_fn_ExecuteForward;
	auto& MF_PrepareCellArray = g_fn_PrepareCellArray;
	auto& MF_PrepareCharArray = g_fn_PrepareCharArray;
	auto& MF_PrepareCellArrayA = g_fn_PrepareCellArrayA;
	auto& MF_PrepareCharArrayA = g_fn_PrepareCharArrayA;
	auto& MF_IsPlayerValid = g_fn_IsPlayerValid;
	auto& MF_GetPlayerName = g_fn_GetPlayerName;
	auto& MF_GetPlayerIP = g_fn_GetPlayerIP;
	auto& MF_IsPlayerIngame = g_fn_IsPlayerIngame;
	auto& MF_IsPlayerBot = g_fn_IsPlayerBot;
	auto& MF_IsPlayerAuthorized = g_fn_IsPlayerAuthorized;
	auto& MF_GetPlayerTime = g_fn_GetPlayerTime;
	auto& MF_GetPlayerPlayTime = g_fn_GetPlayerPlayTime;
	auto& MF_GetPlayerCurweapon = g_fn_GetPlayerCurweapon;
	auto& MF_GetPlayerTeam = g_fn_GetPlayerTeam;
	auto& MF_GetPlayerTeamID = g_fn_GetPlayerTeamID;
	auto& MF_GetPlayerDeaths = g_fn_GetPlayerDeaths;
	auto& MF_GetPlayerMenu = g_fn_GetPlayerMenu;
	auto& MF_GetPlayerKeys = g_fn_GetPlayerKeys;
	auto& MF_IsPlayerAlive = g_fn_IsPlayerAlive;
	auto& MF_GetPlayerFrags = g_fn_GetPlayerFrags;
	auto& MF_IsPlayerConnecting = g_fn_IsPlayerConnecting;
	auto& MF_IsPlayerHLTV = g_fn_IsPlayerHLTV;
	auto& MF_GetPlayerArmor = g_fn_GetPlayerArmor;
	auto& MF_GetPlayerHealth = g_fn_GetPlayerHealth;
	auto& MF_AmxExec = g_fn_AmxExec;
	auto& MF_AmxExecv = g_fn_AmxExecv;
	auto& MF_AmxFindPublic = g_fn_AmxFindPublic;
	auto& MF_AmxAllot = g_fn_AmxAllot;
	auto& MF_AmxFindNative = g_fn_AmxFindNative;
	auto& MF_LoadAmxScript = g_fn_LoadAmxScript;
	auto& MF_UnloadAmxScript = g_fn_UnloadAmxScript;
	auto& MF_MergeDefinitionFile = g_fn_MergeDefinition_File;
	auto& amx_ctof = g_fn_CellToReal;
	auto& amx_ftoc = g_fn_RealToCell;
	auto& MF_RegisterSPForwardByName = g_fn_RegisterSPForwardByName;
	auto& MF_RegisterSPForward = g_fn_RegisterSPForward;
	auto& MF_UnregisterSPForward = g_fn_UnregisterSPForward;
	auto& MF_GetPlayerFlags = g_fn_GetPlayerFlags;
	auto& MF_GetPlayerEdict = g_fn_GetPlayerEdict;
	auto& MF_Format = g_fn_Format;
	auto& MF_RegisterFunction = g_fn_RegisterFunction;
	auto& MF_RequestFunction = g_fn_RequestFunction;
	auto& MF_AmxPush = g_fn_AmxPush;
	auto& MF_SetPlayerTeamInfo = g_fn_SetTeamInfo;
	auto& MF_PlayerPropAddr = g_fn_PlayerPropAddr;
	auto& MF_RegAuthFunc = g_fn_RegAuthFunc;
	auto& MF_UnregAuthFunc = g_fn_UnregAuthFunc;
	auto& MF_FindLibrary = g_fn_FindLibrary;
	auto& MF_AddLibraries = g_fn_AddLibraries;
	auto& MF_RemoveLibraries = g_fn_RemoveLibraries;
	auto& MF_OverrideNatives = g_fn_OverrideNatives;
	auto& MF_GetLocalInfo = g_fn_GetLocalInfo;
	auto& MF_AmxReRegister = g_fn_AmxReRegister;
	auto& MF_RegisterFunctionEx = g_fn_RegisterFunctionEx;
	auto& MF_MessageBlock = g_fn_MessageBlock;
}