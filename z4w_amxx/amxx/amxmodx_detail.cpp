
module;
#include <boost/asio.hpp>
#include <chrono>
#include <functional>

module amxx.amxmodx_detail;
import hlsdk.types;

using namespace hlsdk;

namespace amxx
{
	namespace detail {
		boost::asio::io_context ioc;
		// 这里改用引擎虚拟时钟，避免和操作系统耦合导致系统时间变更的时候出现异常行为
		using timer_type = boost::asio::basic_waitable_timer<EngineClock>;
		std::multimap<int, std::weak_ptr<timer_type>> timer_map;

		void Timer_StartFrame()
		{
			ioc.poll();
		}

		void StartFrame()
		{
			Timer_StartFrame();
		}

		void set_task(duration_t time, std::function<void()> function)
		{
			using namespace detail;
			std::shared_ptr<timer_type> timer = std::make_shared<timer_type>(ioc);
			timer->expires_from_now(time);
			timer_map.emplace(0, timer);
			timer->async_wait([f = std::move(function), timer](const std::error_code& ec) {
				if (!ec)
					f();
			});
		}
	}
}