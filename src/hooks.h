#ifndef _HOOKS_H_
#define _HOOKS_H

#include <Windows.h>

namespace hooks
{
	HMODULE wait_for_rwdata();
	void dta_open();
	void dumper();
}

#endif
