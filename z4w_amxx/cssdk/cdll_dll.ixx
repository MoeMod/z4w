export module cssdk.cdll_dll;

export namespace cssdk {

	constexpr auto MAX_CLIENTS = 32;
	constexpr auto MAX_WEAPONS = 32;
	constexpr auto MAX_WEAPON_SLOTS = 5;
	constexpr auto MAX_ITEM_TYPES = 6;

	constexpr auto HIDEHUD_WEAPONS = (1 << 0);
	constexpr auto HIDEHUD_FLASHLIGHT = (1 << 1);
	constexpr auto HIDEHUD_ALL = (1 << 2);
	constexpr auto HIDEHUD_HEALTH = (1 << 3);

	constexpr auto MAX_AMMO_TYPES = 32;		// ???
	constexpr auto MAX_AMMO_SLOTS = 32;		// not really slots

	constexpr auto HUD_PRINTNOTIFY = 1;
	constexpr auto HUD_PRINTCONSOLE = 2;
	constexpr auto HUD_PRINTTALK = 3;
	constexpr auto HUD_PRINTCENTER = 4;

	constexpr auto WEAPON_SUIT = 31;

	constexpr auto MAX_ITEMS = 4;

	constexpr auto DEFAULT_FOV = 90;		// the default field of view

	constexpr auto HIDEHUD_TIMER = (1 << 4);
	constexpr auto HIDEHUD_MONEY = (1 << 5);
	constexpr auto HIDEHUD_CROSSHAIR = (1 << 6);

	constexpr auto STATUSICON_HIDE = 0;
	constexpr auto STATUSICON_SHOW = 1;
	constexpr auto STATUSICON_FLASH = 2;

	constexpr auto TEAM_UNASSIGNED = 0;
	constexpr auto TEAM_TERRORIST = 1;
	constexpr auto TEAM_CT = 2;
	constexpr auto TEAM_SPECTATOR = 3;

	constexpr auto CLASS_UNASSIGNED = 0;
	constexpr auto CLASS_URBAN = 1;
	constexpr auto CLASS_TERROR = 2;
	constexpr auto CLASS_LEET = 3;
	constexpr auto CLASS_ARCTIC = 4;
	constexpr auto CLASS_GSG9 = 5;
	constexpr auto CLASS_GIGN = 6;
	constexpr auto CLASS_SAS = 7;
	constexpr auto CLASS_GUERILLA = 8;
	constexpr auto CLASS_VIP = 9;
	constexpr auto CLASS_MILITIA = 10;
	constexpr auto CLASS_SPETSNAZ = 11;

	constexpr auto HUD_PRINTRADIO = 5;

	constexpr auto STATUS_NIGHTVISION_ON = 1;
	constexpr auto STATUS_NIGHTVISION_OFF = 0;

	constexpr auto ITEM_STATUS_NIGHTVISION = (1 << 0);
	constexpr auto ITEM_STATUS_DEFUSER = (1 << 1);

	constexpr auto PLAYER_DEAD = (1 << 0);
	constexpr auto PLAYER_HAS_C4 = (1 << 1);
	constexpr auto PLAYER_VIP = (1 << 2);
	constexpr auto PLAYER_ZOMBIE = (1 << 3);

	constexpr auto SIGNAL_BUY = (1 << 0);
	constexpr auto SIGNAL_BOMB = (1 << 1);
	constexpr auto SIGNAL_RESCUE = (1 << 2);
	constexpr auto SIGNAL_ESCAPE = (1 << 3);
	constexpr auto SIGNAL_VIPSAFETY = (1 << 4);

	constexpr auto DATA_IUSER3_CANSHOOT = (1 << 0);
	constexpr auto DATA_IUSER3_FREEZETIMEOVER = (1 << 1);
	constexpr auto DATA_IUSER3_INBOMBZONE = (1 << 2);
	constexpr auto DATA_IUSER3_HOLDINGSHIELD = (1 << 3);
	constexpr auto IUSER3_CANSHOOT = (1 << 0);
	constexpr auto IUSER3_FREEZETIMEOVER = (1 << 1);
	constexpr auto IUSER3_INBOMBZONE = (1 << 2);
	constexpr auto IUSER3_HOLDINGSHIELD = (1 << 3);

	constexpr auto MENU_KEY_1 = (1 << 0);
	constexpr auto MENU_KEY_2 = (1 << 1);
	constexpr auto MENU_KEY_3 = (1 << 2);
	constexpr auto MENU_KEY_4 = (1 << 3);
	constexpr auto MENU_KEY_5 = (1 << 4);
	constexpr auto MENU_KEY_6 = (1 << 5);
	constexpr auto MENU_KEY_7 = (1 << 6);
	constexpr auto MENU_KEY_8 = (1 << 7);
	constexpr auto MENU_KEY_9 = (1 << 8);
	constexpr auto MENU_KEY_0 = (1 << 9);

	constexpr auto WEAPON_ALLWEAPONS = (~(1 << WEAPON_SUIT));

	// custom enum
	enum VGUIMenu
	{
		VGUI_Menu_Team = 2,
		VGUI_Menu_MapBriefing = 4,

		VGUI_Menu_Class_T = 26,
		VGUI_Menu_Class_CT,
		VGUI_Menu_Buy,
		VGUI_Menu_Buy_Pistol,
		VGUI_Menu_Buy_ShotGun,
		VGUI_Menu_Buy_Rifle,
		VGUI_Menu_Buy_SubMachineGun,
		VGUI_Menu_Buy_MachineGun,
		VGUI_Menu_Buy_Item,
	};

	// custom enum
	enum VGUIMenuSlot
	{
		VGUI_MenuSlot_Buy_Pistol = 1,
		VGUI_MenuSlot_Buy_ShotGun,
		VGUI_MenuSlot_Buy_SubMachineGun,
		VGUI_MenuSlot_Buy_Rifle,
		VGUI_MenuSlot_Buy_MachineGun,
		VGUI_MenuSlot_Buy_PrimAmmo,
		VGUI_MenuSlot_Buy_SecAmmo,
		VGUI_MenuSlot_Buy_Item,
		VGUI_MenuSlot_Zbs_Upgrade,
	};

	constexpr auto MENU_TEAM = 2;
	constexpr auto MENU_MAPBRIEFING = 4;
	constexpr auto MENU_CLASS_T = 26;
	constexpr auto MENU_CLASS_CT = 27;
	constexpr auto MENU_BUY = 28;
	constexpr auto MENU_BUY_PISTOL = 29;
	constexpr auto MENU_BUY_SHOTGUN = 30;
	constexpr auto MENU_BUY_RIFLE = 31;
	constexpr auto MENU_BUY_SUBMACHINEGUN = 32;
	constexpr auto MENU_BUY_MACHINEGUN = 33;
	constexpr auto MENU_BUY_ITEM = 34;

	constexpr size_t MAX_PLAYER_NAME_LENGTH = 32;
	constexpr size_t MAX_AUTOBUY_LENGTH = 256;
	constexpr size_t MAX_REBUY_LENGTH = 256;
	constexpr size_t MAX_MOTD_CHUNK = 60;
	constexpr size_t MAX_MOTD_LENGTH = 1536;
}