#pragma once
#include "../sdk.hpp"

class c_hooks{
public:
	std::unique_ptr<vmt> panel_hook;
	std::unique_ptr<vmt> surface_hook;
	void get_hooks();
	void un_hooks();
	static void __fastcall painttraverse(PVOID ppanels, int edx, unsigned int vguipanel, bool forcerepaint, bool allowforce);
	static void __fastcall lockcursor(i_surface* thisptr, void* edx);
private:
	using painttraverse_t = void(__thiscall*)(void*, vgui::vpanel, bool, bool);
	using lockcursor_t = void(__thiscall*)(i_surface*, void*);
};
extern c_hooks g_hooks;