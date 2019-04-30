#pragma once
#include "../sdk.hpp"

class c_math {
private:
	bool screen_transform(const Vector& in, Vector& out);
public:
	void vector_transform(const Vector& in1, const matrix3x4_t& in2, Vector& out);
	bool world_to_screen(const Vector& in, Vector& out);
};
extern c_math g_math;