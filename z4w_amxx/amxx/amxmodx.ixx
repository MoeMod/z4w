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

	std::string get_user_name(int id)
	{
		return MF_GetPlayerName(id);
	}

	void client_cmd(int index, const char* command)
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
}