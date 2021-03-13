module;
#include <map>
#include <functional>
#include <system_error>
export module amxx.amxmodx_timer;
export import amxx.coroutine;
import amxx.amxmodx_detail;
import hlsdk.types;

using namespace hlsdk;
export namespace amxx {

	void set_task(duration_t time, std::function<void()> function, std::function<void(std::error_code)> on_error = {})
	{
		return detail::set_task(time, function, on_error);
	}

	auto set_task(duration_t time)
	{
		return co_create_awaitable([time](auto f) { set_task(time, f); });
	}
}