#pragma once
#include "../sdk.hpp"

class c_menu {
public:
	void draw();
	bool open = false;
private:
	void draw_watermark();
	bool aimbot = true;
	bool visuals = false;
	bool misc = false;
	void draw_aimbot();
	void draw_visuals();
	void draw_misc();
};
extern c_menu g_menu;




struct zgui_controls {

};