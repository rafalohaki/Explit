#pragma once
#include "../../sdk.hpp"

class c_draw_manager {
public:
	vgui::hfont menu;
	vgui::hfont esp;
	void string(const int x, const int y, const color c, const int font, const bool center, const std::string text);
	void string_right(int x, const int y, const color c, const int font, const std::string text);
	void fill_rect(const int x, const int y, const int w, const int h, const color c);
	void rect(const int x, const int y, const int w, const int h, const color c);
	void line(const int x1, const int y1, const int x2, const int y2, const color c);
	void circle(const int x, const int y, const int r, const int seg, const color c);
	void gradient(const int x, const int y, const int w, const int h, const color c1, const color c2);
	void get_text_size(const int font, const std::string text, int& wide, int& tall);
};
extern c_draw_manager g_draw;