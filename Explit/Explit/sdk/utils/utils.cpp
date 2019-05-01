#include "utils.hpp"
c_utils g_utils;

uintptr_t c_utils::find_signature(const char* module, const char* signature)
{
	const char* pat = signature;
	DWORD firstmatch = 0;
	DWORD rangestart = (DWORD)GetModuleHandleA(module);
	MODULEINFO miModInfo;
	GetModuleInformation(GetCurrentProcess(), (HMODULE)rangestart, &miModInfo, sizeof(MODULEINFO));
	DWORD rangeEnd = rangestart + miModInfo.SizeOfImage;
	for (DWORD pCur = rangestart; pCur < rangeEnd; pCur++)
	{
		if (!*pat)
			return firstmatch;

		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == GET_BYTE(pat))
		{
			if (!firstmatch)
				firstmatch = pCur;

			if (!pat[2])
				return firstmatch;

			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
				pat += 3;

			else
				pat += 2;
		}
		else
		{
			pat = signature;
			firstmatch = 0;
		}
	}
	return 0u;
}
inline std::string const& to_string(std::string const& s) { return s; }
template<typename... Args>
std::string c_utils::stringer(Args const&... args)
{
	std::string result;
	using ::to_string;
	using std::to_string;
	int unpack[]{ 0, (result += to_string(args), 0)... };
	static_cast<void>(unpack);
	return result;
}
