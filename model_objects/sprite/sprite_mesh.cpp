#include "model_objects/sprite/sprite_mesh.h"
#include "tool_funcs/tool_funcs.h"

SpriteMesh::SpriteMesh()
	: m_vb(NULL)
{}

SpriteMesh::SpriteMesh( DataSection* rootSec )
	: m_vb(NULL)
	, FileReadBase( rootSec )
{}

SpriteMesh::~SpriteMesh()
{
	if( m_vb )
	{
		m_vb->Release();
		delete m_vb;
		m_vb = NULL;
	}
	if( m_vertex_arr )
	{
		delete [] m_vertex_arr;
		m_vertex_arr = NULL;
	}
}

void SpriteMesh::PreRender( LPDIRECT3DDEVICE9 device )
{
	if( !IsLoaded() )
		return;

	// ���㻺��
	if( FAILED( device->CreateVertexBuffer(
		m_vertex_size * sizeof( ModelVertexStruct ), 
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY, 
		ModelVertexStruct::FVF, 
		D3DPOOL_DEFAULT, 
		&m_vb, 
		NULL
		) ) )
		return;

	return;
}

void SpriteMesh::Render( LPDIRECT3DDEVICE9 device )
{
	if( !IsLoaded() )
		return;

	device->SetRenderState( D3DRS_LIGHTING, false );
	device->SetRenderState( D3DRS_POINTSPRITEENABLE, true );
	device->SetRenderState( D3DRS_POINTSCALEENABLE, true );
	device->SetRenderState( D3DRS_POINTSCALE_A, Tools::FtoD(0.0f));
	device->SetRenderState( D3DRS_POINTSCALE_B, Tools::FtoD(0.0f));
	device->SetRenderState( D3DRS_POINTSCALE_C, Tools::FtoD(1.0f));
	float t = 1.0f;
	device->SetRenderState( D3DRS_POINTSIZE, *((DWORD*)&(t)) );
	device->SetFVF( ModelVertexStruct::FVF );
	device->SetStreamSource( 0, m_vb, 0, sizeof(ModelVertexStruct) );
	//debug
	ModelVertexStruct vb[1];
	m_vb->Lock( 
		0, 
		1 * sizeof( ModelVertexStruct ), 
		(void**)&vb, 
		D3DLOCK_DISCARD 
		);
	vb[0]._x = 0.1f;
	vb[0]._y = 0.1f;
	vb[0]._z = 0.1f;
	vb[0]._color = 0xff0000ff;
	m_vb->Unlock();
	device->DrawPrimitive( D3DPT_POINTLIST, 0, 1 );


	// ѭ�������õ����ɸ����ŵ����ӣ�ÿ�����ɸ����ֳ����ɴ���Ⱦ����
	//ModelVertexStruct vb[c_render_size_of_sprite_at_one_shot];
	//size_t temp_size;
	//temp_size = 0;
	//for( size_t i = 0; i < m_vec_sprite.size(); ++i )
	//{
	//	if( m_vec_sprite[i]->isDead() )
	//	{
	//		continue;
	//	}

	//	if( temp_size % c_render_size_of_sprite_at_one_shot == 0 )
	//	{
	//		if( temp_size != 0 )
	//		{
	//			m_vb->Unlock();
	//			device->DrawPrimitive( D3DPT_POINTLIST, temp_size - c_render_size_of_sprite_at_one_shot, c_render_size_of_sprite_at_one_shot );
	//		}
	//		m_vb->Lock( 
	//			temp_size * sizeof( ModelVertexStruct ), 
	//			c_render_size_of_sprite_at_one_shot * sizeof( ModelVertexStruct ), 
	//			(void**)&vb, 
	//			(temp_size == 0) ? D3DLOCK_DISCARD : D3DLOCK_NOOVERWRITE
	//			);
	//	}
	//	size_t idx = temp_size % c_render_size_of_sprite_at_one_shot;
	//	
	//	vb[idx]._x = m_vec_sprite[i]->_x;
	//	vb[idx]._y = m_vec_sprite[i]->_y;
	//	vb[idx]._z = m_vec_sprite[i]->_z;
	//	vb[idx]._color = m_vec_sprite[i]->_color;
	//	//vb[idx]._size = 100.f;

	//	++temp_size;
	//}
	//m_vb->Unlock();
	//device->DrawPrimitive( D3DPT_POINTLIST, temp_size - (temp_size % c_render_size_of_sprite_at_one_shot), (temp_size % c_render_size_of_sprite_at_one_shot) );

	device->SetRenderState( D3DRS_POINTSPRITEENABLE, false );
	device->SetRenderState( D3DRS_POINTSCALEENABLE, false );
	device->SetRenderState( D3DRS_LIGHTING, true );
}

bool SpriteMesh::OnLoadByDataSection( DataSection* rootSec )
{
	DataSection* childSec = NULL;
	if( rootSec->GetChildByName( "spritemaxcount", childSec ) )
	{
		m_vertex_size = (D3DCULL)childSec->GetData<int>();
	}
	else
	{
		return false;
	}

	return true;
}