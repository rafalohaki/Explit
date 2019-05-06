#pragma once
#include "../../sdk/sdk.hpp"

class c_glow {
private:
	void glow(c_glow_manager::glow_object_definition_t* p_glow_entity, const color color);
public:
	void start();
};
extern c_glow g_glow;