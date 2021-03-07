module;

#include <algorithm>
#include <chrono>
#include <stdarg.h>

export module amxx.dhudmessage;

import hlsdk.enginecallback;
import hlsdk.util;
import amxx.message_const;
import amxxmodule;

using namespace hlsdk;
using namespace amxxmodule;
using namespace std::chrono_literals;

cell __dhud_color;
cell __dhud_x;
cell __dhud_y;
cell __dhud_effect;
cell __dhud_fxtime;
cell __dhud_holdtime;
cell __dhud_fadeintime;
cell __dhud_fadeouttime;
cell __dhud_reliable;


export namespace amxx {

    void set_dhudmessage(int red = 0, int green = 160, int blue = 0, float x = -1.0, float y = 0.65, int effects = 2, duration_t fxtime = 6.0s, duration_t holdtime = 3.0s, duration_t fadeintime = 0.1s, duration_t fadeouttime = 1.5s, bool reliable = false)
    {
        using std::clamp;
#define clamp_byte(x)       ( clamp( x, 0, 255 ) )
#define pack_color(x,y,z) ( z + ( y << 8 ) + ( x << 16 ) )

        __dhud_color = pack_color(clamp_byte(red), clamp_byte(green), clamp_byte(blue));
        __dhud_x = amx_ftoc(x);
        __dhud_y = amx_ftoc(y);
        __dhud_effect = effects;
        __dhud_fxtime = amx_ftoc(dtof(fxtime));
        __dhud_holdtime = amx_ftoc(dtof(holdtime)); 
        __dhud_fadeintime = amx_ftoc(dtof(fadeintime)); 
        __dhud_fadeouttime = amx_ftoc(dtof(fadeouttime)); 
        __dhud_reliable = reliable;
    }

    void send_dhudmessage(const int index, const char *message)
    {
        MESSAGE_BEGIN(__dhud_reliable ? (index ? MSG_ONE : MSG_ALL) : (index ? MSG_ONE_UNRELIABLE : MSG_BROADCAST), SVC_DIRECTOR, nullptr, index ? MF_GetPlayerEdict(index) : nullptr);
        {
            WRITE_BYTE(strlen(message) + 31);
            WRITE_BYTE(DRC_CMD_MESSAGE);
            WRITE_BYTE(__dhud_effect);
            WRITE_LONG(__dhud_color);
            WRITE_LONG(__dhud_x);
            WRITE_LONG(__dhud_y);
            WRITE_LONG(__dhud_fadeintime);
            WRITE_LONG(__dhud_fadeouttime);
            WRITE_LONG(__dhud_holdtime);
            WRITE_LONG(__dhud_fxtime);
            WRITE_STRING(message);
        }
        MESSAGE_END();
    }

    void show_dhudmessage(int index, const char *message, ...)
    {
        char buffer[255];
        va_list va;
        va_start(va, message);
        vsnprintf(buffer, sizeof(buffer), message, va);
        va_end(va);
        send_dhudmessage(index, buffer);
    }
}