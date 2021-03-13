module;

#include <chrono>

export module hlsdk.player;
export import hlsdk.basemonster;
export import hlsdk.pm_materials;
export import hlsdk.player_const;
export import hlsdk.weapons_buy;
export import hlsdk.cdll_dll;
export import hlsdk.hintmessage;
export import hlsdk.player_signal;

using namespace std::chrono_literals;

export namespace hlsdk {

	class CWeaponBox;
	class CBasePlayerWeapon;

	class CBasePlayer : public CBaseMonster
	{
	public:
		CBasePlayer() = delete;
		~CBasePlayer() = delete;

		void Spawn() override;
		void Precache() override;
		void Restart(void) override;
		int Save(CSave& save) override;
		int Restore(CRestore& restore) override;
		int ObjectCaps() override { return (CBaseMonster::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }
		int Classify() override;
		void TraceAttack(entvars_t* pevAttacker, float flDamage, Vector vecDir, TraceResult* ptr, int bitsDamageType) override;
		int TakeDamage(entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) override;
		int TakeHealth(float flHealth, int bitsDamageType) override;
		void Killed(entvars_t* pevAttacker, int iGib) override;
		void AddPoints(int score, BOOL bAllowNegativeScore) override;
		void AddPointsToTeam(int score, BOOL bAllowNegativeScore) override;
		BOOL AddPlayerItem(CBasePlayerItem* pItem) override;
		BOOL RemovePlayerItem(CBasePlayerItem* pItem) override;
		int GiveAmmo(int iAmount, const char* szName, int iMax) override;
		void StartSneaking() override { m_tSneaking = gpGlobals->time - 1s; }
		void StopSneaking() override { m_tSneaking = gpGlobals->time + 30s; }
		BOOL IsSneaking() override { return m_tSneaking <= gpGlobals->time; }
		BOOL IsAlive() override { return (pev->deadflag == DEAD_NO && pev->health > 0.0f); }
		BOOL IsPlayer() override { return (pev->flags & FL_SPECTATOR) != FL_SPECTATOR; }
		BOOL IsNetClient() override { return TRUE; }
		const char* TeamID() override;
		BOOL FBecomeProne() override;
		Vector BodyTarget(const Vector& posSrc) override { return Center() + pev->view_ofs * RANDOM_FLOAT(0.5f, 1.1f); }
		int Illumination() override;
		BOOL ShouldFadeOnDeath() override { return FALSE; }
		void ResetMaxSpeed() override;
		virtual void Jump();
		virtual void Duck();
		virtual void PreThink();
		virtual void PostThink();
		virtual Vector GetGunPosition();
		virtual BOOL IsBot() { return FALSE; }
		virtual void UpdateClientData();
		virtual void ImpulseCommands();
		virtual void RoundRespawn();
		virtual Vector GetAutoaimVector(float flDelta);
		virtual void Blind(duration_t flUntilTime, duration_t flHoldTime, duration_t flFadeTime, int iAlpha);
		virtual void OnTouchingWeapon(CWeaponBox* pWeapon) {}

	public:
		void SpawnClientSideCorpse();
		void Observer_FindNextPlayer(bool bReverse, const char* name = NULL);
		CBaseEntity* Observer_IsValidTarget(int iPlayerIndex, bool bSameTeam);
		void Observer_HandleButtons();
		void Observer_SetMode(int iMode);
		void Observer_CheckTarget();
		void Observer_CheckProperties();
		int IsObserver() { return pev->iuser1; }
		void PlantC4();
		void Radio(const char* msg_id, const char* msg_verbose = NULL, short pitch = 100, bool showIcon = true);
		CBasePlayer* GetNextRadioRecipient(CBasePlayer* pStartPlayer);
		void SmartRadio();
		void ThrowWeapon(const char* pszItemName);
		void ThrowPrimary();
		void AddAccount(int amount, bool bTrackChange = true);
		void Disappear();
		void MakeVIP();
		bool CanPlayerBuy(bool display = false);
		void SwitchTeam();
		void TabulateAmmo();
		void Pain(int m_LastHitGroup, bool HasArmour);
		BOOL IsBombGuy();
		bool IsLookingAtPosition(Vector* pos, float angleTolerance = 20.0f);
		void Reset();
		void SetScoreboardAttributes(CBasePlayer* destination = NULL);
		void RenewItems();
		void PackDeadPlayerItems();
		void GiveDefaultItems();
		void RemoveAllItems(BOOL removeSuit);
		void SetBombIcon(BOOL bFlash = FALSE);
		void SetProgressBarTime(int time);
		void SetProgressBarTime2(int time, duration_t timeElapsed);
		void SetPlayerModel(BOOL HasC4);
		void SetNewPlayerModel(const char* modelName);
		BOOL SwitchWeapon(CBasePlayerItem* pWeapon);
		void CheckPowerups(entvars_t* pev);
		bool CanAffordPrimary();
		bool CanAffordPrimaryAmmo();
		bool CanAffordSecondaryAmmo();
		bool CanAffordArmor();
		bool CanAffordDefuseKit();
		bool CanAffordGrenade();
		bool NeedsPrimaryAmmo();
		bool NeedsSecondaryAmmo();
		bool NeedsArmor();
		bool NeedsDefuseKit();
		bool NeedsGrenade();
		BOOL IsOnLadder();
		BOOL FlashlightIsOn();
		void FlashlightTurnOn();
		void FlashlightTurnOff();
		void UpdatePlayerSound();
		void DeathSound();
		void SetAnimation(PLAYER_ANIM playerAnim);
		void SetWeaponAnimType(const char* szExtention)/* { Q_strcpy(m_szAnimExtention, szExtention); }*/;
		void CheatImpulseCommands(int iImpulse);
		void StartDeathCam();
		void StartObserver(Vector vecPosition, Vector vecViewAngle);
		void HandleSignals();
		void DropPlayerItem(const char* pszItemName);
		BOOL HasPlayerItem(CBasePlayerItem* pCheckItem);
		BOOL HasNamedPlayerItem(const char* pszItemName);
		BOOL HasWeapons();
		void SelectPrevItem(int iItem);
		void SelectNextItem(int iItem);
		void SelectLastItem();
		void SelectItem(const char* pstr);
		void ItemPreFrame();
		void ItemPostFrame();
		void GiveNamedItem(const char* pszName);
		void EnableControl(BOOL fControl);
		bool HintMessage(const char* pMessage, BOOL bDisplayIfPlayerDead = FALSE, BOOL bOverride = FALSE);
		void SendAmmoUpdate();
		void SendFOV(int fov);
		void WaterMove();
		void PlayerDeathThink();
		void PlayerUse();
		void HostageUsed();
		void JoiningThink();
		void RemoveLevelText();
		void MenuPrint(const char* msg);
		void ResetMenu();
		void SyncRoundTimer();
		void CheckSuitUpdate();
		void SetSuitUpdate(const char* name = nullptr, int fgroup = 0, int iNoRepeatTime = 0);
		void UpdateGeigerCounter();
		void CheckTimeBasedDamage();
		void BarnacleVictimBitten(entvars_t* pevBarnacle);
		void BarnacleVictimReleased();
		static int GetAmmoIndex(const char* psz);
		int AmmoInventory(int iAmmoIndex);
		void ResetAutoaim();
		Vector AutoaimDeflection(Vector& vecSrc, float flDist, float flDelta);
		void ForceClientDllUpdate();
		void DeathMessage(entvars_t* pevAttacker) {};
		void SetCustomDecalFrames(int nFrames);
		int GetCustomDecalFrames();
		void InitStatusBar();
		void UpdateStatusBar();
		void StudioEstimateGait();
		void StudioPlayerBlend(int* pBlend, float* pPitch);
		void CalculatePitchBlend();
		void CalculateYawBlend();
		void StudioProcessGait();
		void SendHostagePos();
		void SendHostageIcons();
		void ResetStamina();
		BOOL IsArmored(int nHitGroup);
		BOOL ShouldDoLargeFlinch(int nHitGroup, int nGunType);
		void SetPrefsFromUserinfo(char* infobuffer);
		void SendWeatherInfo();
		void UpdateShieldCrosshair(bool draw);
		bool HasShield();
		bool IsProtectedByShield();
		void RemoveShield();
		void DropShield(bool bDeploy = true);
		void GiveShield(bool bDeploy = true);
		bool IsHittingShield(Vector& vecDirection, TraceResult* ptr);
		bool SelectSpawnSpot(const char* pEntClassName, CBaseEntity*& pSpot);
		bool IsReloading();
		bool IsBlind() const { return (m_blindUntilTime > gpGlobals->time); }
		bool IsAutoFollowAllowed() const { return (gpGlobals->time > m_allowAutoFollowTime); }
		void InhibitAutoFollow(duration_t duration) { m_allowAutoFollowTime = gpGlobals->time + duration; }
		void AllowAutoFollow() { m_allowAutoFollowTime = {}; }
		void ClearAutoBuyData();
		void AddAutoBuyData(const char* str);
		void AutoBuy();
		void ClientCommand(const char* cmd, const char* arg1 = NULL, const char* arg2 = NULL, const char* arg3 = NULL);
		void PrioritizeAutoBuyString(char* autobuyString, const char* priorityString);
		const char* PickPrimaryCareerTaskWeapon();
		const char* PickSecondaryCareerTaskWeapon();
		const char* PickFlashKillWeaponString();
		const char* PickGrenadeKillWeaponString();
		bool ShouldExecuteAutoBuyCommand(AutoBuyInfoStruct* commandInfo, bool boughtPrimary, bool boughtSecondary);
		void PostAutoBuyCommandProcessing(AutoBuyInfoStruct* commandInfo, bool& boughtPrimary, bool& boughtSecondary);
		void ParseAutoBuyString(const char* string, bool& boughtPrimary, bool& boughtSecondary);
		AutoBuyInfoStruct* GetAutoBuyCommandInfo(const char* command);
		void InitRebuyData(const char* str);
		void BuildRebuyStruct();
		void Rebuy();
		void RebuyPrimaryWeapon();
		void RebuyPrimaryAmmo();
		void RebuySecondaryWeapon();
		void RebuySecondaryAmmo();
		void RebuyHEGrenade();
		void RebuyFlashbang();
		void RebuySmokeGrenade();
		void RebuyDefuser();
		void RebuyNightVision();
		void RebuyArmor();
		void UpdateLocation(bool forceUpdate = false);
		void SetObserverAutoDirector(bool val) { m_bObserverAutoDirector = val; }
		bool IsObservingPlayer(CBasePlayer* pPlayer);
		bool CanSwitchObserverModes() const { return m_canSwitchObserverModes; }
		void Intense()
		{
			//m_musicState = INTENSE;
			//m_intenseTimestamp = gpGlobals->time;
		}
	public:
		enum
		{
			MaxLocationLen = 32
		};

		int random_seed;
		unsigned short m_usPlayerBleed;
		EHANDLE m_hObserverTarget;
		time_point_t m_flNextObserverInput;
		int m_iObserverWeapon;
		int m_iObserverC4State;
		bool m_bObserverHasDefuser;
		int m_iObserverLastMode;
		time_point_t m_flFlinchTime;
		time_point_t m_flAnimTime;
		bool m_bHighDamage;
		float m_flVelocityModifier;
		int m_iLastZoom;
		bool m_bResumeZoom;
		time_point_t m_flEjectBrass;
		int m_iKevlar;
		bool m_bNotKilled;
		TeamName m_iTeam;
		int m_iAccount;
		bool m_bHasPrimary;
		time_point_t m_flDeathThrowTime;
		int m_iThrowDirection;
		time_point_t m_flLastTalk;
		bool m_bJustConnected;
		bool m_bContextHelp;
		JoinState m_iJoiningState;
		CBaseEntity* m_pIntroCamera;
		time_point_t m_fIntroCamTime;
		time_point_t m_fLastMovement;
		bool m_bMissionBriefing;
		bool m_bTeamChanged;
		ModelName m_iModelName;
		int m_iTeamKills;
		int m_iIgnoreGlobalChat;
		bool m_bHasNightVision;
		bool m_bNightVisionOn;
		Vector m_vRecentPath[MAX_RECENT_PATH];
		time_point_t m_flIdleCheckTime;
		time_point_t m_flRadioTime;
		int m_iRadioMessages;
		bool m_bIgnoreRadio;
		bool m_bHasC4;
		bool m_bHasDefuser;
		bool m_bKilledByBomb;
		Vector m_vBlastVector;
		bool m_bKilledByGrenade;
		CHintMessageQueue m_hintMessageQueue;
		int m_flDisplayHistory;
		_Menu m_iMenu;
		int m_iChaseTarget;
		CBaseEntity* m_pChaseTarget;
		float m_fCamSwitch;
		bool m_bEscaped;
		bool m_bIsVIP;
		EngineClock::time_point m_tmNextRadarUpdate;
		Vector m_vLastOrigin;
		int m_iCurrentKickVote;
		time_point_t m_flNextVoteTime;
		bool m_bJustKilledTeammate;
		int m_iHostagesKilled;
		int m_iMapVote;
		bool m_bCanShoot;
		time_point_t m_flLastFired;
		time_point_t m_flLastAttackedTeammate;
		bool m_bHeadshotKilled;
		bool m_bPunishedForTK;
		bool m_bReceivesNoMoneyNextRound;
		time_point_t m_iTimeCheckAllowed;
		bool m_bHasChangedName;
		char m_szNewName[MAX_PLAYER_NAME_LENGTH];
		bool m_bIsDefusing;
		time_point_t m_tmHandleSignals;
		CUnifiedSignals m_signals;
		edict_t* m_pentCurBombTarget;
		int m_iPlayerSound;
		int m_iTargetVolume;
		int m_iWeaponVolume;
		int m_iExtraSoundTypes;
		int m_iWeaponFlash;
		float m_flStopExtraSoundTime;
		time_point_t m_flFlashLightTime;
		int m_iFlashBattery;
		int m_afButtonLast;
		int m_afButtonPressed;
		int m_afButtonReleased;
		edict_t* m_pentSndLast;
		float m_flSndRoomtype;
		float m_flSndRange;
		float m_flFallVelocity;
		int m_rgItems[MAX_ITEMS];
		int m_fNewAmmo;
		unsigned int m_afPhysicsFlags;
		time_point_t m_fNextSuicideTime;
		time_point_t m_flTimeStepSound;
		time_point_t m_flTimeWeaponIdle;
		time_point_t m_flSwimTime;
		time_point_t m_flDuckTime;
		time_point_t m_flWallJumpTime;
		time_point_t m_flSuitUpdate;
		int m_rgSuitPlayList[CSUITPLAYLIST];
		int m_iSuitPlayNext;
		int m_rgiSuitNoRepeat[CSUITNOREPEAT];
		float m_rgflSuitNoRepeatTime[CSUITNOREPEAT];
		int m_lastDamageAmount;
		time_point_t m_tbdPrev;
		float m_flgeigerRange;
		time_point_t m_flgeigerDelay;
		int m_igeigerRangePrev;
		int m_iStepLeft;
		char m_szTextureName[CBTEXTURENAMEMAX];
		char m_chTextureType;
		int m_idrowndmg;
		int m_idrownrestored;
		int m_bitsHUDDamage;
		BOOL m_fInitHUD;
		BOOL m_fGameHUDInitialized;
		int m_iTrain;
		BOOL m_fWeapon;
		EHANDLE m_pTank;
		time_point_t m_fDeadTime;
		BOOL m_fNoPlayerSound;
		BOOL m_fLongJump;
		time_point_t m_tSneaking;
		int m_iUpdateTime;
		int m_iClientHealth;
		int m_iClientBattery;
		int m_iHideHUD;
		int m_iClientHideHUD;
		int m_iFOV;
		int m_iClientFOV;
		int m_iNumSpawns;
		CBaseEntity* m_pObserver;
		CBasePlayerItem* m_rgpPlayerItems[MAX_ITEM_TYPES];
		CBasePlayerItem* m_pActiveItem;
		CBasePlayerItem* m_pClientActiveItem;
		CBasePlayerItem* m_pLastItem;
		int m_rgAmmo[MAX_AMMO_SLOTS];
		int m_rgAmmoLast[MAX_AMMO_SLOTS];
		Vector m_vecAutoAim;
		BOOL m_fOnTarget;
		int m_iDeaths;
		int m_izSBarState[SBAR_END];
		time_point_t m_flNextSBarUpdateTime;
		time_point_t m_flStatusBarDisappearDelay;
		char m_SbarString0[SBAR_STRING_SIZE];
		int m_lastx;
		int m_lasty;
		int m_nCustomSprayFrames;
		time_point_t m_flNextDecalTime;
		char m_szTeamName[TEAM_NAME_LENGTH];

		static TYPEDESCRIPTION m_playerSaveData[40];

		/*protected:*/
		int m_modelIndexPlayer;
		char m_szAnimExtention[32];
		int m_iGaitsequence;

		float m_flGaitframe;
		float m_flGaityaw;
		Vector m_prevgaitorigin;
		float m_flPitch;
		float m_flYaw;
		float m_flGaitMovement;
		int m_iAutoWepSwitch;
		bool m_bVGUIMenus;
		bool m_bShowHints;
		bool m_bShieldDrawn;
		bool m_bOwnsShield;
		bool m_bWasFollowing;
		time_point_t m_flNextFollowTime;
		float m_flYawModifier;
		time_point_t m_blindUntilTime;
		time_point_t m_blindStartTime;
		duration_t m_blindHoldTime;
		duration_t m_blindFadeTime;
		int m_blindAlpha;
		time_point_t m_allowAutoFollowTime;
		char m_autoBuyString[MAX_AUTOBUY_LENGTH];
		std::unique_ptr<char[]> m_rebuyString;
		RebuyStruct m_rebuyStruct;
		bool m_bIsInRebuy;
		time_point_t m_flLastUpdateTime;
		char m_lastLocation[MaxLocationLen];
		time_point_t m_progressStart;
		time_point_t m_progressEnd;
		bool m_bObserverAutoDirector;
		bool m_canSwitchObserverModes;
		float m_heartBeatTime;
		float m_intenseTimestamp;
		float m_silentTimestamp;
		MusicState m_musicState;
		time_point_t m_flLastCommandTime[8];
	};
}