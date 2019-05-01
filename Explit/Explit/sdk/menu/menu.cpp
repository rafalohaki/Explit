#include "menu.hpp"
c_menu g_menu;
int imatype = 0;
std::vector<std::string> st = { "type 1", "type 2" ,"type 3", "type 4"};
std::vector<std::string> st2 = { "multi 1", "type 2" ,"type 3", "type 4" };
int dsds = 1;
bool dsa = false;
int key = 2;
float slid = 22;
float nslid = -24;
std::string dasd = "";
void c_menu::draw()
{
	zgui::poll_input("Counter-Strike: Global Offensive");
	if (zgui::begin_window("Explit for Counter-Strike: Global Offensive", { 500, 350 }, g_draw.menu, zgui::zgui_window_flags_none))
	{
		if (zgui::tab_button("Aimbot", { 165,30 }, aimbot))
		{
			aimbot = true;
			visuals = false;
			misc = false;
		}
		zgui::same_line();
		zgui::push({ -17,0 });
		if (zgui::tab_button("Visuals", { 165,30 }, visuals))
		{
			aimbot = false;
			visuals = true;
			misc = false;
		}
		zgui::same_line();	
		zgui::push({ -17,0 });
		if (zgui::tab_button("Misc", { 166,30 }, misc))
		{
			aimbot = false;
			visuals = false;
			misc = true;
		}
		zgui::push({ -327,3 });
		if (aimbot)draw_aimbot();
		if (visuals)draw_visuals();
		if (misc)draw_misc();
		zgui::end_window();
	}
	draw_watermark();
}

void c_menu::draw_watermark()
{
	auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	const auto time = ctime(&timenow);
	auto fps = static_cast<int>(1.f / g_interfaces.p_globalvars->frametime);
	int width, height;
	g_interfaces.p_engine->GetScreenSize(width, height);
	
	g_draw.fill_rect(width - 280, 20, 260, 28, Color(1, 1, 1, 255));
	g_draw.fill_rect(width - 279, 21, 258, 26, Color(51, 51, 51, 255));
	g_draw.fill_rect(width - 278, 22, 256, 24, Color(41, 41, 41, 255));
	g_draw.fill_rect(width - 277, 23, 254, 22, Color(51, 51, 51, 255));
	g_draw.fill_rect(width - 276, 24, 252, 20, Color(1, 1, 1, 255));
	g_draw.fill_rect(width - 275, 25, 250, 18, Color(31, 31, 31, 255));
	g_draw.fill_rect(width - 275, 42, 250, 1, Color(255, 114, 111, 255));
	g_draw.string(width - 205, 26, Color(255, 255, 255), g_draw.menu, true, g_utils.stringer2(time, "  FPS:", fps, "  PING:0ms"));
	
}

void c_menu::draw_misc()
{
	zgui::begin_groupbox("Misc", { 163,290 });
	zgui::push({ 0,5 });
	zgui::checkbox("Check", dsa);
	zgui::combobox("Combo", st,imatype);
	zgui::push({ 0,-17 });
	zgui::combobox("Multi-Combo", st2, imatype);
	zgui::key_bind("KeyBind", key);
	zgui::push({ 0,-35 });
	zgui::slider_int("Int-Slider", 1,100,dsds);
	zgui::push({ 0,-17 });
	zgui::slider_float("Float-Slider", 1, 100, slid);
	zgui::push({ 0,-17 });
	zgui::slider_float("Neg-Slider", -180, 180, nslid);
	zgui::push({ 0,-17 });
	zgui::text_input("KeyInput", dasd);
	zgui::push({ 0,-17 });
	if (zgui::button("Unhook", { 147,18 }))
		g_sdk.unhook = true;
	zgui::end_groupbox();
}
void c_menu::draw_visuals()
{


}
void c_menu::draw_aimbot()
{

}
