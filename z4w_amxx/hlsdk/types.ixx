
export module hlsdk.engine:types;
export import :vector;

export import <chrono>;

using namespace std::chrono_literals;

export namespace hlsdk
{
	typedef unsigned char byte;
	typedef int qboolean;
	typedef unsigned char BYTE;
	typedef int BOOL;
	typedef unsigned short word;
	typedef unsigned int uint;
	typedef unsigned int uint32; //!!!

	typedef int EOFFSET;
	typedef unsigned int ULONG;
	typedef int string_t;

	struct EngineClock
	{
		using rep = float;
		using period = std::ratio<1>;
		using duration = std::chrono::duration<rep, period>;
		using time_point = std::chrono::time_point<EngineClock>;
		static constexpr bool is_steady = false;
		static time_point now() noexcept;
	};

	static_assert(sizeof(EngineClock::duration) == sizeof(float) && sizeof(EngineClock::time_point) == sizeof(float), "EngineClock has not the same layout with engine.");
	using time_point_t = EngineClock::time_point;
	using duration_t = EngineClock::duration;

	constexpr EngineClock::duration zero_duration = EngineClock::duration::zero();
	constexpr EngineClock::duration one_duration = 1.0s;
	constexpr EngineClock::time_point invalid_time_point = EngineClock::time_point(zero_duration);

	constexpr float dtof(duration_t d) { return static_cast<float>(d / one_duration); }
	constexpr duration_t ftod(float f) { return f * one_duration; }
	constexpr float tptof(time_point_t t) { return dtof(t.time_since_epoch()); }
	constexpr time_point_t ftotp(float f) { return time_point_t(ftod(f)); }

	constexpr auto FALSE = 0;
	constexpr auto TRUE = !FALSE;
}