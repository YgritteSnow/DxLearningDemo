#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__TOOL_FUNCS_TOOL_FUNCS_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__TOOL_FUNCS_TOOL_FUNCS_H__

#include <Windows.h>

class Tools
{
public:
	static DWORD FtoD(float f)
	{
		return *(DWORD*)(&f);
	}

	static float RandFloat()
	{
		return (float)rand() / (float)(unsigned)(-1);
	}

	static float RandFloat( float range_min, float range_max )
	{
		return range_min + RandFloat() * ( range_max - range_min );
	}

	static float RandFloat( float range_scale )
	{
		return RandFloat() * range_scale;
	}

	static D3DXVECTOR3 RandVector3()
	{
		D3DXVECTOR3 t = D3DXVECTOR3( RandFloat(-1,1), RandFloat(-1,1), RandFloat(-1,1) );
		D3DXVec3Normalize( &t, &t );
		return t;
	}
};

#endif 