#pragma once
#include "../sdk.hpp"

class c_hooks{
public:
	std::unique_ptr<vmt> panel_hook;
	std::unique_ptr<vmt> surface_hook;
	std::unique_ptr<vmt> client_mode_hook;
	void get_hooks();
	void un_hooks();
	static void __fastcall paint_traverse(PVOID ppanels, int edx, unsigned int vguipanel, bool forcerepaint, bool allowforce);
	static void __fastcall lock_cursor(i_surface* thisptr, void* edx);
	static int	__fastcall post_screen_effects(void *thisptr, void * _EDX, int a1);
private:
	using paint_traverse_fn = void(__thiscall*)(void*, vgui::vpanel, bool, bool);
	using post_screen_effects_fn = int(__fastcall*)(void*, void*, int);
	using lock_cursor_fn = void(__fastcall*)(i_surface*, void*);
};
extern c_hooks g_hooks;