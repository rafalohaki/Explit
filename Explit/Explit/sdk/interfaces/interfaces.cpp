#include "interfaces.hpp"
c_interfaces g_interfaces;

c_interfaces::c_interfaces()
{
	p_global_vars = nullptr;
	p_surface = nullptr;
	p_panel = nullptr;
	p_engine = nullptr;
	p_client = nullptr;
	p_entity_list = nullptr;
	p_client_mode = nullptr;
	g_local_player = nullptr;
	p_model_render = nullptr;
	p_model_info_client = nullptr;
	p_engine_trace = nullptr;
	p_render_view = nullptr;
	p_engine_effects = nullptr;
}

void c_interfaces::get_interfaces()
{
	p_panel = get_interface<i_panel>("vgui2.dll", "VGUI_Panel");
	p_client = get_interface<i_base_client_dll>("client_panorama.dll", "VClient");
	p_engine = get_interface<iv_engine_client>("engine.dll", "VEngineClient");
	p_surface = get_interface<i_surface>("vguimatsurface.dll", "VGUI_Surface");
	p_entity_list = get_interface<i_client_entity_list>("client_panorama.dll", "VClientEntityList");
	p_model_render = get_interface<iv_model_render>("engine.dll", "VEngineModel");
	p_engine_trace = get_interface<i_engine_trace>("engine.dll", "EngineTraceClient");
	p_model_info_client = get_interface<iv_model_info_client>("engine.dll", "VModelInfoClient");
	p_render_view = get_interface<iv_render_view>("engine.dll", "VEngineRenderView");
	p_engine_effects = get_interface<iv_engine_effects>("engine.dll", "VEngineEffects");
	p_global_vars = **reinterpret_cast<i_global_vars_base***>((*reinterpret_cast<uintptr_t**>(p_client))[0] + 0x1B);
	p_client_mode = **reinterpret_cast<i_client_mode***>((*reinterpret_cast<uintptr_t**>(p_client))[10] + 5);
}

template<typename t>
t* c_interfaces::get_interface(const std::string module, const std::string name, const bool exact)
{
	const auto create_interface = reinterpret_cast<std::add_pointer_t<t* (const char* name, int* returnCode)>>(GetProcAddress(GetModuleHandleA(module.c_str()), "CreateInterface"));

	if (exact)
	{
		 auto found_interface = create_interface(name.c_str(), nullptr);

		 std::cout << "[" << module << "]" << name << " -> 0x" << found_interface << std::endl;

		 return found_interface;
	}
	else
	{
		for (int i = 1; i < 100; i++)
		{
			if (auto found_interface = create_interface((std::ostringstream{ } << name.c_str() << std::setfill('0') << std::setw(3) << i).str().c_str(), nullptr))
			{
				std::cout << "[" << module << "]" << name << " -> 0x" << found_interface << std::endl;

				return found_interface;
			}
		}
	}

}

