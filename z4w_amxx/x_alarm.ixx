module;

#include <string>
#include <functional>
#include <chrono>
#include <array>
#include <list>

export module x_alarm;
export import hlsdk.types;
export import SourceSDK.Color;
import amxx.amxmodx;
import amxxmodule;
import plugin;
import stock;

using namespace hlsdk;
using namespace amxx;
using namespace amxxmodule;
using namespace plugin;
using namespace stock;
using namespace std::chrono_literals;

export namespace x_alarm {

    using hlsdk::duration_t;
    using hlsdk::time_point_t;
    using SourceSDK::Color;

    enum AlarmType_e : int
    {
        ALARMTYPE_NONE,
        ALARMTYPE_IDLE,
        ALARMTYPE_TIP,
        ALARMTYPE_INFECT,
        ALARMTYPE_KILL,
        ALARMTYPE_SKILL,
        MAX_ALARMTYPE,
    };

    struct Alarm_s {
        AlarmType_e type;
        Color color;
        duration_t time;
        std::string title;
        std::string subtitle;
        std::string sound;
        std::function<void()> callback;
    };
}

namespace x_alarm {


    constexpr float HUD_ALARM_X = -1.0f;
    constexpr float HUD_ALARM_Y = 0.15f;

    std::list<Alarm_s> g_AlarmList;

    struct TimerTipInfo_s {
        duration_t time = {};
        std::string text;
        time_point_t time_begin = {};
    } g_TimerTipInfo;

    enum AlarmKillerIndex_e
    {
        ALARM_KILL, ALARM_2KILL, ALARM_3KILL,
        ALARM_4KILL, ALARM_5KILL,
        ALARM_3KILLRECORD, ALARM_4KILLRECORD, ALARM_5KILLRECORD,
        ALARM_6KILLRECORD, ALARM_7KILLRECORD, ALARM_8KILLRECORD,
        ALARM_9KILLRECORD, ALARM_10KILLRECORD,
        ALARM_FIRSTBLOOD, ALARM_SHUTDOWN
    };

    constexpr const char* cfg_szTextAlarmKiller[] = {
        "KILL!" , "DOUBLE KILL!" , "TRIPLE KILL!" ,
        "QUADRA KILL!" , "PENTA KILL!" ,
        "KILLING SPREE! x3" , "DOMINATING! x4" , "MEGA KILL! x5" ,
        "UNSTOPPABLE! x6" , "WICKEDSICK! x7" , "MONSTER KILL! x8" ,
        "GOD LIKE! x9" , "Holy Shit! x10" ,
        "FIRST BLOOD" , "PERFECT!"
    };
    constexpr const char* cfg_szSoundAlarmKiller[] = {
        "" , "" , "" ,
        "" , "" ,
        "" , "" , "" ,
        "" , "" , "" ,
        "" , "" ,
        "" , ""
    };

    constexpr const char* cfg_szAlarmSubSound[MAX_ALARMTYPE] = {
        "" ,
        "" ,
        "" ,
        "" ,
        ""
    };

    Color cfg_iAlarmColor[] = {
        { 255, 255, 255 },
        { 255, 255, 255 },
        { 200, 200, 50 },
        { 255, 42, 42 },
        { 42, 212, 255 }
    };

    struct PlayerKillInfo_s {
        int iRoundKill = 0;
        int iKillSeries = 0;
        int iKillingSpree = 0;
        time_point_t flLastKillTime = {};
    };
    bool g_bHasFirstBlood = false;
    std::array<PlayerKillInfo_s, 33> g_ClientData;

