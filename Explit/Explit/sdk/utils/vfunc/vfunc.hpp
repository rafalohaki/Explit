#pragma once
#include "../../sdk.hpp"
//Credits to Wando1423
template<unsigned int index, typename t, typename ... args>
static t vfunc(void* thisptr, args ... arglist)
{
	using fn = t(__thiscall*)(void*, decltype(arglist)...);
	return (*static_cast<fn**>(thisptr))[index](thisptr, arglist...);
}