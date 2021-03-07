export module plugin;

export namespace plugin {
	//AMXX forward
	enum
	{
		FW_Semiclip = 0,
		FW_ALARM_SHOW_PRE,
		FW_ALARM_SHOW_POST,
		TOTAL_FORWARDS
	};

	extern int g_iForwards[TOTAL_FORWARDS];
}