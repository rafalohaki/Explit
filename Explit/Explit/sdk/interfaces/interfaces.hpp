#pragma once
#include "../sdk.hpp"

class c_interfaces {
public:
	c_interfaces();
	i_global_vars_base* p_global_vars;
	i_surface* p_surface;
	i_panel* p_panel;
	iv_engine_client* p_engine;
	i_base_client_dll* p_client;
	i_client_mode* p_client_mode;
	i_client_entity_list* p_entity_list;
	iv_model_render* p_model_render;
	iv_model_info_client* p_model_info_client;
	i_engine_trace* p_engine_trace;
	iv_render_view* p_render_view;
	c_base_entity* g_local_player;
	void get_interfaces();
private:
	template <typename t>
	t* get_interface(const std::string module, const std::string name, const bool exact = false);
};
extern c_interfaces g_interfaces;