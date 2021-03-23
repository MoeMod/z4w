// vi: set ts=4 sw=4 :
// vim: set tw=75 :

// meta_api.h - description of metamod's DLL interface

/*
 * Copyright (c) 2001-2003 Will Day <willday@hpgx.net>
 *
 *    This file is part of Metamod.
 *
 *    Metamod is free software; you can redistribute it and/or modify it
 *    under the terms of the GNU General Public License as published by the
 *    Free Software Foundation; either version 2 of the License, or (at
 *    your option) any later version.
 *
 *    Metamod is distributed in the hope that it will be useful, but
 *    WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with Metamod; if not, write to the Free Software Foundation,
 *    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *    In addition, as a special exception, the author gives permission to
 *    link the code of this program with the Half-Life Game Engine ("HL
 *    Engine") and Modified Game Libraries ("MODs") developed by Valve,
 *    L.L.C ("Valve").  You must obey the GNU General Public License in all
 *    respects for all of the code used other than the HL Engine and MODs
 *    from Valve.  If you modify this file, you may extend this exception
 *    to your version of the file, but you are not obligated to do so.  If
 *    you do not wish to do so, delete this exception statement from your
 *    version.
 *
 */

#pragma once

#include "dllapi_fwd.h"				// GETENTITYAPI_FN, etc
#include "engine_api_fwd.h"			// GET_ENGINE_FUNCTIONS_FN, etc
#include "plinfo.h"				// plugin_info_t, etc
#include "mutil.h"				// mutil_funcs_t, etc

// Version consists of "major:minor", two separate integer numbers.
// Version 1	original
// Version 2	added plugin_info_t **pinfo
// Version 3	init split into query and attach, added detach
// Version 4	added (PLUG_LOADTIME now) to attach
// Version 5	changed mm ifvers int* to string, moved pl ifvers to info
// Version 5:1	added link support for entity "adminmod_timer" (adminmod)
// Version 5:2	added gamedll_funcs to meta_attach() [v1.0-rc2]
// Version 5:3	added mutil_funcs to meta_query() [v1.05]
// Version 5:4	added centersay utility functions [v1.06]
// Version 5:5	added Meta_Init to plugin API [v1.08]
// Version 5:6	added CallGameEntity utility function [v1.09]
// Version 5:7	added GetUserMsgID, GetUserMsgName util funcs [v1.11]
// Version 5:8	added GetPluginPath [v1.11]
// Version 5:9	added GetGameInfo [v1.14]
// Version 5:10 added GINFO_REALDLL_FULLPATH for GetGameInfo [v1.17]
// Version 5:11 added plugin loading and unloading API [v1.18]
// Version 5:12 added util code for checking player query status [v1.18]
// Version 5:13 added cvarquery2 support and api for calling hook tables [v1.19]
constexpr const char* META_INTERFACE_VERSION = "5:13";

// Flags returned by a plugin's api function.
// NOTE: order is crucial, as greater/less comparisons are made.
typedef enum {
	MRES_UNSET = 0,
	MRES_IGNORED,		// plugin didn't take any action
	MRES_HANDLED,		// plugin did something, but real function should still be called
	MRES_OVERRIDE,		// call real function, but use my return value
	MRES_SUPERCEDE,		// skip real function; use my return value
} META_RES;

// Variables provided to plugins.
typedef struct meta_globals_s {
	META_RES mres;			// writable; plugin's return flag
	META_RES prev_mres;		// readable; return flag of the previous plugin called
	META_RES status;		// readable; "highest" return flag so far
	void *orig_ret;			// readable; return value from "real" function
	void *override_ret;		// readable; return value from overriding/superceding plugin
} meta_globals_t;

extern meta_globals_t *gpMetaGlobals;
#define SET_META_RESULT(result)			gpMetaGlobals->mres=result
#define RETURN_META(result) \
	do { gpMetaGlobals->mres=result; return; } while(0)
#define RETURN_META_VALUE(result, value) \
	do { gpMetaGlobals->mres=result; return(value); } while(0)
