module;
#include <exception>
#include <functional>
#include <concepts>
#include <coroutine>
#include <optional>
export module amxx.coroutine;
export import hlsdk.engine;

using namespace hlsdk;
export namespace amxx {
	namespace coroutine {
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
		auto co_create_awaitable(Fn&& fn) requires std::invocable<Fn, std::function<void()>>
		{
			return AwaitableResult<Fn>{ std::forward<Fn>(fn) };
		}

        template<std::movable T>
        class co_generator {
        public:
            struct promise_type {
                co_generator<T> get_return_object() {
                    return co_generator{ Handle::from_promise(*this) };
                }
                static std::suspend_always initial_suspend() noexcept {
                    return {};
                }
                static std::suspend_always final_suspend() noexcept {
                    return {};
                }
                std::suspend_always yield_value(T value) noexcept {
                    current_value = std::move(value);
                    return {};
                }
                // Disallow co_await in generator coroutines.
                void await_transform() = delete;
                [[noreturn]]
                static void unhandled_exception() {
                    throw;
                }

                void return_void() {}

                std::optional<T> current_value;
            };

            using Handle = std::coroutine_handle<promise_type>;

            explicit co_generator(const Handle coroutine) :
                m_coroutine{ coroutine }
            {}

            co_generator() = default;
            ~co_generator() {
                if (m_coroutine) {
                    m_coroutine.destroy();
                }
            }

            co_generator(const co_generator&) = delete;
            co_generator& operator=(const co_generator&) = delete;

            co_generator(co_generator&& other) noexcept :
                m_coroutine{ other.m_coroutine }
            {
                other.m_coroutine = {};
            }
            co_generator& operator=(co_generator&& other) noexcept {
                if (this != &other) {
                    if (m_coroutine) {
                        m_coroutine.destroy();
                    }
                    m_coroutine = other.m_coroutine;
                    other.m_coroutine = {};
                }
                return *this;
            }

            // Range-based for loop support.
            class Iter : std::forward_iterator_tag {
            public:
                void operator++() {
                    m_coroutine.resume();
                }
                const T& operator*() const {
                    return *m_coroutine.promise().current_value;
                }
                bool operator==(std::default_sentinel_t) const {
                    return !m_coroutine || m_coroutine.done();
                }

                explicit Iter(const Handle coroutine) :
                    m_coroutine{ coroutine }
                {}

            private:
                Handle m_coroutine;
            };

            Iter begin() {
                if (m_coroutine) {
                    m_coroutine.resume();
                }
                return Iter{ m_coroutine };
            }
            std::default_sentinel_t end() {
                return {};
            }

        private:
            Handle m_coroutine;
        };

        struct co_task
        {
            struct promise_type {
                auto get_return_object() {
                    return co_task(std::coroutine_handle<promise_type>::from_promise(*this));
                }
                std::suspend_always initial_suspend() { return {}; }
                struct final_awaiter {
                    bool await_ready() noexcept { return false; }
                    void await_resume() noexcept {}
                    std::coroutine_handle<> await_suspend(std::coroutine_handle<promise_type> h) noexcept {
                        // final_awaiter::await_suspend is called when the execution of the
                        // current coroutine (referred to by 'h') is about to finish.
                        // If the current coroutine was resumed by another coroutine via
                        // co_await get_task(), a handle to that coroutine has been stored
                        // as h.promise().previous. In that case, return the handle to resume
                        // the previous coroutine.
                        // Otherwise, return noop_coroutine(), whose resumption does nothing.

                        auto previous = h.promise().previous;
                        if (previous) {
                            return previous;
                        }
                        else {
                            return std::noop_coroutine();
                        }
                    }
                };
                final_awaiter final_suspend() noexcept { return {}; }
                void unhandled_exception() { throw; }
                void return_void() {}
                std::coroutine_handle<> previous;
            };

            co_task(std::coroutine_handle<promise_type> h) : coro(h) {}
            co_task(co_task&& t) = delete;
            ~co_task() { coro.destroy(); }

            struct awaiter {
                bool await_ready() { return false; }
                void await_resume() { return; }
                auto await_suspend(std::coroutine_handle<> h) {
                    coro.promise().previous = h;
                    return coro;
                }
                std::coroutine_handle<promise_type> coro;
            };
            awaiter operator co_await() { return awaiter{ coro }; }
        private:
            std::coroutine_handle<promise_type> coro;
        };

        template<class T = void>
        struct co_task_v {
            struct promise_type {
                auto get_return_object() {
                    return co_task_v(std::coroutine_handle<promise_type>::from_promise(*this));
                }
                std::suspend_always initial_suspend() { return {}; }
                struct final_awaiter {
                    bool await_ready() noexcept { return false; }
                    void await_resume() noexcept {}
                    std::coroutine_handle<> await_suspend(std::coroutine_handle<promise_type> h) noexcept {
                        // final_awaiter::await_suspend is called when the execution of the
                        // current coroutine (referred to by 'h') is about to finish.
                        // If the current coroutine was resumed by another coroutine via
                        // co_await get_task(), a handle to that coroutine has been stored
                        // as h.promise().previous. In that case, return the handle to resume
                        // the previous coroutine.
                        // Otherwise, return noop_coroutine(), whose resumption does nothing.

                        auto previous = h.promise().previous;
                        if (previous) {
                            return previous;
                        }
                        else {
                            return std::noop_coroutine();
                        }
                    }
                };
                final_awaiter final_suspend() noexcept { return {}; }
                void unhandled_exception() { throw; }
                void return_value(T value) { result = std::move(value); }
                T result;
                std::coroutine_handle<> previous;
            };

            co_task_v(std::coroutine_handle<promise_type> h) : coro(h) {}
            co_task_v(co_task_v&& t) = delete;
            ~co_task_v() { coro.destroy(); }

            struct awaiter {
                bool await_ready() { return false; }
                T await_resume() { return std::move(coro.promise().result); }
                auto await_suspend(std::coroutine_handle<> h) {
                    coro.promise().previous = h;
                    return coro;
                }
                std::coroutine_handle<promise_type> coro;
            };
            awaiter operator co_await() { return awaiter{ coro }; }
            T operator()() {
                coro.resume();
                return std::move(coro.promise().result);
            }
        private:
            std::coroutine_handle<promise_type> coro;
        };
	}

    using coroutine::co_generator;
    using coroutine::co_task;
    using coroutine::co_task_v;
    using coroutine::co_create_awaitable;
}