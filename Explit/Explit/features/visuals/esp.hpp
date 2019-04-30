#pragma once
#include "../../sdk/sdk.hpp"

class c_esp {
private:
	RECT get_boundbox(C_BaseEntity* pent);
	void draw_players(C_BaseEntity* pplayer, RECT box);
public:
	void start();
};
extern c_esp g_esp;