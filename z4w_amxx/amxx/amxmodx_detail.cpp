
module;
#define BOOST_ASIO_NO_DEPRECATED
#define BOOST_ASIO_STANDALONE
#include <boost/asio.hpp> // vcpkg install boost-asio
#include <chrono>
#include <functional>
#include <ranges>

module amxx.amxmodx_detail;
import hlsdk.engine;

using namespace hlsdk;
namespace amxx
{
	namespace detail {
#pragma region timer
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

		auto valid_tasks(int taskid)
		{
			auto [first, last] = timer_map.equal_range(taskid);
			return std::ranges::subrange(first, last) | std::ranges::views::values | std::ranges::views::transform([](const auto& wp) {return wp.lock(); });
		}

		void set_task(duration_t time, std::function<void(std::error_code)> function, int taskid)
		{
			using namespace detail;
			std::shared_ptr<timer_type> timer = std::make_shared<timer_type>(ioc);
			timer->expires_after(time);
			timer_map.emplace(taskid, timer);
			timer->async_wait([f = std::move(function), timer, taskid](const std::error_code& ec) {
				f(ec);
				for(auto [iter, last] = timer_map.equal_range(taskid); iter != last;)
				{
					if(iter->second.lock() == timer)
					{
						iter = timer_map.erase(iter);
					}
					else
					{
						++iter;
					}
				}
			});
		}

		std::size_t remove_task(int taskid)
		{
			std::size_t ret = task_count(taskid);
			std::ranges::for_each(valid_tasks(taskid), std::bind_front(&timer_type::cancel));
			return ret;
		}

		std::size_t task_count(int taskid)
		{
			return std::ranges::distance(valid_tasks(taskid));
		}

		bool task_exists(int taskid)
		{
			return !std::ranges::empty(valid_tasks(taskid));
		}

		void RequestFrame(std::function<void()> func)
		{
			boost::asio::dispatch(ioc, func);
		}
#pragma endregion
#pragma region message
		void MessageBegin(int msg_dest, int msg_type, const float* pOrigin, edict_t* ed) {}
		void MessageEnd() {}
		void WriteByte(int iValue) {}
		void WriteChar(int iValue) {}
		void WriteShort(int iValue) {}
		void WriteLong(int iValue) {}
		void WriteAngle(float fValue) {}
		void WriteCoord(float fValue) {}
		void WriteString(const char* sz) {}
		void WriteEntity(int iValue) {}
#pragma endregion
	}
}