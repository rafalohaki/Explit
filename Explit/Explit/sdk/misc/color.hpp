#pragma once
#include <cstdint>
#include "../sdk.hpp"
class color
{
public:
	color();
	color(zgui::color col);
	color(int _r, int _g, int _b);
	color(int _r, int _g, int _b, int _a);
	color(float _r, float _g, float _b) : color(_r, _g, _b, 1.0f) {}
	color(float _r, float _g, float _b, float _a)
		: color(
			static_cast<int>(_r * 255.0f),
			static_cast<int>(_g * 255.0f),
			static_cast<int>(_b * 255.0f),
			static_cast<int>(_a * 255.0f))
	{
	}
	explicit color(float* rgb) : color(rgb[0], rgb[1], rgb[2], 1.0f) {}
	explicit color(unsigned long argb)
	{
		colors[2] = (unsigned char)((argb & 0x000000ff) >> (0 * 8));
		colors[1] = (unsigned char)((argb & 0x0000ff00) >> (1 * 8));
		colors[0] = (unsigned char)((argb & 0x00ff0000) >> (2 * 8));
		colors[3] = (unsigned char)((argb & 0xff000000) >> (3 * 8));
	}

	void    set_raw_color(int color32);
	int     get_raw_color() const;
	void    set_color(int _r, int _g, int _b, int _a = 0);
	void    set_color(float _r, float _g, float _b, float _a = 0);
	void	set_color(float* color);
	void    get_color(int &_r, int &_g, int &_b, int &_a) const;

	int r() const { return colors[0]; }
	int g() const { return colors[1]; }
	int b() const { return colors[2]; }
	int a() const { return colors[3]; }

	void set_alpha(int alpha) { colors[3] = alpha; }

	unsigned char &operator[](int index)
	{
		return colors[index];
	}
	const unsigned char &operator[](int index) const
	{
		return colors[index];
	}

	bool operator==(const color &rhs) const;
	bool operator!=(const color &rhs) const;
	color &operator=(const color &rhs);

	unsigned char colors[4];
};