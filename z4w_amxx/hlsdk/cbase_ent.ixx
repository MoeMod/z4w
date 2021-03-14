module;

#include <type_traits>
#include <chrono>

export module hlsdk.cbase:ent;
import :fwd;
import :ehandle;
export import hlsdk.extdll;
export import hlsdk.util;
export import hlsdk.cbase_const;
import hlsdk.monsterevent;
import hlsdk.activity;

using namespace std::chrono_literals;

export namespace hlsdk {

	class CBaseEntity
	{
	protected:
		CBaseEntity() = delete;
		~CBaseEntity() = default;

	public:
		virtual void Spawn(void) {}
		virtual void Precache(void) {}
		virtual void Restart(void) {}
		virtual void KeyValue(KeyValueData* pkvd) { pkvd->fHandled = FALSE; }
		virtual int Save(CSave& save);
		virtual int Restore(CRestore& restore);
		virtual int ObjectCaps(void) { return FCAP_ACROSS_TRANSITION; }
		virtual void Activate(void) {}
		virtual void SetObjectCollisionBox(void);
		virtual int Classify(void) { return CLASS_NONE; }
		virtual void DeathNotice(entvars_t* pevChild) {}
		virtual void TraceAttack(entvars_t* pevAttacker, float flDamage, Vector vecDir, TraceResult* ptr, int bitsDamageType);
		virtual int TakeDamage(entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType);
		virtual int TakeHealth(float flHealth, int bitsDamageType);
		virtual void Killed(entvars_t* pevAttacker, int iGib);
		virtual int BloodColor(void) { return DONT_BLEED; }
		virtual void TraceBleed(float flDamage, Vector vecDir, TraceResult* ptr, int bitsDamageType);
		virtual BOOL IsTriggered(CBaseEntity* pActivator) { return TRUE; }
		virtual CBaseMonster* MyMonsterPointer(void) { return nullptr; }
		virtual CSquadMonster* MySquadMonsterPointer(void) { return nullptr; }
		virtual int GetToggleState(void) { return TS_AT_TOP; }
		virtual void AddPoints(int score, BOOL bAllowNegativeScore) {}
		virtual void AddPointsToTeam(int score, BOOL bAllowNegativeScore) {}
		virtual BOOL AddPlayerItem(CBasePlayerItem* pItem) { return 0; }
		virtual BOOL RemovePlayerItem(CBasePlayerItem* pItem) { return 0; }
		virtual int GiveAmmo(int iAmount, const char* szName, int iMax) { return -1; }
		virtual duration_t GetDelay(void) { return zero_duration; }
		virtual int IsMoving(void) { return pev->velocity != g_vecZero; }
		virtual void OverrideReset(void) {}
		virtual int DamageDecal(int bitsDamageType);
		virtual void SetToggleState(int state) {}
		virtual void StartSneaking(void) {}
		virtual void StopSneaking(void) {}
		virtual BOOL OnControls(entvars_t* onpev) { return FALSE; }
		virtual BOOL IsSneaking(void) { return FALSE; }
		virtual BOOL IsAlive(void) { return (pev->deadflag == DEAD_NO) && pev->health > 0; }
		virtual BOOL IsBSPModel(void) { return pev->solid == SOLID_BSP || pev->movetype == MOVETYPE_PUSHSTEP; }
		virtual BOOL ReflectGauss(void) { return IsBSPModel() && !pev->takedamage; }
		virtual BOOL HasTarget(string_t targetname) { return FStrEq(STRING(targetname), STRING(pev->targetname)); }
		virtual BOOL IsInWorld(void);
		virtual BOOL IsPlayer(void) { return FALSE; }
		virtual BOOL IsNetClient(void) { return FALSE; }
		virtual const char* TeamID(void) { return ""; }
		virtual CBaseEntity* GetNextTarget(void);

