#include "model_objects/meshmodel/model_mesh.h"
#include "model_objects/model_vertex.h"
#include "model_objects/meshmodel/mesh_factory.h"

ModelMesh::ModelMesh()
	: m_d3d_fillmode( D3DFILL_WIREFRAME )
	, m_d3d_cullmode( D3DCULL_CCW )
	, m_vb(NULL)
	, m_ib(NULL)
{}

ModelMesh::ModelMesh( const char* filename )
	: m_d3d_fillmode( D3DFILL_WIREFRAME )
	, m_d3d_cullmode( D3DCULL_CCW )
	, m_vb(NULL)
	, m_ib(NULL)
	, FileReadBase( filename )
{}

ModelMesh::ModelMesh( DataSection* rootSec )
	: m_d3d_fillmode( D3DFILL_WIREFRAME )
	, m_d3d_cullmode( D3DCULL_CCW )
	, m_vb(NULL)
	, m_ib(NULL)
	, FileReadBase( rootSec )
{}

ModelMesh::~ModelMesh()
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
	if( m_vertex_arr )
	{
		delete [] m_vertex_arr;
		m_vertex_arr = NULL;
	}
}

void ModelMesh::PreRender( LPDIRECT3DDEVICE9 device )
{
	if( !IsLoaded() )
		return;

	// 顶点缓存
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

	// 索引缓存
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

void ModelMesh::Render( LPDIRECT3DDEVICE9 device )
{
	if( !IsLoaded() )
		return;

	device->SetRenderState( D3DRS_FILLMODE, m_d3d_fillmode);
	device->SetRenderState( D3DRS_CULLMODE, m_d3d_cullmode );

 	device->SetStreamSource( 0, m_vb, 0, sizeof(ModelVertexStruct) );
	device->SetFVF( ModelVertexStruct::FVF );
	device->SetIndices( m_ib );

	device->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, m_vertex_size, 0, m_index_size / 3 );
}

float terrainFunc( float x, float z ) // 二元函数
{
	return sin(x) * sin(z);
}

void terrainDiffFunc( float x, float z, float& dx, float& dy, float& dz ) // 二元函数的导数的三个分量
{
	dx = - cos(x) * sin(z);
	dy = - sin(x) * cos(z);
	dz = 1;
	D3DXVECTOR3 t_vec(dx, dy, dz);
	D3DXVec3Normalize( &t_vec, &t_vec );
	dx = t_vec.x;
	dy = t_vec.y;
	dz = t_vec.z;
}

bool ModelMesh::OnLoadByDataSection( DataSection* rootSec )
{
	DataSection* childSec = NULL;
	if( rootSec->GetChildByName( "cullmode", childSec ) )
		m_d3d_cullmode = (D3DCULL)childSec->GetData<int>();

	if( rootSec->GetChildByName( "fillmode", childSec ) )
		m_d3d_fillmode = (D3DFILLMODE)childSec->GetData<int>();

	if( rootSec->GetChildByName( "meshtype", childSec ) )
	{
		int mesh_case = childSec->GetData<int>();

		switch( mesh_case )
		{
		case 1:
			{
				GenerateBallMesh<ModelVertexStruct>( m_vertex_arr, m_vertex_size, m_index_arr, m_index_size, 1.f );
			}
			break;

		case 2:
			{
				GenerateTerrainMeshByFunc<ModelVertexStruct>( m_vertex_arr, m_vertex_size, m_index_arr, m_index_size, &terrainFunc, &terrainDiffFunc, 10.0, 10.0 );
			}
			break;

		default:
			return false;
		}
	}

	return true;
}