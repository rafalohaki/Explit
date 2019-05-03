#include "color.hpp"

color::color()
{
	*((int *)this) = 0;
}
color::color(int _r, int _g, int _b)
{
	setcolor(_r, _g, _b, 255);
}
color::color(zgui::color col)
{
	setcolor(col.r, col.g, col.g, col.a);
}
color::color(int _r, int _g, int _b, int _a)
{
	setcolor(_r, _g, _b, _a);
}
void color::setrawcolor(int color32)
{
	*((int *)this) = color32;
}
int color::getrawcolor() const
{
	return *((int *)this);
}
__inline void color::setcolor(int _r, int _g, int _b, int _a)
{
	_ccolor[0] = (unsigned char)_r;
	_ccolor[1] = (unsigned char)_g;
	_ccolor[2] = (unsigned char)_b;
	_ccolor[3] = (unsigned char)_a;
}
__inline void color::setcolor(float _r, float _g, float _b, float _a)
{
	_ccolor[0] = static_cast<unsigned char>(_r * 255.0f);
	_ccolor[1] = static_cast<unsigned char>(_g * 255.0f);
	_ccolor[2] = static_cast<unsigned char>(_b * 255.0f);
	_ccolor[3] = static_cast<unsigned char>(_a * 255.0f);
}
void color::setcolor(float* color)
{
	if (!color)
		return;

	_ccolor[0] = (unsigned char)(color[0] * 255.f);
	_ccolor[1] = (unsigned char)(color[1] * 255.f);
	_ccolor[2] = (unsigned char)(color[2] * 255.f);
	_ccolor[3] = (unsigned char)(color[3] * 255.f);
}
void color::getcolor(int &_r, int &_g, int &_b, int &_a) const
{
	_r = _ccolor[0];
	_g = _ccolor[1];
	_b = _ccolor[2];
	_a = _ccolor[3];
}
bool color::operator== (const color &rhs) const
{
	return (*((int *)this) == *((int *)&rhs));
}
bool color::operator!= (const color &rhs) const
{
	return !(operator==(rhs));
}
color& color::operator=(const color &rhs)
{
	setrawcolor(rhs.getrawcolor());
	return *this;
}