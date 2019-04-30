#include "sdk.hpp"
c_sdk g_sdk;


void c_sdk::on_inject()
{
#ifdef _DEBUG       
	AllocConsole();
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	SetConsoleTitleA("Explit Debug Console");
#endif
	HWND csgo = nullptr;

	while (!(csgo = FindWindowA("Valve001", nullptr)))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	g_interfaces.get_interfaces();
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	c.netvar = std::shared_ptr<c_netvarmanager>(new c_netvarmanager());
	g_hooks.get_hooks();

	

}

void c_sdk::un_inject()
{
#ifdef _DEBUG       
	fclose((FILE*)stdin);
	fclose((FILE*)stdout);

	HWND hw_ConsoleHwnd = GetConsoleWindow();
	FreeConsole();
	PostMessageW(hw_ConsoleHwnd, WM_CLOSE, 0, 0);
#endif
	g_hooks.un_hooks();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}