module;

export module hlsdk.basemonster;
export import hlsdk.cbase_ext;
export import hlsdk.activity;

export namespace hlsdk {
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