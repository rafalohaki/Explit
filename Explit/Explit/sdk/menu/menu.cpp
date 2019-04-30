#include "menu.hpp"
c_menu g_menu;

void c_menu::draw()
{
	zgui::poll_input("Counter-Strike: Global Offensive");

	if (zgui::begin_window("Explit for Counter-Strike: Global Offensive", { 500, 350 }, g_draw.menu, zgui::zgui_window_flags_none))
	{
		if (zgui::button("Unhook", { 30,30 }))
			g_sdk.unhook = true;
		zgui::checkbox("esp", g_sdk.esp);
		zgui::end_window();
	}
}
