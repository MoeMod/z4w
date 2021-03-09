module;

#include <algorithm>
#include <chrono>
#include <string>
#include <stdarg.h>

export module amxx.amxmodx;

import hlsdk.extdll;
import hlsdk.util;
export import amxx.message_const;
export import amxx.amxconst;
export import amxx.hudmessage;
export import amxx.dhudmessage;
export import amxx.amxmodx_timer;
export import amxx.convert;
import amxxmodule;

using namespace hlsdk;
using namespace amxxmodule;

export namespace amxx {
	using hlsdk::EngineClock;

	using namespace std::chrono_literals;

	time_point_t get_gametime()
	{
		return EngineClock::now();
	}

	std::string get_user_name(auto_ent<int> id)
	{
		return MF_GetPlayerName(id);
	}

	void client_cmd(auto_ent<int> index, const char* command)
	{
		if (!index)
		{
			for (int i = 0; i <= gpGlobals->maxClients; ++i)
			{
				if (MF_IsPlayerValid(i) && !MF_IsPlayerBot(i))
				{
					edict_t* client = MF_GetPlayerEdict(i);
					CLIENT_COMMAND(client, "%s\n", command);
				}
			}
		}
		else
		{
			if (index < 1 || index > gpGlobals->maxClients)
			{
				//LogError(amx, AMX_ERR_NATIVE, "Invalid player id %d", index);
				return;
			}
			if (MF_IsPlayerValid(index) && !MF_IsPlayerBot(index))
			{
				edict_t* client = MF_GetPlayerEdict(index);
				CLIENT_COMMAND(client, "%s\n", command);
			}
		}
	}

	bool is_map_valid(const char *map)
	{
		return IS_MAP_VALID(map);
	}

	bool is_user_connected(auto_ent<int> id)
	{
		return MF_IsPlayerIngame(id);
	}

	bool is_user_connecting(auto_ent<int> id)
	{
		return !MF_IsPlayerIngame(id) && MF_IsPlayerValid(id) && (GETPLAYERUSERID(ent_cast<edict_t *>(id)) > 0);
	}

	bool is_user_bot(auto_ent<int> id)
	{
		return MF_IsPlayerBot(id);
	}

	bool is_user_authorized(auto_ent<int> id)
	{
		return MF_IsPlayerAuthorized(id);
	}

	bool is_user_alive(auto_ent<int> id)
	{
		int index = id.value;
		if (index < 1 || index > gpGlobals->maxClients)
			return false;
		if (!is_user_connected(id))
			return false;
		return MF_IsPlayerAlive(id);
	}
}