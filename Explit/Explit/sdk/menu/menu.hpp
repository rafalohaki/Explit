#pragma once
#include "../sdk.hpp"

class c_menu {
public:
	void draw();
	bool open = false;
private:
};
extern c_menu g_menu;