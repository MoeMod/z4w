module;

export module hlsdk.globals;
import hlsdk.types;

export namespace hlsdk {
	Vector g_vecAttackDir;
	int g_iSkillLevel;
	int gDisplayTitle;
	BOOL g_fGameOver;
	const Vector g_vecZero = Vector(0, 0, 0);
	int g_Language;

	bool g_bIsCzeroGame = false;
	bool g_bEnableCSBot = false;
}