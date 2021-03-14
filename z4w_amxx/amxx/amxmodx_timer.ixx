module;
#include <map>
#include <functional>
#include <coroutine>
#include <system_error>
export module amxx.amxmodx_timer;
import amxx.amxmodx_detail;
import amxx.coroutine;
import hlsdk.engine;

using namespace hlsdk;
export namespace amxx {

	void set_task(duration_t time, std::function<void(std::error_code)> function, int taskid = 0)
	{
		return detail::set_task(time, function, taskid);
	}

	void set_task(duration_t time, std::function<void()> function, int taskid = 0)
	{
		return detail::set_task(time, [function](std::error_code ec) { if (!ec) function(); }, taskid);
	}

	void set_task(duration_t time, std::function<void(int)> function, int taskid = 0)
	{
		return detail::set_task(time, [function, taskid](std::error_code ec) { if (!ec) function(taskid); }, taskid);
	}

	struct task_awaitable
	{
		task_awaitable(duration_t time, int taskid) : m_time(time), m_taskid(taskid), m_result() {}
		bool await_ready() noexcept {
			return false;
		}
		void await_suspend(std::coroutine_handle<> h) {
			set_task(m_time, [h, this](std::error_code ec) { m_result = std::move(ec); h.resume(); }, m_taskid);
		}
		[[nodiscard]] bool await_resume() noexcept { return !m_result; }
		duration_t m_time;
		int m_taskid;
		std::error_code m_result;
	};

	auto set_task(duration_t time, int taskid = 0)
	{
		return task_awaitable(time, taskid);
	}

	std::size_t remove_task(int taskid)
	{
		return detail::remove_task(taskid);
	}

	bool task_exists(int taskid)
	{
		return detail::task_exists(taskid);
	}

	void RequestFrame(std::function<void()> func)
	{
		return detail::RequestFrame(func);
	}

	auto RequestFrame()
	{
		return co_create_awaitable([](auto func) { RequestFrame(func); });
	}
}