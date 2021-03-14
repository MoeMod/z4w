module;
#include <functional>
#include <system_error>
export module amxx.amxmodx_detail;
import hlsdk.engine;

export namespace amxx {
	namespace detail {
		void StartFrame();
		void set_task(hlsdk::duration_t time, std::function<void(std::error_code)> function, int taskid);
		std::size_t remove_task(int taskid);
		std::size_t task_count(int taskid);
		bool task_exists(int taskid);
		void RequestFrame(std::function<void()> func);
	}
}