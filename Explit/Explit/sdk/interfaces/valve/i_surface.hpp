#pragma once
#include "../../sdk.hpp"

class color;
namespace vgui
{
	typedef unsigned long hfont;
	typedef unsigned int vpanel;
};

enum fontfeature
{
	font_feature_antialiased_fonts = 1,
	font_feature_dropshadow_fonts = 2,
	font_feature_outline_fonts = 6,
};

enum fontdrawtype
{
	font_draw_default = 0,
	font_draw_nonadditive,
	font_draw_additive,
	font_draw_type_count = 2,
};

enum fontflags
{
	fontflag_none,
	fontflag_italic = 0x001,
	fontflag_underline = 0x002,
	fontflag_strikeout = 0x004,
	fontflag_symbol = 0x008,
	fontflag_antialias = 0x010,
	fontflag_gaussianblur = 0x020,
	fontflag_rotary = 0x040,
	fontflag_dropshadow = 0x080,
	fontflag_additive = 0x100,
	fontflag_outline = 0x200,
	fontflag_custom = 0x400,
	fontflag_bitmap = 0x800,
};

struct intrect
{
	int x0;
	int y0;
	int x1;
	int y1;
};

struct vertex_t
{
	vertex_t() {}
	vertex_t(const vector2d &pos, const vector2d &coord = vector2d(0, 0))
	{
		m_position = pos;
		m_texcoord = coord;
	}
	void init(const vector2d &pos, const vector2d &coord = vector2d(0, 0))
	{
		m_position = pos;
		m_texcoord = coord;
	}

	vector2d m_position;
	vector2d m_texcoord;
};

