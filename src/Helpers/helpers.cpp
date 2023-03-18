#include "Helpers.hpp"

DWORD Helpers::GetPointerAddress(DWORD baseAddress, std::vector<DWORD> offsets)
{
	DWORD addr = baseAddress;
	for (size_t i = 0; i < offsets.size(); i++)
	{
		addr = *(DWORD*)addr;
		addr += offsets[i];
	}
	return addr;
}

void Helpers::InstallJmpHook(DWORD hookAddress, DWORD myFunction)
{
	DWORD protect[2];
	VirtualProtect((void*)hookAddress, 5, PAGE_EXECUTE_READWRITE, &protect[0]);
	*(BYTE*)hookAddress = 0xE9;
	*(DWORD*)(hookAddress + 1) = (myFunction - hookAddress) - 5;
	VirtualProtect((void*)hookAddress, 5, protect[0], &protect[1]);
}

void Helpers::InstallCallHook(DWORD hookAddress, DWORD myFunction)
{
	DWORD protect[2];
	VirtualProtect((void*)hookAddress, 5, PAGE_EXECUTE_READWRITE, &protect[0]);
	*(BYTE*)hookAddress = 0xE8;
	*(DWORD*)(hookAddress + 1) = (myFunction - hookAddress) - 5;
	VirtualProtect((void*)hookAddress, 5, protect[0], &protect[1]);
}

void Helpers::PatchBytes(DWORD hookAddress, void *data, int count)
{
    DWORD protect[2];
    VirtualProtect((void*)hookAddress, count, PAGE_EXECUTE_READWRITE, &protect[0]);
    memcpy((void*)hookAddress, data, count);
    VirtualProtect((void*)hookAddress, count, protect[0], &protect[1]);
}

void Helpers::Nop(DWORD hookAddress, int count)
{
	DWORD tempAddress = hookAddress;
	DWORD protect[2];
	VirtualProtect((void*)hookAddress, count, PAGE_EXECUTE_READWRITE, &protect[0]);
	for (int i = 0; i < count; tempAddress++, i++)
	{
		*(BYTE*)tempAddress = 0x90;
	}
	VirtualProtect((void*)hookAddress, count, protect[0], &protect[1]);
}