module;
#include <exception>
#include <functional>
#include <coroutine>
export module amxx.coroutine;
export import hlsdk.types;

using namespace hlsdk;
export namespace amxx {
	inline namespace coroutine {
		using std::coroutine_handle;

		template<class Fn = void(*)(void(*)())>
		struct AwaitableResult
		{
			bool await_ready() noexcept {
				return false;
			}
			void await_suspend(coroutine_handle<> h) {
				std::invoke(m_callback, std::bind(&coroutine_handle<>::resume, h));
			}
			void await_resume() noexcept {}

			typename std::decay<Fn>::type m_callback;
		};

		template<class Fn = void(*)(void(*)())>
		auto co_create_awaitable(Fn&& fn) // requires std::invocable<Fn, std::function<void()>>
		{
			return AwaitableResult<Fn>{ std::forward<Fn>(fn) };
		}

		class co_task
		{
		public:
			struct promise_type {
				auto get_return_object() { return co_task{}; }
				auto initial_suspend() { return std::suspend_never{}; }
				auto final_suspend() noexcept { return std::suspend_never{}; }
				void unhandled_exception() { std::terminate(); }
				void return_void() {}
			};
		};
	}
}