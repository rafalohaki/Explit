#include "hooks.hpp"
c_hooks g_hooks;

#pragma region zgui
void line(int x, int y, int x2, int y2, zgui::color c) noexcept { g_draw.line(x, y, x2, y2, c); }
void rect(int x, int y, int x2, int y2, zgui::color c) noexcept { g_draw.rect(x, y, x2, y2, c); }
void filled_rect(int x, int y, int x2, int y2, zgui::color c) noexcept { g_draw.fill_rect(x, y, x2, y2, c); }
void text(int x, int y, zgui::color color, int font, bool center, const char* text) noexcept { g_draw.string(x, y, color, font, center, text); }
void get_text_size(unsigned long font, const char* text, int& wide, int& tall) noexcept { g_draw.get_text_size(font, text, wide, tall); }
float get_frametime() noexcept { return g_interfaces.p_global_vars->frame_time; }
#pragma endregion


void c_hooks::get_hooks() 
{
	panel_hook = std::make_unique<vmt>(g_interfaces.p_panel);
	surface_hook = std::make_unique<vmt>(g_interfaces.p_surface);
	client_mode_hook = std::make_unique<vmt>(g_interfaces.p_client_mode);
	render_view_hook = std::make_unique<vmt>(g_interfaces.p_render_view);
	panel_hook->hook(41, paint_traverse);
	client_mode_hook->hook(44, post_screen_effects);
	render_view_hook->hook(9, scene_end);
	//surface_hook->hook(67, lockcursor);
	zgui::functions.draw_line = line;
	zgui::functions.draw_rect = rect;
	zgui::functions.draw_filled_rect = filled_rect;
	zgui::functions.draw_text = text;
	zgui::functions.get_text_size = get_text_size;
	zgui::functions.get_frametime = get_frametime;
}

void c_hooks::un_hooks()
{
	panel_hook->unhook(41);
	client_mode_hook->unhook(44);
	render_view_hook->unhook(9);
	//surface_hook->unhook(67);
}

void __fastcall  c_hooks::paint_traverse(PVOID p_panels, int edx, unsigned int vgui_panel, bool force_repaint, bool allow_force)
{
	static auto ohook = g_hooks.panel_hook->getorginal<paint_traverse_fn>(41);
	static uint32_t overlay_panel;	

	if (!overlay_panel)
	{
		const auto panel_name = g_interfaces.p_panel->get_name(vgui_panel);

		if (lstrcmpA(panel_name, "MatSystemTopPanel") == 0)
		{
			overlay_panel = vgui_panel;
			g_draw.menu = g_interfaces.p_surface->create_font_();
			g_interfaces.p_surface->set_font_glyph_set(g_draw.menu, "Tahoma", 12, 540, 0, 0, fontflag_outline | fontflag_dropshadow);
			g_draw.esp = g_interfaces.p_surface->create_font_();
			g_interfaces.p_surface->set_font_glyph_set(g_draw.esp, "Tahoma", 11, 500, 0, 0, fontflag_outline );
		}
	}
	if (overlay_panel == vgui_panel)
	{
		g_interfaces.g_local_player = reinterpret_cast<c_base_entity*>(g_interfaces.p_entity_list->get_client_entity((g_interfaces.p_engine->get_local_player())));

		if (g_interfaces.g_local_player && g_interfaces.p_engine->is_in_game() && g_interfaces.p_engine->is_connected())
		{
			g_esp.start();
			g_dlight.start();
		}

		g_menu.draw();
	}

	ohook(p_panels, vgui_panel, force_repaint, allow_force);
}

int __fastcall c_hooks::post_screen_effects(void *thisptr, void * _edx, int a1)
{
	static auto ohook = g_hooks.client_mode_hook->getorginal<post_screen_effects_fn>(44);

	if(!g_interfaces.p_engine->is_in_game() || !g_interfaces.p_engine->is_connected())
		return ohook(thisptr, _edx, a1);

	if (g_config.settings.visuals.glow.glow)
		g_glow.start();

	return ohook(thisptr, _edx, a1);
}

void __fastcall c_hooks::scene_end(void* thisptr, void* edx)
{
	static auto ohook = g_hooks.render_view_hook->getorginal<scene_end_fn>(9);

	ohook(thisptr);

	g_chams.scene_end_start();
}

void __fastcall  c_hooks::lock_cursor(i_surface* thisptr, void* edx)
{
	static auto ohook = g_hooks.surface_hook->getorginal<lock_cursor_fn>(67);

	if (!menu_open)
		ohook(thisptr,edx);

	g_interfaces.p_surface->unlock_cursor();
}
