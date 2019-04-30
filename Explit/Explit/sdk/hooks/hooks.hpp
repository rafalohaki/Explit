#pragma once
#include "../sdk.hpp"

class c_hooks{
public:
	std::unique_ptr<vmt> panel_hook;
	std::unique_ptr<vmt> surface_hook;
	void get_hooks();
	void un_hooks();
	static void __fastcall PaintTraverse(PVOID pPanels, int edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce);
	static void __fastcall LockCursor(ISurface* thisptr, void* edx);
private:
	using PaintTraverse_t = void(__thiscall*)(void*, vgui::VPANEL, bool, bool);
	using LockCursor_t = void(__thiscall*)(ISurface*, void*);
};
extern c_hooks g_hooks;