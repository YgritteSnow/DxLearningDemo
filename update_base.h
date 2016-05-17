#ifndef __UPDATE_BASE_H__
#define __UPDATE_BASE_H__

#include <Windows.h>

class UpdateBase
{
public:
	virtual void Update( DWORD timeDelta ) = 0;
};

#endif