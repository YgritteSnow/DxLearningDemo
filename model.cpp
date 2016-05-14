#include "model.h"
#include "mesh_factory.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
DWORD ModelVertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;

Model::~Model()
{
	if( m_vb )
	{
		m_vb->Release();
		m_vb = NULL;
	}
	if( m_ib )
	{
		m_ib->Release();
		m_ib = NULL;
	}
	if( m_index_arr )
		delete[] m_index_arr;
	if( m_vertex_arr )
		delete[] m_vertex_arr;
}

void Model::Config()
{
	m_vb = NULL;
	m_ib = NULL;
	GenerateBallMesh<ModelVertexStruct>( m_vertex_arr, m_vertex_size, m_index_arr, m_index_size, 1.f );
	PaintMesh<ModelVertexStruct>( m_vertex_arr, m_vertex_size );

	D3DXMatrixTranslation( &m_matrix, 0, 0, 0 );
}

void Model::PreRender( LPDIRECT3DDEVICE9 device )
{
	// ¶¥µã»º´æ
	if( FAILED( device->CreateVertexBuffer(
		m_vertex_size * sizeof( ModelVertexStruct ), 
		D3DUSAGE_SOFTWAREPROCESSING, 
		ModelVertexStruct::FVF, 
		D3DPOOL_DEFAULT, 
		&m_vb, 
		NULL
		) ) )
		return;

	ModelVertexStruct* verticies = NULL;
	m_vb->Lock( 0, 0, (void **) &verticies, 0 );
	memcpy( verticies, m_vertex_arr, m_vertex_size * sizeof( ModelVertexStruct ) );
	m_vb->Unlock();

	// Ë÷Òý»º´æ
	if( FAILED( device->CreateIndexBuffer(
		m_index_size * sizeof(WORD), 
		D3DUSAGE_SOFTWAREPROCESSING, 
		D3DFMT_INDEX16, 
		D3DPOOL_DEFAULT, 
		&m_ib, 
		NULL 
		) ) )
		return;

	WORD* indices = NULL;
	m_ib->Lock( 0, 0, (void **) &indices, 0 );
	memcpy( indices, m_index_arr, m_index_size * sizeof(WORD) );
	m_ib->Unlock();

	return;
}

void Model::Render( LPDIRECT3DDEVICE9 device )
{
	// Ìî³ä
	device->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	// ±³ÃæÏûÒþ
	device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

 	device->SetStreamSource( 0, m_vb, 0, sizeof(ModelVertexStruct) );
	device->SetFVF( ModelVertexStruct::FVF );
	device->SetIndices( m_ib );
	device->SetTransform( D3DTS_WORLD, &m_matrix );
	device->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, m_vertex_size, 0, m_index_size / 3 );
	/*LPD3DXMESH pmesh = NULL;
	D3DXCreateTeapot( device, &pmesh, NULL );
	pmesh->DrawSubset(0);*/
}
