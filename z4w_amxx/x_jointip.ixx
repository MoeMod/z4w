module;
#include <string>
#include <chrono>
#include <coroutine>
export module x_jointip;
import amxx.amxmodx;
import hlsdk.engine;
import stock;
import x_iplocation;
using namespace amxx;
using namespace hlsdk;
using namespace std::chrono_literals;

export namespace x_jointip {
    time_point_t g_flLastShowTime;
    std::string MakeWelcomeMessage(const std::string& name, const std::string& ip)
    {
        auto location = x_iplocation::GetIPLocation(ip);
        return location.empty() ?
            "\4[柑橘CitruS]\1 玩家\3" + name + "\1 进入了服务器。" :
            "\4[柑橘CitruS]\1 欢迎\3" + name + "\1 来自 \3[" + location + "]\1 进入服务器！";
    }
    co_task ClientPutInServer(auto_ent<int> id)
    {
        auto name = get_user_name(id);
        auto ip = get_user_ip(id);
        auto szMessage = MakeWelcomeMessage(name, ip);
        if (co_await set_task(1.0s))
        {
            stock::client_color(0, id, szMessage);
            g_flLastShowTime = get_gametime();
        }
    }

    co_task ClientDisconnect(auto_ent<int> id)
    {
        auto name = get_user_name(id);
        auto ip = get_user_ip(id);
        auto szMessage = "\4[柑橘CitruS]\1 玩家\3" + name + "\1 离开了服务器。";
        if (co_await set_task(1.0s))
        {
            stock::client_color(0, id, szMessage);
            g_flLastShowTime = get_gametime();
        }
    }
}