module;
#include <Windows.h>

export module x_hook;
export import metahook;
export import hlsdk.consts;

using namespace metahook;
using namespace hlsdk;

export namespace x_hook {
	HMODULE g_hEngine = 0;
	void *g_dwEngineBase = 0;
	DWORD g_dwEngineSize = 0;
	DWORD g_dwEngineBuildnum = 0;
	DWORD g_dwDataSize = 0x02FFFFFF - 0x01D00000;

	void PatchEngineSolid();

	void plugin_init()
	{
		g_hEngine = g_pMetaHookAPI->GetEngineModule();
		g_dwEngineBase = reinterpret_cast<void*>(g_pMetaHookAPI->GetEngineBase());
		g_dwEngineSize = g_pMetaHookAPI->GetEngineSize();
		g_dwEngineSize = g_pMetaHookAPI->GetEngineBuildnum();

		PatchEngineSolid();
	}

	void PatchEngineSolid()
	{
		constexpr char ANY = 0x2A;
		constexpr char END = '\0';
		// SV_ClipToLinks
		// if (touch->v.solid != SOLID_SLIDEBOX)
#ifdef _WIN32
		char SIG_SV_ClipToLinks[] = {0x55,0x8B,0xEC,0x83,0xEC,ANY,0x53,0x8B,0x5D,ANY,0x56,0x57,0x8B,0x7D,0x08,0x8B,0x47,ANY,0x8D,0x4F,ANY,0x3B,0xC1,0x0F,0x84,ANY,ANY,ANY,ANY,0x8B,0x48,ANY,0x8D,0x70,ANY,0x89,END};
		auto pfnSV_ClipToLinks = g_pMetaHookAPI->SearchPattern(g_dwEngineBase, g_dwDataSize, SIG_SV_ClipToLinks, sizeof(SIG_SV_ClipToLinks) - 1);
		char SIG_EngineSolidCheck[] = { 0x83,0xF9,0x03,0x74,ANY,0x8B,0x53,0x3C,0x8B,0x43,0x38,0x52,0x50,0x56,0xE8,END };
		auto pEngineSolidCheck = g_pMetaHookAPI->SearchPattern(pfnSV_ClipToLinks, 0x200, SIG_EngineSolidCheck, sizeof(SIG_EngineSolidCheck) - 1);
#elif __linux__ // TODO
		auto pfnSV_ClipToLinks = dlsym(g_hEngine, "SV_ClipToLinks"); // export
		char SIG_EngineSolidCheck[] = { 0x83, 0xF8, 0x03, 0x74, ANY, 0x8B, 0x46, ANY, 0x89, ANY, ANY, ANY, 0x8B, 0x46, END };
		auto pEngineSolidCheck = findsig(pfnSV_ClipToLinks, 0x200, SIG_EngineSolidCheck, sizeof(SIG_EngineSolidCheck) - 1);
#endif
		// SOLID_SLIDEBOX(3) -> SOLID_TRIGGER(1)
#ifdef _WIN32
		// 83 F9 03                                      cmp     ecx, 3
		g_pMetaHookAPI->WriteBYTE(reinterpret_cast<char*>(pEngineSolidCheck) + 2, SOLID_TRIGGER);
#elif __linux__
		// 83 F8 03                                      cmp     eax, 3
		g_pMetaHookAPI->WriteBYTE(reinterpret_cast<char*>(pEngineSolidCheck) + 2, SOLID_TRIGGER);
#endif
	}

}
