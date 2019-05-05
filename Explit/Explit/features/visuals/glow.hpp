#pragma once
#include "../../sdk/sdk.hpp"

class c_glow {
private:
	void glow(c_glow_manager::glow_object_definition_t* glow_entity, const color c);
public:
	void start();
};
extern c_glow g_glow;