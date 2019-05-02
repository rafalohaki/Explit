#pragma once
#include "../../sdk.hpp"

class c_draw_manager {
public:
	vgui::HFont menu;
	vgui::HFont esp;
	void string(const int x, const int y, const Color c, const int font, const bool center, const std::string text);
	void string_right(int x, const int y, const Color c, const int font, const std::string text);
	void fill_rect(const int x, const int y, const int w, const int h, const Color c);
	void rect(const int x, const int y, const int w, const int h, const Color c);
	void line(const int x1, const int y1, const int x2, const int y2, const Color c);
	void circle(const int x, const int y, const int r, const int seg, const Color c);
	void gradient(const int x, const int y, const int w, const int h, const Color c1, const Color c2);
	void get_text_size(const int font, const std::string text, int& wide, int& tall);
};
extern c_draw_manager g_draw;