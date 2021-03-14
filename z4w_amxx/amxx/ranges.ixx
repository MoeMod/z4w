module;
#include <array>
#include <ranges>
#include <numeric>
#include <span>

export module amxx.ranges;
export import amxx.amxmodx;
export import amxx.convert;
export import hlsdk.cdll_dll;

using namespace hlsdk;

export namespace amxx {
	namespace ranges {
		namespace detail {
			template<class T, T...I> constexpr auto IntegerSequenceArr(std::integer_sequence<T, I...>)
			{
				constexpr std::array<T, sizeof...(I)> arr = { I... };
				return arr;
			}
		}

		template<class EntityType = int>
		inline auto players()
		{
			constexpr auto arr = detail::IntegerSequenceArr(std::make_integer_sequence<int, MAX_CLIENTS + 1>());
			int player_count = get_maxplayers();
			return std::ranges::subrange(arr.begin() + 1, arr.begin() + 1 + player_count)
				| std::views::transform(convert::make_auto_ent<EntityType>);
		}

		inline auto connected = std::views::filter(is_user_connected);
		inline auto alive = std::views::filter(is_user_alive);
	}
}