//-----------------------------------------------------------------------------
// purpose: wraps contextless windows system functions
//-----------------------------------------------------------------------------
class i_surface : public i_app_system
{
public:
	virtual void          run_frame() = 0;
	virtual vgui::vpanel  get_embedded_panel() = 0;
	virtual void          set_embedded_panel(vgui::vpanel ppanel) = 0;
	virtual void          push_make_current(vgui::vpanel panel, bool useinsets) = 0;
	virtual void          pop_make_current(vgui::vpanel panel) = 0;
	virtual void          draw_set_color(int r, int g, int b, int a) = 0;
	virtual void          draw_set_color(color col) = 0;
	virtual void          draw_filled_rect(int x0, int y0, int x1, int y1) = 0;
	virtual void          draw_filled_rect_array(intrect *prects, int numrects) = 0;
	virtual void          draw_outlined_rect(int x0, int y0, int x1, int y1) = 0;
	virtual void          draw_line(int x0, int y0, int x1, int y1) = 0;
	virtual void          draw_poly_line(int *px, int *py, int numpoints) = 0;
	virtual void          draw_set_apparent_depth(float f) = 0;
	virtual void          draw_clear_apparent_depth(void) = 0;
	virtual void          draw_set_text_font(vgui::hfont font) = 0;
	virtual void          draw_set_text_color(int r, int g, int b, int a) = 0;
	virtual void          draw_set_text_color(color col) = 0;
	virtual void          draw_set_text_pos(int x, int y) = 0;
	virtual void          draw_get_text_pos(int& x, int& y) = 0;
	virtual void          draw_print_text(const wchar_t *text, int textlen, fontdrawtype drawtype = fontdrawtype::font_draw_default) = 0;
	virtual void          draw_unicode_char(wchar_t wch, fontdrawtype drawtype = fontdrawtype::font_draw_default) = 0;
	virtual void          draw_flush_text() = 0;
	virtual void*         create_html_window(void *events, vgui::vpanel context) = 0;
	virtual void          paint_html_window(void *htmlwin) = 0;
	virtual void          delete_html_window(void *htmlwin) = 0;
	virtual int           draw_get_texture_id(char const *filename) = 0;
	virtual bool          draw_get_texture_file(int id, char *filename, int maxlen) = 0;
	virtual void          draw_set_texture_file(int id, const char *filename, int hardwarefilter, bool forcereload) = 0;
	virtual void          draw_set_texture_rgba(int id, const unsigned char *rgba, int wide, int tall) = 0;
	virtual void          draw_set_texture(int id) = 0;
	virtual void          delete_texture_by_id(int id) = 0;
	virtual void          draw_get_texture_size(int id, int &wide, int &tall) = 0;
	virtual void          draw_textured_rect(int x0, int y0, int x1, int y1) = 0;
	virtual bool          is_texture_id_valid(int id) = 0;
	virtual int           create_new_texture_id(bool procedural = false) = 0;
	virtual void          get_screen_size(int &wide, int &tall) = 0;
	virtual void          set_as_top_most(vgui::vpanel panel, bool state) = 0;
	virtual void          bring_to_front(vgui::vpanel panel) = 0;
	virtual void          set_foreground_window(vgui::vpanel panel) = 0;
	virtual void          set_panel_visible(vgui::vpanel panel, bool state) = 0;
	virtual void          set_minimized(vgui::vpanel panel, bool state) = 0;
	virtual bool          is_minimized(vgui::vpanel panel) = 0;
	virtual void          flash_window(vgui::vpanel panel, bool state) = 0;
	virtual void          set_title(vgui::vpanel panel, const wchar_t *title) = 0;
	virtual void          set_as_tool_bar(vgui::vpanel panel, bool state) = 0;
	virtual void          create_popup(vgui::vpanel panel, bool minimised, bool showtaskbaricon = true, bool disabled = false, bool mouseinput = true, bool kbinput = true) = 0;
	virtual void          swap_buffers(vgui::vpanel panel) = 0;
	virtual void          invalidate(vgui::vpanel panel) = 0;
	virtual void          set_cursor(unsigned long cursor) = 0;
	virtual bool          is_cursor_visible() = 0;
	virtual void          applychanges() = 0;
	virtual bool          is_within(int x, int y) = 0;
	virtual bool          has_focus() = 0;
	virtual bool          supports_feature(int /*surfacefeature_t*/ feature) = 0;
	virtual void          restrict_paint_to_single_panel(vgui::vpanel panel, bool bforceallownonmodalsurface = false) = 0;
	virtual void          set_modal_panel(vgui::vpanel) = 0;
	virtual vgui::vpanel  get_modal_panel() = 0;
	virtual void          unlock_cursor() = 0;
	virtual void          lock_cursor() = 0;
	virtual void          set_translate_extended_keys(bool state) = 0;
	virtual vgui::vpanel  get_top_most_popup() = 0;
	virtual void          set_top_level_focus(vgui::vpanel panel) = 0;
	virtual vgui::hfont   create_font_() = 0;
	virtual bool          set_font_glyph_set(vgui::hfont font, const char *windowsfontname, int tall, int weight, int blur, int scanlines, int flags, int nrangemin = 0, int nrangemax = 0) = 0;
	virtual bool          add_custom_font_file(const char *fontfilename) = 0;
	virtual int           get_font_tall(vgui::hfont font) = 0;
	virtual int           get_font_ascent(vgui::hfont font, wchar_t wch) = 0;
	virtual bool          is_font_additive(vgui::hfont font) = 0;
	virtual void          get_charabc_wide(vgui::hfont font, int ch, int &a, int &b, int &c) = 0;
	virtual int           get_character_width(vgui::hfont font, int ch) = 0;
	virtual void          get_text_size(vgui::hfont font, const wchar_t *text, int &wide, int &tall) = 0;
	virtual vgui::vpanel  get_notify_panel() = 0;
	virtual void          set_notify_icon(vgui::vpanel context, unsigned long icon, vgui::vpanel paneltoreceivemessages, const char *text) = 0;
	virtual void          play_sound(const char *filename) = 0;
	virtual int           get_popup_count() = 0;
	virtual vgui::vpanel  get_popup(int index) = 0;
	virtual bool          should_paint_child_panel(vgui::vpanel childpanel) = 0;
	virtual bool          recreate_context(vgui::vpanel panel) = 0;
	virtual void          add_panel(vgui::vpanel panel) = 0;
	virtual void          release_panel(vgui::vpanel panel) = 0;
	virtual void          move_popup_to_front(vgui::vpanel panel) = 0;
	virtual void          move_popup_to_back(vgui::vpanel panel) = 0;
	virtual void          solve_traverse(vgui::vpanel panel, bool forceapplyschemesettings = false) = 0;
	virtual void          paint_traverse(vgui::vpanel panel) = 0;
	virtual void          enable_mouse_capture(vgui::vpanel panel, bool state) = 0;
	virtual void          get_work_space_bounds(int &x, int &y, int &wide, int &tall) = 0;
	virtual void          get_absolute_window_bounds(int &x, int &y, int &wide, int &tall) = 0;
	virtual void          get_proportional_base(int &width, int &height) = 0;
	virtual void          calculate_mouse_visible() = 0;
	virtual bool          need_kb_input() = 0;
	virtual bool          has_cursor_pos_functions() = 0;
	virtual void          surface_get_cursor_pos(int &x, int &y) = 0;
	virtual void          surface_set_cursor_pos(int x, int y) = 0;
	virtual void          draw_textured_line(const vertex_t &a, const vertex_t &b) = 0;
	virtual void          draw_outlined_circle(int x, int y, int radius, int segments) = 0;
	virtual void          draw_textured_polyline(const vertex_t *p, int n) = 0;
	virtual void          draw_textured_subrect(int x0, int y0, int x1, int y1, float texs0, float text0, float texs1, float text1) = 0;
	virtual void          draw_textured_polygon(int n, vertex_t *pvertice, bool bclipvertices = true) = 0;
};