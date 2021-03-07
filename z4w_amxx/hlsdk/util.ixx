module;

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <limits>

export module hlsdk.util;

export import hlsdk.extdll;
export import hlsdk.cvardef;
export import hlsdk.enginecallback;
export import hlsdk.globals;

export namespace hlsdk
{
	extern globalvars_t* gpGlobals;

	typedef struct hudtextparms_s
	{
		float		x;
		float		y;
		int			effect;
		byte		r1, g1, b1, a1;
		byte		r2, g2, b2, a2;
		duration_t		fadeinTime;
		duration_t		fadeoutTime;
		duration_t		holdTime;
		duration_t		fxTime;
		int			channel;
	} hudtextparms_t;

	class UTIL_GroupTrace
	{
	public:
		UTIL_GroupTrace(int groupmask, int op);
		~UTIL_GroupTrace();
	private:
		int m_oldgroupmask;
		int m_oldgroupop;
	};

	extern int g_groupmask;
	extern int g_groupop;

	inline void	PLAYBACK_EVENT(int flags, const edict_t* who, unsigned short index) { return PLAYBACK_EVENT_FULL(flags, who, index, 0, (float*)&g_vecZero, (float*)&g_vecZero, 0.0, 0.0, 0, 0, 0, 0); }
	inline void	PLAYBACK_EVENT_DELAY(int flags, const edict_t* who, unsigned short index, float delay) { return PLAYBACK_EVENT_FULL(flags, who, index, delay, (float*)&g_vecZero, (float*)&g_vecZero, 0.0, 0.0, 0, 0, 0, 0); }

	constexpr string_t iStringNull{};

	inline const char* STRING(string_t offset)
	{
		return gpGlobals->pStringBase + (ptrdiff_t)(offset);
	}

	inline string_t MAKE_STRING(const char* szValue)
	{
		ptrdiff_t ptrdiff = szValue - STRING(0);
		if (ptrdiff > std::numeric_limits<int>::max() || ptrdiff < std::numeric_limits<int>::min())
			return ALLOC_STRING(szValue);
		else
			return (int)ptrdiff;
	}

	inline void MAKE_STRING_CLASS(const char* str, entvars_t* pev)
	{
		pev->classname = (string_t)MAKE_STRING(str);
	}

	inline edict_t* FIND_ENTITY_BY_CLASSNAME(edict_t* entStart, const char* pszName)
	{
		return FIND_ENTITY_BY_STRING(entStart, "classname", pszName);
	}

	inline edict_t* FIND_ENTITY_BY_TARGETNAME(edict_t* entStart, const char* pszName)
	{
		return FIND_ENTITY_BY_STRING(entStart, "targetname", pszName);
	}

#if defined(_DEBUG) && !defined(CLIENT_DLL)
	edict_t* DBG_EntOfVars(const entvars_t* pev)
	{
		if (pev->pContainingEntity != NULL)
			return pev->pContainingEntity;

		ALERT(at_console, "entvars_t pContainingEntity is NULL, calling into engine");

		edict_t* pent = (*g_engfuncs.pfnFindEntityByVars)((entvars_t*)pev);

		if (pent == NULL)
			ALERT(at_console, "DAMN!  Even the engine couldn't FindEntityByVars!");

		((entvars_t*)pev)->pContainingEntity = pent;
		return pent;
	}
	inline edict_t* ENT(const entvars_t* pev) { return DBG_EntOfVars(pev); }
#else
	inline edict_t* ENT(const entvars_t* pev)
	{
		return pev->pContainingEntity;
	}
#endif

	inline edict_t* ENT(EOFFSET eoffset)
	{
		return (*g_engfuncs.pfnPEntityOfEntOffset)(eoffset);
	}

	inline EOFFSET OFFSET(const edict_t* pent)
	{
#if _DEBUG
		if (!pent)
			ALERT(at_error, "Bad ent in OFFSET()\n");
#endif
		return (*g_engfuncs.pfnEntOffsetOfPEntity)(pent);
	}

	inline EOFFSET OFFSET(const entvars_t* pev)
	{
		return OFFSET(ENT(pev));
	}

	inline entvars_t* VARS(edict_t* pent)
	{
		if (!pent)
			return nullptr;

		return &pent->v;
	}

	inline entvars_t* VARS(EOFFSET eoffset)
	{
		return VARS(ENT(eoffset));
	}

	inline int ENTINDEX(const edict_t* pEdict)
	{
		return (*g_engfuncs.pfnIndexOfEdict)(pEdict);
	}

	inline edict_t* INDEXENT(int iEdictNum)
	{
		return (*g_engfuncs.pfnPEntityOfEntIndex)(iEdictNum);
	}

	inline void MESSAGE_BEGIN(int msg_dest, int msg_type, const float* pOrigin, entvars_t* ent)
	{
		MESSAGE_BEGIN(msg_dest, msg_type, pOrigin, ENT(ent));
	}

	inline BOOL FNullEnt(EOFFSET eoffset)
	{
		return eoffset == 0;
	}
	inline BOOL FNullEnt(const edict_t* pent)
	{
		return pent == nullptr || FNullEnt(OFFSET(pent));
	}
	inline BOOL FNullEnt(entvars_t* pev)
	{
		return pev == nullptr || FNullEnt(OFFSET(pev));
	}

	inline BOOL FStringNull(int iString)
	{
		return (iString == iStringNull);
	}

	inline BOOL FStrEq(const char* sz1, const char* sz2)
	{
		return (strcmp(sz1, sz2) == 0);
	}

	inline BOOL FClassnameIs(entvars_t* pev, const char* szClassname)
	{
		return FStrEq(STRING(pev->classname), szClassname);
	}

	inline BOOL FClassnameIs(edict_t* pent, const char* szClassname)
	{
		//TODO: check is null?
		return FStrEq(STRING(VARS(pent)->classname), szClassname);
	}

	inline void UTIL_MakeVectorsPrivate(Vector vecAngles, float* p_vForward, float* p_vRight, float* p_vUp)
	{
		g_engfuncs.pfnAngleVectors(vecAngles, p_vForward, p_vRight, p_vUp);
	}



	char* UTIL_VarArgs(const char* format, ...)
	{
		va_list		argptr;
		static char		string[1024];

		va_start(argptr, format);
		vsnprintf(string, sizeof(string), format, argptr);
		va_end(argptr);

		return string;
	}


	//=========================================================
	// UTIL_LogPrintf - Prints a logged message to console.
	// Preceded by LOG: ( timestamp ) < message >
	//=========================================================
	void UTIL_LogPrintf(const char* fmt, ...)
	{
		va_list			argptr;
		static char		string[1024];

		va_start(argptr, fmt);
		vsnprintf(string, sizeof(string), fmt, argptr);
		va_end(argptr);

		// Print to server console
		ALERT(at_logged, "%s", string);
	}

	EngineClock::time_point get_gametime() noexcept
	{
		return gpGlobals->time;
	}

	EngineClock::time_point EngineClock::now() noexcept
	{
		return gpGlobals->time;
	}
}