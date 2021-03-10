module;
#include <string>

export module x_iplocation;
import amxx.amxmodx;
import qqwry;
import encode;

using namespace amxx;

export namespace x_iplocation {

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
}