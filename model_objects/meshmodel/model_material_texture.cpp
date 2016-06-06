#include "model_objects/meshmodel/model_material_texture.h"
#include "model_objects/model_vertex.h"

#define TEX_FILE_PATH L"tex_alpha.png"

void ModelWithMaterialTexture::Config()
{
	// 依然使用最初的那个生成顶点的函数。。。直接随便加点东东就ok简直太好用了【懒 - -
	ModelWithMaterial::Config();

	/*ZeroMemory( &m_mtl, sizeof(m_mtl) );
	m_mtl.Ambient = D3DXCOLOR( 1, 1, 1, 1.0f );
	m_mtl.Diffuse = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	m_mtl.Specular = D3DXCOLOR( 0.5f, 0.5f, 0.5f, 1.0f );
	m_mtl.Emissive = D3DXCOLOR( 0.0f, 0.0f, 0.0f, 1.0f );
	m_mtl.Power = 1.f;

	GenerateBallMesh<ModelVertexStruct>( m_vertex_arr, m_vertex_size, m_index_arr, m_index_size, 1.f );
	PaintMesh<ModelVertexStruct>( m_vertex_arr, m_vertex_size );

	D3DXMatrixTranslation( &m_matrix, 0, 0, 0 );*/
}

void ModelWithMaterialTexture::PreRender( LPDIRECT3DDEVICE9 device )
{
	if( FAILED( D3DXCreateTextureFromFile(
		device, TEX_FILE_PATH, &m_ptex ) ) )
		exit(0);

	ModelWithMaterial::PreRender( device );
}

void ModelWithMaterialTexture::Render( LPDIRECT3DDEVICE9 device )
{
	device->SetTexture( 0, m_ptex );
	ModelWithMaterial::Render( device );
}