		virtual void Think(void) { if (m_pfnThink) (this->*m_pfnThink)(); }
		virtual void Touch(CBaseEntity* pOther) { if (m_pfnTouch) (this->*m_pfnTouch)(pOther); }
		virtual void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) { if (m_pfnUse) (this->*m_pfnUse)(pActivator, pCaller, useType, value); }
		virtual void Blocked(CBaseEntity* pOther) { if (m_pfnBlocked) (this->*m_pfnBlocked)(pOther); }
		virtual CBaseEntity* Respawn(void) { return nullptr; }
		virtual void UpdateOwner(void) {}
		virtual BOOL FBecomeProne(void) { return FALSE; }
		virtual Vector Center(void) { return (pev->absmax + pev->absmin) * 0.5; }
		virtual Vector EyePosition(void) { return pev->origin + pev->view_ofs; }
		virtual Vector EarPosition(void) { return pev->origin + pev->view_ofs; }
		virtual Vector BodyTarget(const Vector& posSrc) { return Center(); }
		virtual int Illumination(void) { return GETENTITYILLUM(ENT(pev)); }
		virtual BOOL FVisible(CBaseEntity* pEntity);
		virtual BOOL FVisible(const Vector& vecOrigin);

	public:
		void SUB_Remove(void);
		void SUB_DoNothing(void);
		void SUB_StartFadeOut(void);
		void SUB_FadeOut(void);
		void SUB_CallUseToggle(void) { Use(this, this, USE_TOGGLE, 0); }
		void SUB_UseTargets(CBaseEntity* pActivator, USE_TYPE useType, float value);

	public:
		void UpdateOnRemove(void);
		int ShouldToggle(USE_TYPE useType, BOOL currentState);
		void FireBullets(ULONG cShots, Vector vecSrc, Vector vecDirShooting, Vector vecSpread, float flDistance, int iBulletType, int iTracerFreq = 4, int iDamage = 0, entvars_t* pevAttacker = nullptr);
		void FireBullets2(ULONG cShots, Vector vecSrc, Vector vecDirShooting, Vector vecSpread, float flDistance, int iBulletType, int iTracerFreq = 4, int iDamage = 0, entvars_t* pevAttacker = nullptr, int iWeaponType = 0);
		Vector FireBullets3(Vector vecSrc, Vector vecDirShooting, float flSpread, float flDistance, int iPenetration, int iBulletType, int iDamage, float flRangeModifier, entvars_t* pevAttacker, bool bPistol, int shared_rand = 0);
		Vector FireBullets4(Vector vecSrc, Vector vecDirShooting, float flSpread, float flDistance, int iPenetration, int iBulletType, int iDamage, float flRangeModifier, entvars_t* pevAttacker, bool bPistol, int shared_rand = 0, int iWeaponType = 0);
		int Intersects(CBaseEntity* pOther);
		void MakeDormant(void);
		int IsDormant(void);
		BOOL IsLockedByMaster(void) { return FALSE; }

	public:
		static CBaseEntity* Instance(edict_t* pent) { return GET_PRIVATE<CBaseEntity>(pent ? pent : ENT(0)); }
		static CBaseEntity* Instance(entvars_t* instpev) { return Instance(ENT(instpev)); }
		static CBaseEntity* Instance(int inst_eoffset) { return Instance(ENT(inst_eoffset)); }

		CBaseMonster* GetMonsterPointer(entvars_t* pevMonster)
		{
			CBaseEntity* pEntity = Instance(pevMonster);

			if (pEntity)
				return pEntity->MyMonsterPointer();

			return nullptr;
		}

		CBaseMonster* GetMonsterPointer(edict_t* pentMonster)
		{
			CBaseEntity* pEntity = Instance(pentMonster);

			if (pEntity)
				return pEntity->MyMonsterPointer();

			return nullptr;
		}

		static CBaseEntity* Create(const char* szName, const Vector& vecOrigin, const Vector& vecAngles, edict_t* pentOwner = nullptr);

		edict_t* edict(void) { return ENT(pev); }
		EOFFSET eoffset(void) { return OFFSET(pev); }
		int entindex(void) { return ENTINDEX(edict()); }

