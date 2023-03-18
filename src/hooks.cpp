#include "hooks.h"
#include <iostream>
#include <fstream>
#include <vector>

namespace hooks
{
	DWORD dta_open_return;
	char* file_name;

	void get_game_version()
	{
		if (*(DWORD*)0x005BEC2E != 0x18B)
		{
			MessageBoxA(NULL, "Wrong game version!\n\nYou should use Mafia v1.2!", "Error!", MB_ICONERROR);
			exit(1);
		}
	}

	HMODULE wait_for_rwdata()
	{
		while (GetModuleHandleA("rw_data.dll") == NULL)
		{
			Sleep(10);
		}

		HMODULE rw_data = GetModuleHandleA("rw_data.dll");
		
		dta_open_return = (DWORD)rw_data + 0x18A0 + 0x161 + 0x5;

		return rw_data;
	}

	void print_dta_file(const char* file_name_print)
	{
		printf("[INFO] -> File %s was opened!\n", file_name_print);
	}

	__declspec(naked) void dta_open()
	{
		_asm
		{
			mov ecx, [esp+0x68]
			push ecx
			mov file_name, ecx
		}

		_asm pushad
		print_dta_file(file_name);
		_asm popad

		_asm 
		{
			jmp dta_open_return
		}
	}
}