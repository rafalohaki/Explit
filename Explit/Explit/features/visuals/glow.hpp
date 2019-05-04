#pragma once
#include "../../sdk/sdk.hpp"

class c_glow {
private:
	void draw_players(c_glow_manager::glow_object_definition_t* glow_entity);
	void draw_weapons(c_glow_manager::glow_object_definition_t* glow_entity);
	void draw_chickens(c_glow_manager::glow_object_definition_t* glow_entity);
public:
	void start();
};
extern c_glow g_glow;