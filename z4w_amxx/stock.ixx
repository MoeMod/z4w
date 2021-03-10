module;
#include <stdio.h>
#include <string.h>

export module stock;
import amxx.amxmodx;
import hlsdk.extdll;
import hlsdk.enginecallback;
import amxxmodule;

using namespace amxx;
using namespace hlsdk;
using namespace amxxmodule;

export namespace stock {
    void PlaySound(int index, const char* szSound, bool stop_sounds_first = false)
    {
        if (!szSound || !szSound[0])
            return;
        char buffer[512];
        if (stop_sounds_first)
        {
            if (!strcmp(szSound + strlen(szSound) - 4, ".mp3"))
            {
                snprintf(buffer, 511, "stopsound; mp3 play \"sound/%s\"", szSound);
                client_cmd(index, buffer);
            }
            else
            {
                snprintf(buffer, 511, "mp3 stop; stopsound; spk \"%s\"", szSound);
                client_cmd(index, buffer);
            }
        }
        else
        {
            if (!strcmp(szSound + strlen(szSound) - 4, ".mp3"))
            {
                snprintf(buffer, 511, "mp3 play \"sound/%s\"", szSound);
                client_cmd(index, buffer);
            }
            else
            {
                snprintf(buffer, 511, "spk \"%s\"", szSound);
                client_cmd(index, buffer);
            }
        }
    }

    void client_color(auto_ent<int> playerid, int colorid, const char* msg)
    {
        MESSAGE_BEGIN(playerid ? MSG_ONE : MSG_ALL, get_user_msgid("SayText"), nullptr, playerid ? ent_cast<edict_t*>(playerid) : nullptr);
        WRITE_BYTE(colorid);
        WRITE_STRING(msg);
        MESSAGE_END();
    }
}