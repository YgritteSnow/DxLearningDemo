#ifndef __MODEL_H__
#define __MODEL_H__

#include <d3dx9.h>
#include <d3dx9math.h>
#pragma comment(lib, "d3dx9.lib")
#include "render_object_base.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
struct PosVertex{
	float _x, _y, _z;
};

struct ModelVertex// : public PosVertex
{
	ModelVertex()
		:_x(0), _y(0), _z(0), 
		_nx(0), _ny(0), _nz(0), 
		_color(0x0){}

	float _x, _y, _z;
	float _nx, _ny, _nz;
	DWORD _color;
	static DWORD FVF;
};

class Model : public RenderObjectBase
{
public:
	Model(){};
	virtual ~Model();
	virtual void PreRender( LPDIRECT3DDEVICE9 device );
	virtual void Render( LPDIRECT3DDEVICE9 device );

protected:
	virtual void Config();

	LPDIRECT3DVERTEXBUFFER9 m_vb;
	LPDIRECT3DINDEXBUFFER9 m_ib;
	typedef ModelVertex ModelVertexStruct;

	int m_vertex_size;
	ModelVertexStruct* m_vertex_arr;
	
	int m_index_size;
	WORD* m_index_arr;

	D3DXMATRIX m_matrix;
};

#endif