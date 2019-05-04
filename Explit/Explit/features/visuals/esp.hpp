#pragma once
#include "../../sdk/sdk.hpp"

class c_esp {
private:
	RECT get_boundbox(c_base_entity* pent);
	void draw_players(c_base_entity* pplayer, RECT box);
	void draw_weapons(c_base_entity* pentity, RECT box);
	void draw_chickens(c_base_entity* pentity, RECT box);
	void draw_projectiles(c_base_entity* pentity, RECT box);
public:
	void start();
};
extern c_esp g_esp;