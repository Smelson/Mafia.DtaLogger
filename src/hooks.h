#ifndef _HOOKS_H_
#define _HOOKS_H

#include <Windows.h>

namespace hooks
{
	void get_game_version();
	HMODULE wait_for_rwdata();
	void dta_open();
}

#endif
