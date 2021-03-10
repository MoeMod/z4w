module;
#include <map>
#include <functional>
export module amxx.amxmodx_timer;
import amxx.amxmodx_detail;
import hlsdk.types;

using namespace hlsdk;
export namespace amxx {

	void set_task(duration_t time, std::function<void()> function)
	{
		return detail::set_task(time, function);
	}

}