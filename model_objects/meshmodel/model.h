#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MODEL_OBJECTS_MESHMODEL_MODEL_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MODEL_OBJECTS_MESHMODEL_MODEL_H__

#include <d3dx9.h>
#include <d3dx9math.h>
#pragma comment(lib, "d3dx9.lib")
#include "render_interface/render_object_base.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
struct PosVertex{
	float _x, _y, _z;
};

struct ModelVertex;
class Model : public RenderObjectBase
{
public:
	typedef ModelVertex ModelVertexStruct;

	Model():m_vb(NULL), m_ib(NULL), m_vertex_arr(NULL), m_index_arr(NULL){};
	virtual ~Model();
	virtual void PreRender( LPDIRECT3DDEVICE9 device );
	virtual void Render( LPDIRECT3DDEVICE9 device );

protected:
	virtual void Config();

	LPDIRECT3DVERTEXBUFFER9 m_vb;
	LPDIRECT3DINDEXBUFFER9 m_ib;

	int m_vertex_size;
	ModelVertexStruct* m_vertex_arr;
	
	int m_index_size;
	WORD* m_index_arr;

	D3DXMATRIX m_matrix;
};

#endif 