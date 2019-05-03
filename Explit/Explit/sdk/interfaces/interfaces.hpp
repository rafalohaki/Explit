#pragma once
#include "../sdk.hpp"

class c_interfaces {
public:
	c_interfaces();
	i_global_vars_base* p_globalvars;
	i_surface* p_surface;
	i_panel* p_panel;
	iv_engine_client* p_engine;
	i_base_client_dll* p_client;
	i_client_entity_list* p_entitylist;
	c_base_entity* g_localplayer;
	void get_interfaces();
private:
	template <typename t>
	t* get_interface(const std::string module, const std::string name, const bool exact = false);
};
extern c_interfaces g_interfaces;