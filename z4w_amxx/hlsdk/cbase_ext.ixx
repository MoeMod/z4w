module;

#include <chrono>

export module hlsdk.cbase_ext;
export import hlsdk.cbase;
export import hlsdk.monsterevent;
export import hlsdk.ehandle;

using namespace std::chrono_literals;

export namespace hlsdk {

	class CPointEntity : public CBaseEntity
	{
	public:
		void Spawn(void);
		int ObjectCaps(void) { return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION; }
	};

	class CBaseDelay : public CBaseEntity
	{
	public:
		void KeyValue(KeyValueData* pkvd);
		int Save(CSave& save);
		int Restore(CRestore& restore);

	public:
		void SUB_UseTargets(CBaseEntity* pActivator, USE_TYPE useType, float value);

	public:
		void DelayThink(void);

	public:
		static TYPEDESCRIPTION m_SaveData[];

	public:
		duration_t m_flDelay;
		int m_iszKillTarget;
	};

	class CBaseAnimating : public CBaseDelay
	{
	public:
		int Save(CSave& save);
		int Restore(CRestore& restore);
		virtual void HandleAnimEvent(MonsterEvent_t* pEvent) {}

	public:
		duration_t StudioFrameAdvance(duration_t flInterval = {});
		int GetSequenceFlags(void);
		int LookupActivity(int activity);
		int LookupActivityHeaviest(int activity);
		int LookupSequence(const char* label);
		void ResetSequenceInfo(void);
		void DispatchAnimEvents(duration_t flFutureInterval = 0.1s);
		float SetBoneController(int iController, float flValue);
		void InitBoneControllers(void);
		float SetBlending(int iBlender, float flValue);
		void GetBonePosition(int iBone, Vector& origin, Vector& angles);
		void GetAutomovement(Vector& origin, Vector& angles, float flInterval = 0.1);
		int FindTransition(int iEndingSequence, int iGoalSequence, int* piDir);
		void GetAttachment(int iAttachment, Vector& origin, Vector& angles);
		void SetBodygroup(int iGroup, int iValue);
		int GetBodygroup(int iGroup);
		int ExtractBbox(int sequence, float* mins, float* maxs);
		void SetSequenceBox(void);

	public:
		static TYPEDESCRIPTION m_SaveData[];

	public:
		float m_flFrameRate;
		float m_flGroundSpeed;
		time_point_t m_flLastEventCheck;
		BOOL m_fSequenceFinished;
		BOOL m_fSequenceLoops;
	};

	class CBaseToggle : public CBaseAnimating
	{
	public:
		void KeyValue(KeyValueData* pkvd);
		int Save(CSave& save);
		int Restore(CRestore& restore);
		int GetToggleState(void) { return m_toggle_state; }
		duration_t GetDelay(void) { return m_flWait; }

	public:
		void LinearMove(Vector vecDest, float flSpeed);
		void LinearMoveDone(void);
		void AngularMove(Vector vecDestAngle, float flSpeed);
		void AngularMoveDone(void);
		BOOL IsLockedByMaster(void);

	public:
		static float AxisValue(int flags, const Vector& angles);
		static void AxisDir(entvars_t* pev);
		static float AxisDelta(int flags, const Vector& angle1, const Vector& angle2);

	public:
		static TYPEDESCRIPTION m_SaveData[];

	public:
		TOGGLE_STATE m_toggle_state;
		time_point_t m_flActivateFinished;
		float m_flMoveDistance;
		duration_t m_flWait;
		float m_flLip;
		float m_flTWidth;
		float m_flTLength;
		Vector m_vecPosition1;
		Vector m_vecPosition2;
		Vector m_vecAngle1;
		Vector m_vecAngle2;
		int m_cTriggersLeft;
		float m_flHeight;
		EHANDLE m_hActivator;
		void (CBaseToggle::* m_pfnCallWhenMoveDone)(void);
		Vector m_vecFinalDest;
		Vector m_vecFinalAngle;
		int m_bitsDamageInflict;
		string_t m_sMaster;

	public:
		template <typename T>
		auto SetMoveDone(void (T::* pfn)(void)) -> typename std::enable_if<std::is_base_of<CBaseToggle, T>::value>::type
		{
			m_pfnCallWhenMoveDone = static_cast<void (CBaseToggle::*)(void)>(pfn);
		}
	};

}