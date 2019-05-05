#pragma once
#include "../../sdk/sdk.hpp"

class c_dlight
{
private:
	void dlight(c_base_entity* pplayer, const colorrgbexp32 color);
public:
	void start();
};
extern c_dlight g_dlight;