	public:
		// cbase_memory.cpp

		// allocate memory for CBaseEntity with given pev
		void* operator new(size_t stAllocateBlock, entvars_t* newpev) noexcept = delete;
		// free pev  when constructor throws, etc...
		void operator delete(void* pMem, entvars_t* pev) = delete;
		// automatically allocate pev
		void* operator new(size_t stAllocateBlock) = delete;
		// auto remove entity...
		void operator delete(void* pMem) = delete;

	public:
		template <typename T>
		auto SetThink(void (T::* pfn)()) -> typename std::enable_if<std::is_base_of<CBaseEntity, T>::value>::type
		{
			m_pfnThink = static_cast<void (CBaseEntity::*)()>(pfn);
		}
		void SetThink(std::nullptr_t null)
		{
			m_pfnThink = null;
		}
		template <typename T>
		auto SetTouch(void (T::* pfn)(CBaseEntity* pOther)) -> typename std::enable_if<std::is_base_of<CBaseEntity, T>::value>::type
		{
			m_pfnTouch = static_cast<void (CBaseEntity::*)(CBaseEntity*)>(pfn);
		}
		void SetTouch(std::nullptr_t null)
		{
			m_pfnThink = null;
		}
		template <typename T>
		auto SetUse(void (T::* pfn)(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)) -> typename std::enable_if<std::is_base_of<CBaseEntity, T>::value>::type
		{
			m_pfnUse = static_cast<void (CBaseEntity::*)(CBaseEntity*, CBaseEntity*, USE_TYPE, float)>(pfn);
		}
		void SetUse(std::nullptr_t null)
		{
			m_pfnThink = null;
		}
		template <typename T>
		auto SetBlocked(void (T::* pfn)(CBaseEntity* pOther)) -> typename std::enable_if<std::is_base_of<CBaseEntity, T>::value>::type
		{
			m_pfnBlocked = static_cast<void (CBaseEntity::*)(CBaseEntity*)>(pfn);
		}
		void SetBlocked(std::nullptr_t null)
		{
			m_pfnThink = null;
		}

	public:
		static TYPEDESCRIPTION m_SaveData[];

