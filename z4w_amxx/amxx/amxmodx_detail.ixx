module;
#include <functional>
export module amxx.amxmodx_detail;
import hlsdk.types;

export namespace amxx {
	namespace detail {
		void StartFrame();
		void set_task(hlsdk::duration_t time, std::function<void()> function);
	}
}