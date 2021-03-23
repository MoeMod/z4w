
export module amxx.amxmodx_menu;
import amxx.amxmodx_detail;
import hlsdk.engine;

using namespace hlsdk;
export namespace amxx {
	struct MenuStack_MP {
		int m_iMenu;
	};
	struct MenuStack_AMXX {
		int keys; // Player_Keys
		bool vgui; // Player_Vgui
		float menuexpire; // Player_MenuExpire
		int menuid; // Player_Menu
		int newmenu; // Player_Newmenu
		int page; // Player_NewmenuPage
	};
}