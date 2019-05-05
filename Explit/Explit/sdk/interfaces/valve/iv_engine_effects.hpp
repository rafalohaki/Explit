#pragma once
#include "../../sdk.hpp"

struct colorrgbexp32
{
	byte r, g, b;
	signed char exponent;
};

struct dlight_t
{
	int				flags;
	Vector			origin;
	float			radius;
	colorrgbexp32	color;
	float			die;
	float			decay;
	float			min_light;
	int				key;
	int				style;
	Vector			m_direction;
	float			m_inner_angle;
	float			m_outer_angle;

	float get_radius() const
	{
		return radius;
	}
	float get_radius_squared() const
	{
		return radius * radius;
	}
	float is_radius_greater_than_zero() const
	{
		return radius > 0.0f;
	}
};

class iv_engine_effects {
public:
	dlight_t* cl_alloc_dlight(int key) 
	{
		return vfunc<4, dlight_t*,int>(this, key); 
	}
	dlight_t* cl_alloc_elight(int key) 
	{
		return vfunc<5, dlight_t*,int>(this, key);
	}
	dlight_t* get_elight_by_key(int key) 
	{
		return vfunc<8, dlight_t*, int>(this, key);
	}
};
