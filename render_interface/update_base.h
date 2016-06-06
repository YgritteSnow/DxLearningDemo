#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__RENDER_INTERFACE_UPDATE_BASE_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__RENDER_INTERFACE_UPDATE_BASE_H__

#include <Windows.h>

class UpdateBase
{
public:
	virtual void Update( DWORD timeDelta ) = 0;
};

#endif 