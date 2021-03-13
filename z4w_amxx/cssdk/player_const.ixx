module;
#include <chrono>

export module cssdk.player_const;
export import hlsdk.types;

using namespace std::chrono_literals;

export namespace cssdk {
	using namespace hlsdk;

	typedef enum
	{
		PLAYER_IDLE,
		PLAYER_WALK,
		PLAYER_JUMP,
		PLAYER_SUPERJUMP,
		PLAYER_DIE,
		PLAYER_ATTACK1,
		PLAYER_ATTACK2,
		PLAYER_FLINCH,
		PLAYER_LARGE_FLINCH,
		PLAYER_RELOAD,
		PLAYER_HOLDBOMB

	} PLAYER_ANIM;

	typedef enum
	{
		Menu_OFF,
		Menu_ChooseTeam,
		Menu_IGChooseTeam,
		Menu_ChooseAppearance,
		Menu_Buy,
		Menu_BuyPistol,
		Menu_BuyRifle,
		Menu_BuyMachineGun,
		Menu_BuyShotgun,
		Menu_BuySubMachineGun,
		Menu_BuyItem,
		Menu_Radio1,
		Menu_Radio2,
		Menu_Radio3,
		Menu_ClientBuy,
		Menu_ZbsUpgrade

	} _Menu;

	typedef enum : int
	{
		UNASSIGNED,
		TERRORIST,
		CT,
		SPECTATOR,

	} TeamName;

	typedef enum : int
	{
		MODEL_UNASSIGNED,
		MODEL_URBAN,
		MODEL_TERROR,
		MODEL_LEET,
		MODEL_ARCTIC,
		MODEL_GSG9,
		MODEL_GIGN,
		MODEL_SAS,
		MODEL_GUERILLA,
		MODEL_VIP,
		MODEL_MILITIA,
		MODEL_SPETSNAZ,

		MODEL_ZOMBIE_HOST,
		MODEL_ZOMBIE_ORIGIN,

	} ModelName;

	typedef enum : int
	{
		JOINED,
		SHOWLTEXT,
		READINGLTEXT,
		SHOWTEAMSELECT,
		PICKINGTEAM,
		GETINTOGAME

	} JoinState;

	typedef enum : int
	{
		CMD_SAY = 0,
		CMD_SAYTEAM,
		CMD_FULLUPDATE,
		CMD_VOTE,
		CMD_VOTEMAP,
		CMD_LISTMAPS,
		CMD_LISTPLAYERS,
		CMD_NIGHTVISION,
		COMMANDS_TO_TRACK,

	} TrackCommands;

	typedef struct
	{
		int m_primaryWeapon;
		int m_primaryAmmo;
		int m_secondaryWeapon;
		int m_secondaryAmmo;
		int m_heGrenade;
		int m_flashbang;
		int m_smokeGrenade;
		int m_defuser;
		int m_nightVision;
		int m_armor;

	} RebuyStruct;

	typedef enum
	{
		THROW_NONE,
		THROW_FORWARD,
		THROW_BACKWARD,
		THROW_HITVEL,
		THROW_BOMB,
		THROW_GRENADE,
		THROW_HITVEL_MINUS_AIRVEL

	} ThrowDirection;

	enum sbar_data
	{
		SBAR_ID_TARGETTYPE = 1,
		SBAR_ID_TARGETNAME,
		SBAR_ID_TARGETHEALTH,
		SBAR_END
	};

	typedef enum
	{
		SILENT,
		CALM,
		INTENSE

	} MusicState;

	constexpr auto MIN_BUY_TIME = 15;	// the minimum threshold values for cvar mp_buytime 15 sec's

	constexpr auto MAX_BUFFER_MENU = 175;
	constexpr auto MAX_BUFFER_MENU_BRIEFING = 50;

	constexpr size_t MAX_RECENT_PATH = 20;

	constexpr duration_t SUITUPDATETIME = 3.5s;
	constexpr duration_t SUITFIRSTUPDATETIME = 0.1s;

	constexpr float PLAYER_FATAL_FALL_SPEED = 1100.0f;
	constexpr float PLAYER_MAX_SAFE_FALL_SPEED = 500.0f;
	constexpr float PLAYER_USE_RADIUS = 64.0f;

	constexpr float ARMOR_RATIO = 0.5; // Armor Takes 50% of the damage
	constexpr float ARMOR_BONUS = 0.5; // Each Point of Armor is work 1/x points of health

	constexpr duration_t FLASH_DRAIN_TIME = 1.2s; // 100 units/3 minutes
	constexpr duration_t FLASH_CHARGE_TIME = 0.2s; // 100 units/20 seconds  (seconds per unit)

	// damage per unit per second.
	constexpr float DAMAGE_FOR_FALL_SPEED = 100.0f / (PLAYER_FATAL_FALL_SPEED - PLAYER_MAX_SAFE_FALL_SPEED);
	constexpr float PLAYER_MIN_BOUNCE_SPEED = 350.0f;

	// won't punch player's screen/make scrape noise unless player falling at least this fast.
	constexpr float PLAYER_FALL_PUNCH_THRESHHOLD = 250.0f;

	// Money blinks few of times on the freeze period
	// NOTE: It works for CZ
	constexpr auto MONEY_BLINK_AMOUNT = 30;

