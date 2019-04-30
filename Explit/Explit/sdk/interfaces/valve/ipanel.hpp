#pragma once
#include "../../sdk.hpp"
class IPanel
{
public:
	const char *getname(unsigned int vguipanel)
	{
		return vfunc<36, const char *, unsigned int>(this, vguipanel);
	}
};