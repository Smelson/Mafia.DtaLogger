#pragma once
#include <Windows.h>
#include <vector>
#include <chrono>


namespace Helpers
{
	DWORD GetPointerAddress(DWORD baseAddress, std::vector<DWORD> offsets);
	void InstallJmpHook(DWORD hookAddress, DWORD myFunction);
	void InstallCallHook(DWORD hookAddress, DWORD myFunction);
    void PatchBytes(DWORD hookAddress, void* data, int count);
	void Nop(DWORD hookAddress, int count);
}