	constexpr auto PFLAG_ONLADDER = (1 << 0);
	constexpr auto PFLAG_ONSWING = (1 << 0);
	constexpr auto PFLAG_ONTRAIN = (1 << 1);
	constexpr auto PFLAG_ONBARNACLE = (1 << 2);
	constexpr auto PFLAG_DUCKING = (1 << 3);
	constexpr auto PFLAG_USING = (1 << 4);
	constexpr auto PFLAG_OBSERVER = (1 << 5);

	constexpr auto TRAIN_OFF = 0x00;
	constexpr auto TRAIN_NEUTRAL = 0x01;
	constexpr auto TRAIN_SLOW = 0x02;
	constexpr auto TRAIN_MEDIUM = 0x03;
	constexpr auto TRAIN_FAST = 0x04;
	constexpr auto TRAIN_BACK = 0x05;
	constexpr auto TRAIN_ACTIVE = 0x80;
	constexpr auto TRAIN_NEW = 0xc0;

	constexpr auto DHF_ROUND_STARTED = (1 << 1);
	constexpr auto DHF_HOSTAGE_SEEN_FAR = (1 << 2);
	constexpr auto DHF_HOSTAGE_SEEN_NEAR = (1 << 3);
	constexpr auto DHF_HOSTAGE_USED = (1 << 4);
	constexpr auto DHF_HOSTAGE_INJURED = (1 << 5);
	constexpr auto DHF_HOSTAGE_KILLED = (1 << 6);
	constexpr auto DHF_FRIEND_SEEN = (1 << 7);
	constexpr auto DHF_ENEMY_SEEN = (1 << 8);
	constexpr auto DHF_FRIEND_INJURED = (1 << 9);
	constexpr auto DHF_FRIEND_KILLED = (1 << 10);
	constexpr auto DHF_ENEMY_KILLED = (1 << 11);
	constexpr auto DHF_BOMB_RETRIEVED = (1 << 12);
	constexpr auto DHF_AMMO_EXHAUSTED = (1 << 15);
	constexpr auto DHF_IN_TARGET_ZONE = (1 << 16);
	constexpr auto DHF_IN_RESCUE_ZONE = (1 << 17);
	constexpr auto DHF_IN_ESCAPE_ZONE = (1 << 18);
	constexpr auto DHF_IN_VIPSAFETY_ZONE = (1 << 19);
	constexpr auto DHF_NIGHTVISION = (1 << 20);
	constexpr auto DHF_HOSTAGE_CTMOVE = (1 << 21);
	constexpr auto DHF_SPEC_DUCK = (1 << 22);

	constexpr auto DHM_ROUND_CLEAR = (DHF_ROUND_STARTED | DHF_HOSTAGE_KILLED | DHF_FRIEND_KILLED | DHF_BOMB_RETRIEVED);
	constexpr auto DHM_CONNECT_CLEAR = (DHF_HOSTAGE_SEEN_FAR | DHF_HOSTAGE_SEEN_NEAR | DHF_HOSTAGE_USED | DHF_HOSTAGE_INJURED | DHF_FRIEND_SEEN | DHF_ENEMY_SEEN | DHF_FRIEND_INJURED | DHF_ENEMY_KILLED | DHF_AMMO_EXHAUSTED | DHF_IN_TARGET_ZONE | DHF_IN_RESCUE_ZONE | DHF_IN_ESCAPE_ZONE | DHF_IN_VIPSAFETY_ZONE | DHF_HOSTAGE_CTMOVE | DHF_SPEC_DUCK);

	constexpr auto IGNOREMSG_NONE = 0;
	constexpr auto IGNOREMSG_ENEMY = 1;
	constexpr auto IGNOREMSG_TEAM = 2;

	// max of 4 suit sentences queued up at any time
	constexpr auto CSUITPLAYLIST = 4;

	constexpr auto SUIT_GROUP = TRUE;
	constexpr auto SUIT_SENTENCE = FALSE;

	constexpr auto SUIT_REPEAT_OK = 0;
	constexpr auto SUIT_NEXT_IN_30SEC = 30;
	constexpr auto SUIT_NEXT_IN_1MIN = 60;
	constexpr auto SUIT_NEXT_IN_5MIN = 300;
	constexpr auto SUIT_NEXT_IN_10MIN = 600;
	constexpr auto SUIT_NEXT_IN_30MIN = 1800;
	constexpr auto SUIT_NEXT_IN_1HOUR = 3600;

	constexpr auto TEAM_NAME_LENGTH = 16;

	constexpr auto MAX_ID_RANGE = 2048.0f;
	constexpr auto MAX_SPECTATOR_ID_RANGE = 8192.0f;
	constexpr auto SBAR_STRING_SIZE = 128;

	constexpr auto SBAR_TARGETTYPE_TEAMMATE = 1;
	constexpr auto SBAR_TARGETTYPE_ENEMY = 2;
	constexpr auto SBAR_TARGETTYPE_HOSTAGE = 3;

	constexpr auto CHAT_INTERVAL = 1.0f;
	constexpr auto CSUITNOREPEAT = 32;

	constexpr auto AUTOAIM_2DEGREES = 0.0348994967025;
	constexpr auto AUTOAIM_5DEGREES = 0.08715574274766;
	constexpr auto AUTOAIM_8DEGREES = 0.1391731009601;
	constexpr auto AUTOAIM_10DEGREES = 0.1736481776669;

	constexpr auto SOUND_FLASHLIGHT_ON = "items/flashlight1.wav";
	constexpr auto SOUND_FLASHLIGHT_OFF = "items/flashlight1.wav";
}