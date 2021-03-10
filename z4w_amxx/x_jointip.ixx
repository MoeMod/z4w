module;
#include <string>

export module x_jointip;
import amxx.amxmodx;
import stock;
import x_iplocation;

using namespace amxx;
using namespace stock;

export namespace x_jointip {

    std::string MakeWelcomeMessage(const std::string& name, const std::string& ip)
    {
        auto location = x_iplocation::GetIPLocation(ip);
        return location.empty() ?
            "\4[柑橘CitruS]\1 玩家\3" + name + "\1 进入了服务器。" :
            "\4[柑橘CitruS]\1 欢迎\3" + name + "\1 来自 \3[" + location + "]\1 进入服务器！";
    }

    void ClientPutInServer(auto_ent<int> id)
    {
        auto name = get_user_name(id);
        auto ip = get_user_ip(id);
        auto szMessage = MakeWelcomeMessage(name, ip);
        client_color(0, id, szMessage.c_str());
    }

    void ClientDisconnect(auto_ent<int> id)
    {
        auto name = get_user_name(id);
        auto ip = get_user_ip(id);
        auto szMessage = "\4[柑橘CitruS]\1 玩家\3" + name + "\1 离开了服务器。";
        client_color(0, id, szMessage.c_str());
    }
}