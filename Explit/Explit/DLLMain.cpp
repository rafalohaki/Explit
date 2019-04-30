#include "sdk/sdk.hpp"
DWORD WINAPI attach(HMODULE hModule)
{
	g_sdk.on_inject();
	while (!g_sdk.unhook) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	FreeLibraryAndExitThread(hModule, 1);
}
BOOL APIENTRY DllMain(HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH: 
		{
			DisableThreadLibraryCalls(hModule);
			auto handle = CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)attach, hModule, NULL, nullptr);

			CloseHandle(handle);
		}
		 break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
		{
			g_sdk.un_inject();
		}
			break;
	}
	return TRUE;
}