#define META_RESULT_STATUS				gpMetaGlobals->status
#define META_RESULT_PREVIOUS			gpMetaGlobals->prev_mres
#define META_RESULT_ORIG_RET(type)		*(type *)gpMetaGlobals->orig_ret
#define META_RESULT_OVERRIDE_RET(type)	*(type *)gpMetaGlobals->override_ret

// Table of getapi functions, retrieved from each plugin.
typedef struct {
	GETENTITYAPI_FN         pfnGetEntityAPI;
	GETENTITYAPI_FN         pfnGetEntityAPI_Post;
	GETENTITYAPI2_FN        pfnGetEntityAPI2;
	GETENTITYAPI2_FN        pfnGetEntityAPI2_Post;
	GETNEWDLLFUNCTIONS_FN   pfnGetNewDLLFunctions;
	GETNEWDLLFUNCTIONS_FN   pfnGetNewDLLFunctions_Post;
	GET_ENGINE_FUNCTIONS_FN pfnGetEngineFunctions;
	GET_ENGINE_FUNCTIONS_FN pfnGetEngineFunctions_Post;
} META_FUNCTIONS;

// Pair of function tables provided by game DLL.
typedef struct {
	DLL_FUNCTIONS *dllapi_table;
	NEW_DLL_FUNCTIONS *newapi_table;
} gamedll_funcs_t;

// Declared in plugin; referenced in macros.
extern gamedll_funcs_t *gpGamedllFuncs;
extern mutil_funcs_t *gpMetaUtilFuncs;

// Tell the dll that we'll be loading it as a metamod plugin, in case it
// needs to do something special prior to the standard query/attach
// procedure.  In particular, this will allow for DLL's that can be used as
// both standalone DLL's and metamod plugins. (optional; not required in
// plugin)
C_DLLEXPORT void Meta_Init(void);
typedef void (*META_INIT_FN) (void);

// Get info about plugin, compare meta_interface versions, provide meta
// utility callback functions.
C_DLLEXPORT int Meta_Query(char *interfaceVersion, 
		plugin_info_t **plinfo, 
		mutil_funcs_t *pMetaUtilFuncs);
typedef int (*META_QUERY_FN) (char *interfaceVersion, 
		plugin_info_t **plinfo, 
		mutil_funcs_t *pMetaUtilFuncs);

// Attach the plugin to the API; get the table of getapi functions; give 
// meta_globals and gamedll_funcs.
C_DLLEXPORT int Meta_Attach(PLUG_LOADTIME now, 
		META_FUNCTIONS *pFunctionTable, 
		meta_globals_t *pMGlobals, 
		gamedll_funcs_t *pGamedllFuncs);
typedef int (*META_ATTACH_FN) (PLUG_LOADTIME now, 
		META_FUNCTIONS *pFunctionTable, 
		meta_globals_t *pMGlobals, 
		gamedll_funcs_t *pGamedllFuncs);

// Detach the plugin; tell why and when.
C_DLLEXPORT int Meta_Detach(PLUG_LOADTIME now, PL_UNLOAD_REASON reason);
typedef int (*META_DETACH_FN) (PLUG_LOADTIME now, PL_UNLOAD_REASON reason);

// Standard HL SDK interface function prototypes.
C_DLLEXPORT int GetEntityAPI_Post(DLL_FUNCTIONS *pFunctionTable, 
		int interfaceVersion );
C_DLLEXPORT int GetEntityAPI2_Post(DLL_FUNCTIONS *pFunctionTable, 
		int *interfaceVersion );

// Additional SDK-like interface function prototypes.
C_DLLEXPORT int GetNewDLLFunctions_Post(NEW_DLL_FUNCTIONS *pNewFunctionTable, 
		int *interfaceVersion );
C_DLLEXPORT int GetEngineFunctions(enginefuncs_t *pengfuncsFromEngine, 
		int *interfaceVersion);
C_DLLEXPORT int GetEngineFunctions_Post(enginefuncs_t *pengfuncsFromEngine, 
		int *interfaceVersion);
