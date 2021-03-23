module;
#include <functional>
#include <system_error>
export module amxx.amxmodx_detail;
import hlsdk.engine;

using namespace hlsdk;

export namespace amxx {
	namespace detail {
		void StartFrame();
		void set_task(hlsdk::duration_t time, std::function<void(std::error_code)> function, int taskid);
		std::size_t remove_task(int taskid);
		std::size_t task_count(int taskid);
		bool task_exists(int taskid);
		void RequestFrame(std::function<void()> func);

		void MessageBegin(int msg_dest, int msg_type, const float* pOrigin, edict_t* ed);
		void MessageEnd();
		void WriteByte(int iValue);
		void WriteChar(int iValue);
		void WriteShort(int iValue);
		void WriteLong(int iValue);
		void WriteAngle(float fValue);
		void WriteCoord(float fValue);
		void WriteString(const char *sz);
		void WriteEntity(int iValue);
	}
}