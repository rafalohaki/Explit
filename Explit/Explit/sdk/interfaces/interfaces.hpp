#pragma once
#include "../sdk.hpp"

class c_interfaces {
public:
	c_interfaces();
	CGlobalVarsBase* p_globalvars;
	ISurface* p_surface;
	IPanel* p_panel;
	IVEngineClient* p_engine;
	IBaseClientDLL* p_client;
	IClientEntityList* p_entitylist;
	C_BaseEntity* g_localplayer;
	void get_interfaces();
private:
	template <typename t>
	t* get_interface(const std::string module, const std::string name, const bool exact = false);
};
extern c_interfaces g_interfaces;