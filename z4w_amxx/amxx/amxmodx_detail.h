#pragma once

#include <functional>

import hlsdk.types;

namespace amxx {
	namespace detail {
		void AMXX_StartFrame();
		void set_task(hlsdk::duration_t time, std::function<void()> function);
	}
}