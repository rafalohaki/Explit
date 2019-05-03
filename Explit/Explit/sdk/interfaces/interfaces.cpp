#include "interfaces.hpp"
c_interfaces g_interfaces;

c_interfaces::c_interfaces()
{
	p_globalvars = nullptr;
	p_surface = nullptr;
	p_panel = nullptr;
	p_engine = nullptr;
	p_client = nullptr;
	p_entitylist = nullptr;
	g_localplayer = nullptr;
}

void c_interfaces::get_interfaces()
{
	p_panel = get_interface<i_panel>("vgui2.dll", "VGUI_Panel");
	p_client = get_interface<i_base_client_dll>("client_panorama.dll", "VClient");
	p_engine = get_interface<iv_engine_client>("engine.dll", "VEngineClient");
	p_surface = get_interface<i_surface>("vguimatsurface.dll", "VGUI_Surface");
	p_entitylist = get_interface<i_client_entity_list>("client_panorama.dll", "VClientEntityList");
	p_globalvars = **(i_global_vars_base***)((*(DWORD**)(p_client))[0] + 0x1B);
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

