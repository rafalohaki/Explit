#pragma once
#include "../sdk.hpp"

class c_hooks{
public:
	std::unique_ptr<vmt> panel_hook;
	std::unique_ptr<vmt> surface_hook;
	std::unique_ptr<vmt> client_mode_hook;
	void get_hooks();
	void un_hooks();
	static void __fastcall painttraverse(PVOID ppanels, int edx, unsigned int vguipanel, bool forcerepaint, bool allowforce);
	static void __fastcall lockcursor(i_surface* thisptr, void* edx);
	static int	__fastcall	post_screen_effects(void *thisptr, void * _EDX, int a1);
private:
	using painttraverse_fn = void(__thiscall*)(void*, vgui::vpanel, bool, bool);
	typedef void(__fastcall* LockCursor_t) (i_surface*, void*);
	typedef  int(__fastcall  *Effects_t)(void*, void*, int);
	using lockcursor_fn = void(__fastcall*)(i_surface* thisptr, void* edx);
};
extern c_hooks g_hooks;