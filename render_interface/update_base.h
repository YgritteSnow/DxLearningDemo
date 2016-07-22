#ifndef __RENDER_INTERFACE_UPDATE_BASE_H__
#define __RENDER_INTERFACE_UPDATE_BASE_H__

#include <Windows.h>

class UpdateBase
{
public:
	virtual void Update( DWORD timeDelta ) = 0;
};

#endif 