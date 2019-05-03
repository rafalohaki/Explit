#pragma once
#include "../../sdk.hpp"
class i_panel
{
public:
	const char *get_name(unsigned int vguipanel)
	{
		return vfunc<36, const char *, unsigned int>(this, vguipanel);
	}
};