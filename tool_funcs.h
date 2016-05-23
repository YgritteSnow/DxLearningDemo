#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__TOOL_FUNCS_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__TOOL_FUNCS_H__
#include <Windows.h>
DWORD FtoD(float f)
{
	return *(DWORD*)(&f);
}

#endif 