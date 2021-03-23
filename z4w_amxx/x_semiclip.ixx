
export module x_semiclip;

import hlsdk.extdll;
import hlsdk.util;
import hlsdk.pm_defs;
import hlsdk.entity_state;
import amxxmodule;
import amxx.amxmodx;
import plugin;

import <algorithm>;

using namespace hlsdk;
using namespace amxxmodule;
using namespace amxx;
using namespace plugin;

export namespace x_semiclip {

	//here we backup the physent array
	int g_iNumBackupPhysent;
	physent_t g_sBackupPhysent[MAX_PHYSENTS];

	bool g_bSolid[MAX_MOVEENTS], g_bRestore[MAX_MOVEENTS];

	// penetrates when return 0
	int PM_ShouldCollide(int playerindex, int entindex)
	{
		return !MF_ExecuteForward(g_iForwards[FW_Semiclip], (cell)playerindex, (cell)entindex);
	}

	void PM_Move(struct playermove_s* ppmove, int server)
	{
		int iPlayerIndex = ppmove->player_index + 1;

		//backup physent
		g_iNumBackupPhysent = ppmove->numphysent;
		std::copy(ppmove->physents, ppmove->physents + ppmove->numphysent, g_sBackupPhysent);

		//rebuild
		physent_t* iter = std::remove_if(ppmove->physents, ppmove->physents + ppmove->numphysent, [iPlayerIndex](const physent_t& ps) {
			return !PM_ShouldCollide(iPlayerIndex, ps.info);
			});
		ppmove->numphysent = std::distance(ppmove->physents, iter);
	}

	void PM_Move_Post(struct playermove_s* ppmove, int server)
	{
		ppmove->numphysent = g_iNumBackupPhysent;
		std::move(g_sBackupPhysent, g_sBackupPhysent + g_iNumBackupPhysent, ppmove->physents);
	}

	void PlayerPreThink(edict_t* pPlayer)
	{
		int Client = ENTINDEX(pPlayer);
		static int Flag = 0U;

		if (Flag > Client)
		{
			for (int Iterator = 1; Iterator <= gpGlobals->maxClients; Iterator++)
			{
				if (!MF_IsPlayerAlive(Iterator))
				{
					g_bSolid[Iterator] = false;
					continue;
				}

				pPlayer = MF_GetPlayerEdict(Iterator);

				//g_Player[Iterator].Team = MF_GetPlayerTeamID(Iterator);
				//g_Player[Iterator].Solid = pPlayer->v.solid == SOLID_SLIDEBOX ? true : false;
				if (pPlayer->v.solid == SOLID_SLIDEBOX)
				{
					g_bSolid[Iterator] = true;
				}
				else
				{
					g_bSolid[Iterator] = false;
				}
			}
		}

		Flag = Client;

		if (!g_bSolid[Client])
		{
			return;
		}

		for (int Iterator = 1U; Iterator <= gpGlobals->maxClients; Iterator++)
		{
			if (!g_bSolid[Iterator] || Client == Iterator || PM_ShouldCollide(Iterator, Client))
			{
				continue;
			}

			pPlayer = MF_GetPlayerEdict(Iterator);

			pPlayer->v.solid = SOLID_NOT;

			g_bRestore[Iterator] = true;
		}

		return;
	}

	void PlayerPostThink(edict_t*)
	{
		for (int Iterator = 1U; Iterator <= gpGlobals->maxClients; Iterator++)
		{
			if (g_bRestore[Iterator])
			{
				edict_t* pPlayer = MF_GetPlayerEdict(Iterator);

				pPlayer->v.solid = SOLID_SLIDEBOX;

				g_bRestore[Iterator] = false;
			}
		}

		return;
	}

	bool IsPlayerIndex(int ent_id)
	{
		return ent_id > 0 && ent_id <= gpGlobals->maxClients;
	}

	int AddToFullPack_Post(struct entity_state_s* state, int e, edict_t* ent, edict_t* host, int hostflags, int player, unsigned char* pSet)
	{
		int ent_id = ENTINDEX(ent);
		int host_id = ENTINDEX(host);
		if (player && (ent != host) && IsPlayerIndex(ent_id))
		{
			state->solid = SOLID_NOT;

			entvars_t* pevHost = &(host->v);
			entvars_t* pevEntity = &(ent->v);
			if (pevHost && pevEntity && pevHost->deadflag == DEAD_NO)
			{
				Vector vecDelta = pevEntity->origin - pevHost->origin;
				float flLengthSquared = DotProduct(vecDelta, vecDelta);
				if (flLengthSquared < 85.0f * 85.0f)
				{
					if (!PM_ShouldCollide(host_id, ent_id))
					{
						state->renderamt = static_cast<int>(sqrtf(flLengthSquared * 9.0f));
						state->rendermode = kRenderTransAlpha;
					}
				}
			}
		}

		return PLUGIN_CONTINUE;
	}

	void plugin_init()
	{

	}
}