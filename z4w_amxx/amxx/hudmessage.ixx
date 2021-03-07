module;

#include <algorithm>
#include <chrono>
#include <stdarg.h>

export module amxx.hudmessage;

import hlsdk.enginecallback;
import hlsdk.util;
import amxx.message_const;
import amxx.amxmodx_util;
import amxxmodule;

using namespace hlsdk;
using namespace amxxmodule;
using namespace std::chrono_literals;

hudtextparms_t g_hudset;

export namespace amxx {
	void set_hudmessage(int red = 200, int green = 100, int blue = 0, float x = -1.0, float y = 0.35, int effects = 0, duration_t fxtime = 6.0s, duration_t holdtime = 12.0s, duration_t fadeintime = 0.1s, duration_t fadeouttime = 0.2s, int channel = 4) /* 11 param */
	{
		g_hudset.a1 = 0;
		g_hudset.a2 = 0;
		g_hudset.r2 = 255;
		g_hudset.g2 = 255;
		g_hudset.b2 = 250;
		g_hudset.r1 = static_cast<byte>(red);
		g_hudset.g1 = static_cast<byte>(green);
		g_hudset.b1 = static_cast<byte>(blue);
		g_hudset.x = x;
		g_hudset.y = y;
		g_hudset.effect = effects;
		g_hudset.fxTime = fxtime;
		g_hudset.holdTime = holdtime;
		g_hudset.fadeinTime = fadeintime;
		g_hudset.fadeoutTime = fadeouttime;
		g_hudset.channel = channel;

	}

	int NextHUDChannel(int* channels)
	{
		int ilow = 1;

		for (int i = ilow + 1; i <= 4; i++)
		{
			if (channels[i] < channels[ilow])
				ilow = i;
		}

		return ilow;
	}

	int send_hudmessage(int index, const char *message) /* 2 param */
	{
		int len = 0;

		/**
		 * Earlier versions would ignore invalid bounds.
		 * Now, bounds are only checked for internal operations.
		 *  "channel" stores the valid channel that core uses.
		 *  "g_hudset.channel" stores the direct channel passed to the engine.
		 */

		bool aut = (g_hudset.channel == -1) ? true : false;
		int channel = -1;
		if (!aut)
		{
			/**
			 * guarantee this to be between 0-4
			 * if it's not auto, we don't care
			 */
			channel = std::abs(g_hudset.channel % 5);
		}
		if (index == 0)
		{
			for (int i = 0; i <= gpGlobals->maxClients; ++i)
			{
				if (MF_IsPlayerValid(i) && MF_IsPlayerIngame(i) && !MF_IsPlayerBot(i))
				{
					message = UTIL_SplitHudMessage(message);
					int* channels = (int*)MF_PlayerPropAddr(i, Player_NewmenuPage) + 1; // int[5]
					cell* hudmap = (cell*)MF_PlayerPropAddr(i, Player_NewmenuPage) + 1 + 5; // int[5]
					if (aut)
					{
						channel = NextHUDChannel(channels);
						channels[channel] = static_cast<int>(gpGlobals->time.time_since_epoch() / 1s);
						g_hudset.channel = channel;
					}
					//don't need to set g_hudset!
					hudmap[channel] = 0;
					UTIL_HudMessage(MF_GetPlayerEdict(i), g_hudset, message);
				}
			}
		}
		else {
			message = UTIL_SplitHudMessage(message);

			if (index < 1 || index > gpGlobals->maxClients)
			{
				return 0;
			}

			if (MF_IsPlayerValid(index) && MF_IsPlayerIngame(index) && !MF_IsPlayerBot(index))
			{
				int* channels = (int*)MF_PlayerPropAddr(index, Player_NewmenuPage) + 1; // int[5]
				cell* hudmap = (cell*)MF_PlayerPropAddr(index, Player_NewmenuPage) + 1 + 5; // int[5]
				if (aut)
				{
					channel = NextHUDChannel(channels);
					channels[channel] = static_cast<int>(gpGlobals->time.time_since_epoch() / 1s);
					g_hudset.channel = channel;
				}
				hudmap[channel] = 0;
				UTIL_HudMessage(MF_GetPlayerEdict(index), g_hudset, message);
			}
		}

		return len;
	}

	void show_hudmessage(int index, const char* message, ...)
	{
		char buffer[255];
		va_list va;
		va_start(va, message);
		vsnprintf(buffer, sizeof(buffer), message, va);
		va_end(va);
		send_hudmessage(index, buffer);
	}
}