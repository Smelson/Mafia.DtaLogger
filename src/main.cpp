#include "main.h"

int __stdcall DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);

		AllocConsole();
		freopen("CONOUT$", "w", stdout);

		HMODULE rw_data = hooks::wait_for_rwdata();
		DWORD dtaOpen = (DWORD)rw_data + 0x18A0 + 0x161;

		printf("[INFO] -> rw_data.dll is loaded at 0x%0x\n\n", dtaOpen);
		
		CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(hooks::dumper), nullptr, NULL, nullptr);
		Helpers::InstallJmpHook(dtaOpen, (DWORD)hooks::dta_open);
	}

	if (dwReason == DLL_PROCESS_DETACH) {

	}

	return 1;
}