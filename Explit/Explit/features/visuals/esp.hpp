#pragma once
#include "../../sdk/sdk.hpp"

class c_esp {
private:
	RECT get_boundbox(c_base_entity* p_entity);
	void draw_players(c_base_entity* p_player, const RECT box);
	void draw_weapons(c_base_entity* p_entity, const RECT box);
	void draw_chickens(c_base_entity* p_entity, const  RECT box);
public:
	void start();
};
extern c_esp g_esp;