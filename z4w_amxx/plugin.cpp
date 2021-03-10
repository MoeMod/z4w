
#include <algorithm>
#include <string>

#include "amxxmodule.h"
#include "meta_api.h"

import amxxmodule;
import plugin;
import x_alarm;
import x_semiclip;
import x_jointip;

namespace plugin {
	int g_iForwards[TOTAL_FORWARDS];
}

using namespace amxxmodule;
using namespace plugin;

//Register forward
void ServerDeactivate_Post(void)
{
	std::fill_n(g_iForwards, TOTAL_FORWARDS, 0);
}

void OnAmxxAttach(void)
{
	std::fill_n(g_iForwards, TOTAL_FORWARDS, 0);

	extern AMX_NATIVE_INFO Plugin_Natives[];
	MF_AddNatives(Plugin_Natives);
}

void OnPluginsLoaded(void)
{
	g_iForwards[FW_Semiclip] = MF_RegisterForward("x_fw_api_semiclip", ET_CONTINUE, FP_CELL, FP_CELL, FP_DONE);
	g_iForwards[FW_ALARM_SHOW_PRE] = MF_RegisterForward("x_fw_alarm_show_pre", ET_CONTINUE, FP_CELL, FP_ARRAY, FP_ARRAY, FP_ARRAY, FP_ARRAY, FP_FLOAT, FP_DONE);
	g_iForwards[FW_ALARM_SHOW_POST] = MF_RegisterForward("x_fw_alarm_show_post", ET_IGNORE, FP_CELL, FP_ARRAY, FP_ARRAY, FP_ARRAY, FP_ARRAY, FP_FLOAT, FP_DONE);
	x_alarm::plugin_init();
}

void PM_Move(struct playermove_s* ppmove, int server)
{
	x_semiclip::PM_Move(ppmove, server);
	RETURN_META(MRES_HANDLED);
}

void PM_Move_Post(struct playermove_s* ppmove, int server)
{
	x_semiclip::PM_Move_Post(ppmove, server);
	RETURN_META(MRES_HANDLED);
}

void PlayerPreThink(edict_t* pPlayer)
{
	x_semiclip::PlayerPreThink(pPlayer);
	RETURN_META(MRES_HANDLED);
}

void PlayerPostThink(edict_t* pPlayer)
{
	x_semiclip::PlayerPostThink(pPlayer);
	RETURN_META(MRES_HANDLED);
}

void ClientPutInServer(edict_t* pPlayer)
{
	x_jointip::ClientPutInServer(pPlayer);
	RETURN_META(MRES_HANDLED);
}

void ClientDisconnect(edict_t* pPlayer)
{
	x_jointip::ClientDisconnect(pPlayer);
	RETURN_META(MRES_HANDLED);
}

int AddToFullPack_Post(struct entity_state_s* state, int e, edict_t* ent, edict_t* host, int hostflags, int player, unsigned char* pSet)
{
	x_semiclip::AddToFullPack_Post(state, e, ent, host, hostflags, player, pSet);
	RETURN_META_VALUE(MRES_HANDLED, 1);
}

static auto x_alarm_from_args(AMX* amx, cell* params)
{
	using namespace x_alarm;
	AlarmType_e type = (AlarmType_e)params[1];
	int len;
	char* str;
	cell* vec;
	str = MF_GetAmxString(amx, params[2], 0, &len);
	std::string szTitle(str);
	str = MF_GetAmxString(amx, params[3], 0, &len);
	std::string szSubTitle(str);
	str = MF_GetAmxString(amx, params[4], 0, &len);
	std::string szSound(str);
	vec = MF_GetAmxAddr(amx, params[5]);
	Color color = { vec[0], vec[1], vec[2] };
	duration_t time = ftod(amx_ctof(params[6]));
	return Alarm_s{ type, color, time, std::move(szTitle), std::move(szSubTitle), std::move(szSound) };
}

// native x_alarm_insert(iAlarmType = X_ALARMTYPE_NONE, const szTitle[], const szSubTitle[], const szSound[] = "", const iColor[], Float:flAlarmTime)
static cell AMX_NATIVE_CALL x_alarm_insert(AMX* amx, cell* params)
{
	AlarmInsert(x_alarm_from_args(amx, params));
	return 1;
}

// native x_alarm_push(iAlarmType = X_ALARMTYPE_NONE, const szTitle[], const szSubTitle[], const szSound[] = "", const iColor[], Float:flAlarmTime)
static cell AMX_NATIVE_CALL x_alarm_push(AMX* amx, cell* params)
{
	x_alarm::AlarmPush(x_alarm_from_args(amx, params));
	return 1;
}

// native x_alarm_timertip(iTime, const szText[])
static cell AMX_NATIVE_CALL x_alarm_timertip(AMX* amx, cell* params)
{
	int iTime = params[1];
	int len;
	char* str;
	str = MF_GetAmxString(amx, params[2], 0, &len);
	std::string szText(str);
	x_alarm::TimerTip(ftod(float(iTime)), std::move(szText));
	return 1;
}

// native x_alarm_kill(iKiller, iVictim, iAlarmType = X_ALARMTYPE_KILL)
static cell AMX_NATIVE_CALL x_alarm_kill(AMX* amx, cell* params)
{
	using namespace x_alarm;
	int iKiller = params[1];
	int iVictim = params[2];
	AlarmType_e iAlarmType = (AlarmType_e)params[3];
	x_alarm::SendKillEvent(iKiller, iVictim, iAlarmType);
	return 1;
}

AMX_NATIVE_INFO Plugin_Natives[] =
{
	{"x_alarm_push",			x_alarm_push},
	{"x_alarm_insert",			x_alarm_insert},
	{"x_alarm_timertip",		x_alarm_timertip},
	{"x_alarm_kill",			x_alarm_kill},
	{NULL,				NULL},
};