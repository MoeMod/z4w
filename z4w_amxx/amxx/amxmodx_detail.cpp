
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
		using timer_type = boost::asio::high_resolution_timer;
		std::multimap<int, std::weak_ptr<boost::asio::high_resolution_timer>> timer_map;

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
			timer->expires_from_now(std::chrono::duration_cast<timer_type::duration>(time));
			timer_map.emplace(0, timer);
			timer->async_wait([f = std::move(function), timer](const std::error_code& ec) {
				if (!ec)
					f();
			});
		}
	}
}