	public:
		entvars_t* pev;
		CBaseEntity* m_pGoalEnt;
		CBaseEntity* m_pLink;
		void (CBaseEntity::* m_pfnThink)(void);
		void (CBaseEntity::* m_pfnTouch)(CBaseEntity* pOther);
		void (CBaseEntity::* m_pfnUse)(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value);
		void (CBaseEntity::* m_pfnBlocked)(CBaseEntity* pOther);
		int current_ammo;
		int currentammo;
		int maxammo_buckshot;
		int ammo_buckshot;
		int maxammo_9mm;
		int ammo_9mm;
		int maxammo_556nato;
		int ammo_556nato;
		int maxammo_556natobox;
		int ammo_556natobox;
		int maxammo_762nato;
		int ammo_762nato;
		int maxammo_45acp;
		int ammo_45acp;
		int maxammo_50ae;
		int ammo_50ae;
		int maxammo_338mag;
		int ammo_338mag;
		int maxammo_57mm;
		int ammo_57mm;
		int maxammo_357sig;
		int ammo_357sig;
		time_point_t m_flStartThrow;
		time_point_t m_flReleaseThrow;
		int m_iSwing;
		bool has_disconnected;
	};



	class CPointEntity : public CBaseEntity
	{
	public:
		void Spawn(void) override;
		int ObjectCaps(void) override { return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION; }
	};

	class CBaseDelay : public CBaseEntity
	{
	public:
		void KeyValue(KeyValueData* pkvd) override;
		int Save(CSave& save) override;
		int Restore(CRestore& restore) override;

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
		int Save(CSave& save) override;
		int Restore(CRestore& restore) override;
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
		void KeyValue(KeyValueData* pkvd) override;
		int Save(CSave& save) override;
		int Restore(CRestore& restore) override;
		int GetToggleState(void) override { return m_toggle_state; }
		duration_t GetDelay(void) override { return m_flWait; }

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

	class CBaseMonster : public CBaseToggle
	{
	public:
		void KeyValue(KeyValueData* pkvd) override;
		void TraceAttack(entvars_t* pevAttacker, float flDamage, Vector vecDir, TraceResult* ptr, int bitsDamageType) override;
		int TakeDamage(entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) override;
		int TakeHealth(float flHealth, int bitsDamageType) override;
		void Killed(entvars_t* pevAttacker, int iGib) override;
		int BloodColor(void) override { return m_bloodColor; }
		BOOL IsAlive(void) override { return (pev->deadflag != DEAD_DEAD); }
		virtual float ChangeYaw(int speed);
		virtual BOOL HasHumanGibs(void);
		virtual BOOL HasAlienGibs(void);
		virtual void FadeMonster(void);
		virtual void GibMonster(void);
		virtual Activity GetDeathActivity(void);
		virtual void BecomeDead(void);
		virtual BOOL ShouldFadeOnDeath(void);
		virtual int IRelationship(CBaseEntity* pTarget);
		virtual void PainSound(void) { return; }
		virtual void ResetMaxSpeed(void) {};
		virtual void ReportAIState(void);
		virtual void MonsterInitDead(void);
		virtual void Look(int iDistance);
		virtual CBaseEntity* BestVisibleEnemy(void);
		virtual BOOL FInViewCone(CBaseEntity* pEntity);
		virtual BOOL FInViewCone(const Vector* pOrigin);

	public:
		void MakeIdealYaw(Vector vecTarget);
		Activity GetSmallFlinchActivity(void);
		BOOL ShouldGibMonster(int iGib);
		void CallGibMonster(void);
		BOOL FCheckAITrigger(void);
		int DeadTakeDamage(entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType);
		float DamageForce(float damage);
		void RadiusDamage(entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int iClassIgnore, int bitsDamageType);
		void RadiusDamage(Vector vecSrc, entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int iClassIgnore, int bitsDamageType);
		void CorpseFallThink(void);
		CBaseEntity* CheckTraceHullAttack(float flDist, int iDamage, int iDmgType);
		void MakeDamageBloodDecal(int cCount, float flNoise, TraceResult* ptr, const Vector& vecDir);
		void BloodSplat(const Vector& vecPos, const Vector& vecDir, int hitgroup, int iDamage);

	public:
		void SetConditions(int iConditions) { m_afConditions |= iConditions; }
		void ClearConditions(int iConditions) { m_afConditions &= ~iConditions; }
		BOOL HasConditions(int iConditions)
		{
			if (m_afConditions & iConditions) return TRUE;
			return FALSE;
		}
		BOOL HasAllConditions(int iConditions)
		{
			if ((m_afConditions & iConditions) == iConditions) return TRUE;
			return FALSE;
		}
		void Remember(int iMemory) { m_afMemory |= iMemory; }
		void Forget(int iMemory) { m_afMemory &= ~iMemory; }
		BOOL HasMemory(int iMemory)
		{
			if (m_afMemory & iMemory) return TRUE;
			return FALSE;
		}
		BOOL HasAllMemories(int iMemory)
		{
			if ((m_afMemory & iMemory) == iMemory) return TRUE;
			return FALSE;
		}
		void StopAnimation(void) { pev->framerate = 0; }

	public:
		Activity m_Activity;
		Activity m_IdealActivity;
		int m_LastHitGroup;
		int m_bitsDamageType;
		BYTE m_rgbTimeBasedDamage[CDMG_TIMEBASED];
		MONSTERSTATE m_MonsterState;
		MONSTERSTATE m_IdealMonsterState;
		int m_afConditions;
		int m_afMemory;
		duration_t m_flNextAttack;
		EHANDLE m_hEnemy;
		EHANDLE m_hTargetEnt;
		float m_flFieldOfView;
		int m_bloodColor;
		Vector m_HackedGunPos;
		Vector m_vecEnemyLKP;
	};
}