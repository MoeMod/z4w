module;
#include "amxmodx_detail.h"
export module amxx.amxmodx_detail;
import hlsdk.types;
import amxx.amxmodx_timer;

export namespace amxx {
	namespace detail {
		void StartFrame()
		{
			AMXX_StartFrame();
		}
	}
}