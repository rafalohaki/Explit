#include "draw_manager.hpp"
c_draw_manager g_draw;

void c_draw_manager::string(const int x, const int y, const color c, const int font, const bool center, const std::string text)
{
	const auto wtext = std::wstring(text.begin(), text.end());

	int width = 0, height = 0;

	if (center)
	{
		g_interfaces.p_surface->gettextsize(font, wtext.c_str(), width, height);
	}
	g_interfaces.p_surface->drawsettextcolor(c);
	g_interfaces.p_surface->drawsettextfont(font);
	g_interfaces.p_surface->drawsettextpos(x - (width / 2), y);
	g_interfaces.p_surface->drawprinttext(wtext.c_str(), wcslen(wtext.c_str()));
}
void c_draw_manager::string_right(int x,  const int y, const color c,  const int font, const std::string text)
{
	const auto wtext = std::wstring(text.begin(), text.end());

	int width = 0, height = 0;

	g_interfaces.p_surface->gettextsize(font, wtext.c_str(), width, height);
	x -= width;
	g_interfaces.p_surface->drawsettextcolor(c);
	g_interfaces.p_surface->drawsettextfont(font);
	g_interfaces.p_surface->drawsettextpos(x, y);
	g_interfaces.p_surface->drawprinttext(wtext.c_str(), wcslen(wtext.c_str()));
}

void c_draw_manager::rect(const int x, const int y, const int w, const int h, color c) 
{
	g_interfaces.p_surface->drawsetcolor(c);
	g_interfaces.p_surface->drawoutlinedrect(x, y, x + w, y + h);
}
void c_draw_manager::fill_rect(const int x, const int y, const int w, const int h, color c) 
{
	g_interfaces.p_surface->drawsetcolor(c);
	g_interfaces.p_surface->drawfilledrect(x, y, x + w, y + h);
}
void c_draw_manager::line(const int x, const int y, const int x1, const int y2, color c) 
{
	g_interfaces.p_surface->drawsetcolor(c);
	g_interfaces.p_surface->drawline(x, y, x1, y2);
}
void c_draw_manager::circle(const int x, const int y, const int r, const int seg, color c) 
{
	g_interfaces.p_surface->drawsetcolor(c);
	g_interfaces.p_surface->drawoutlinedcircle(x, y, r, seg);
}
void c_draw_manager::gradient(const int x, const int y, const int w, const int h, color c1, color c2)
{
	fill_rect(x, y, w, h, c1);
	BYTE first = c2.r();
	BYTE second = c2.g();
	BYTE third = c2.b();
	for (int i = 0; i < h; i++)
	{
		float fi = i, fh = h;
		float a = fi / fh;
		DWORD ia = a * 255;
		fill_rect(x, y + i, w, 1, color(first, second, third, ia));
	}
}
void c_draw_manager::get_text_size(const int font, const std::string text, int& wide, int& tall)
{
	const auto wtext = std::wstring(text.begin(), text.end());
	g_interfaces.p_surface->gettextsize(font, wtext.c_str(), wide, tall);
}
