#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MODEL_OBJECTS_MESHMODEL_MESH_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MODEL_OBJECTS_MESHMODEL_MESH_H__

#include <d3dx9.h>
#include <d3dx9math.h>
#pragma comment(lib, "d3dx9.lib")

#include "render_interface/render_object_base.h"
#include "file_reader/data_section.h"

struct ModelVertex;
class ModelMesh : public RenderObjectBase
{
public:
	ModelMesh();
	~ModelMesh();

	typedef ModelVertex ModelVertexStruct;

	void LoadByDataSection( DataSection* rootSec );

	virtual void Config(){}
	virtual void PreRender( LPDIRECT3DDEVICE9 device );
	virtual void Render( LPDIRECT3DDEVICE9 device );

private:
	bool m_isloaded;

	D3DFILLMODE m_d3d_fillmode;
	D3DCULL m_d3d_cullmode;

	LPDIRECT3DVERTEXBUFFER9 m_vb;
	LPDIRECT3DINDEXBUFFER9 m_ib;

	int m_vertex_size;
	ModelVertexStruct* m_vertex_arr;

	int m_index_size;
	WORD* m_index_arr;
};
#endif 