module;
#include <stdio.h>
#include <string.h>

export module stock;
import amxx.amxmodx;

using namespace amxx;

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
}