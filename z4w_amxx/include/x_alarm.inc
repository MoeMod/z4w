#if defined _x_alarm_included
  #endinput
#endif
#define _x_alarm_included

enum _:MAX_X_ALARMTYPE
{
    X_ALARMTYPE_NONE,
    X_ALARMTYPE_IDLE,
    X_ALARMTYPE_TIP,
    X_ALARMTYPE_INFECT,
    X_ALARMTYPE_KILL,
    X_ALARMTYPE_SKILL,
}

enum
{
    X_ALARM_IGNORED = 0,
    X_ALARM_SUPERCEDE
};

native x_alarm_push(iAlarmType = X_ALARMTYPE_NONE, const szTitle[], const szSubTitle[], const szSound[] = "", const iColor[], Float:flAlarmTime)
native x_alarm_insert(iAlarmType = X_ALARMTYPE_NONE, const szTitle[], const szSubTitle[], const szSound[] = "", const iColor[], Float:flAlarmTime)
native x_alarm_timertip(iTime, const szText[])
native x_alarm_kill(iKiller, iVictim, iAlarmType = X_ALARMTYPE_KILL)

forward x_fw_alarm_show_pre(iType, szTitle[128], szSubTitle[512], szSound[128], iColor[3], Float:flAlarmTime)
forward x_fw_alarm_show_post(iType, const szTitle[], const szSubTitle[], const szSound[], const iColor[], Float:flAlarmTime)