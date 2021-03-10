module;
#include <string>

export module x_jointip;
import amxx.amxmodx;
import stock;
import qqwry;
import encode;

using namespace amxx;
using namespace stock;

export namespace x_jointip {

    std::string GetIPLocation(std::string ip) noexcept try
    {
        // 放到游戏根目录
        static CQQWry qqwry("QQWry.dat");
        std::string country, area;
        // 去掉ip后面的端口号（不知道为什么会有...）
        ip.erase(std::find(ip.begin(), ip.end(), ':'), ip.end());
        qqwry.GetAddressByIp(ip.c_str(), country, area);
        country = GBK_To_UTF8(country);
        area = GBK_To_UTF8(area);
        if (country == " CZ88.NET")
            country.clear();
        if (area == " CZ88.NET")
            area.clear();
        return country + " " + area;
    }
    catch (...)
    {
        return {};
    }

    std::string MakeWelcomeMessage(const std::string& name, const std::string& ip)
    {
        auto location = GetIPLocation(ip);
        return location.empty() ?
            " \x04[柑橘CitruS]\x01 玩家\x03" + name + "\x01 进入了服务器。" :
            " \x04[柑橘CitruS]\x01 欢迎\x03" + name + "\x01 来自 \x03[" + location + "]\x01 进入服务器！";
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
        auto szMessage = " \x04[柑橘CitruS]\x01 玩家\x03" + name + "\x01 离开了服务器。";
        client_color(0, id, szMessage.c_str());
    }
}