    void CheckAlarmTask()
    {
        Alarm_s alarm = Alarm_s{ ALARMTYPE_IDLE, cfg_iAlarmColor[ALARMTYPE_IDLE], 0.96875s };
        if (!g_AlarmList.empty())
        {
            alarm = g_AlarmList.front();
            g_AlarmList.pop_front();
        }

        int iTimerCount = static_cast<int>((g_TimerTipInfo.time_begin + g_TimerTipInfo.time - get_gametime()) / 1s);
        if (iTimerCount > 0)
        {
            alarm = Alarm_s{ ALARMTYPE_TIP, cfg_iAlarmColor[ALARMTYPE_TIP], 1.0s, g_TimerTipInfo.text + " [" + std::to_string(iTimerCount) + "]" };
        }

        int iType = alarm.type;
        char title[128]; strncpy(title, alarm.title.c_str(), 127);
        char subtitle[512]; strncpy(subtitle, alarm.subtitle.c_str(), 127);
        char sound[128]; strncpy(sound, alarm.sound.c_str(), 127);
        int color[3] = { alarm.color.r(), alarm.color.g(), alarm.color.b() };
        float flAlarmTime = alarm.time / 1s;

        auto iForwardResult = MF_ExecuteForward(g_iForwards[FW_ALARM_SHOW_PRE], (cell)iType, MF_PrepareCharArrayA(title, 127, 1), MF_PrepareCharArrayA(subtitle, 511, 1), MF_PrepareCharArrayA(sound, 127, 1), MF_PrepareCellArrayA(color, 3, 1), amx_ftoc(flAlarmTime));

        alarm.title = title;
        alarm.subtitle = subtitle;
        alarm.sound = sound;
        alarm.color = { color[0], color[1], color[2] };

        if (iForwardResult == PLUGIN_CONTINUE)
        {
            if (!alarm.title.empty() || !alarm.subtitle.empty())
            {
                set_hudmessage(color[0], color[1], color[2], HUD_ALARM_X, HUD_ALARM_Y, 0, 1.0s, alarm.time + 0.1s, 0.1s, 0.4s, 3);
                show_hudmessage(0, "\n [柑橘CitruS] \n\n%s", subtitle);
                set_dhudmessage(color[0], color[1], color[2], HUD_ALARM_X, HUD_ALARM_Y + 0.05f, 0, 1.2s, alarm.time + 0.1s, 0.1s, 0.4s);
                show_dhudmessage(0, title);
            }
            if (alarm.callback)
                alarm.callback();

            if (iType < std::extent<decltype(cfg_szAlarmSubSound)>::value)
                PlaySound(0, cfg_szAlarmSubSound[iType]);
            else
                PlaySound(0, sound);

            auto iForwardResult = MF_ExecuteForward(g_iForwards[FW_ALARM_SHOW_POST], (cell)iType, MF_PrepareCharArrayA(title, 127, 0), MF_PrepareCharArrayA(subtitle, 511, 0), MF_PrepareCharArrayA(sound, 127, 0), MF_PrepareCellArrayA(color, 3, 0), amx_ftoc(flAlarmTime));
        }
        set_task(alarm.time, CheckAlarmTask);
    }
}

export namespace x_alarm {

    void AlarmPush(const Alarm_s& alarm)
    {
        g_AlarmList.push_back(alarm);
    }

    void AlarmInsert(const Alarm_s& alarm)
    {
        g_AlarmList.push_front(alarm);
    }

    void TimerTip(duration_t time, const std::string& text)
    {
        g_TimerTipInfo = { time, text, get_gametime() };
    }

    void SendKillEvent(int killer, int victim, AlarmType_e iAlarmType)
    {
        if (!killer || !victim)
            return;
        auto iAlarm = ALARM_KILL;
        g_ClientData[killer].iRoundKill++;
        if (get_gametime() - g_ClientData[killer].flLastKillTime > 11.5s)
            g_ClientData[killer].iKillSeries = 0;
        g_ClientData[killer].iKillSeries = std::min(g_ClientData[killer].iKillSeries + 1, 5);
        if (get_gametime() - g_ClientData[victim].flLastKillTime <= 11.5s)
            iAlarm = ALARM_SHUTDOWN;
        switch (g_ClientData[killer].iKillingSpree)
        {
        case 3:iAlarm = ALARM_3KILLRECORD; break;
        case 4:iAlarm = ALARM_4KILLRECORD; break;
        case 5:iAlarm = ALARM_5KILLRECORD; break;
        case 6:iAlarm = ALARM_6KILLRECORD; break;
        case 7:iAlarm = ALARM_7KILLRECORD; break;
        case 8:iAlarm = ALARM_8KILLRECORD; break;
        case 9:iAlarm = ALARM_9KILLRECORD; break;
        case 10:iAlarm = ALARM_10KILLRECORD; break;
        default:break;
        }
        switch (g_ClientData[killer].iKillSeries)
        {
        case 2:iAlarm = ALARM_2KILL; break;
        case 3:iAlarm = ALARM_3KILL; break;
        case 4:iAlarm = ALARM_4KILL; break;
        case 5:iAlarm = ALARM_5KILL; break;
        default:break;
        }
        g_ClientData[killer].flLastKillTime = get_gametime();
        if (!std::exchange(g_bHasFirstBlood, true))
            iAlarm = ALARM_FIRSTBLOOD;

        g_ClientData[victim].iKillingSpree = 0;
        g_ClientData[killer].iKillingSpree++;

        AlarmPush(Alarm_s{ iAlarmType, cfg_iAlarmColor[iAlarmType], 1.0s,
                          get_user_name(killer) + std::string("\t:\t") + cfg_szTextAlarmKiller[iAlarm],
                          get_user_name(killer) + std::string(" has killed ") + get_user_name(victim),
                          ""
            });
    }

    void plugin_init()
    {
        g_ClientData = {};
        g_TimerTipInfo = {};
        g_bHasFirstBlood = false;
        set_task(15s, CheckAlarmTask);
    }
}