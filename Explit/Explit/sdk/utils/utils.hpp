#pragma once
#include "../sdk.hpp"
#define INRANGE(x,a,b)   (x >= a && x <= b)
#define GET_BYTE( x )    (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))
#define GET_BITS( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))

class c_utils {
private:
	inline std::string const& to_string(std::string const& s);
public:
	uintptr_t find_signature(const char* module, const char* signature);
	template<typename... Args>
	std::string stringer(Args const&... args);

};
extern c_utils g_utils;
