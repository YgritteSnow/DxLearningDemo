#include "model_objects/meshmodel/texture.h"
#include "file_reader/file_reader.h"

ModelTexture::ModelTexture()
	: m_ptex(NULL)
	, m_isSpecularEnable(false)
	, m_isAlphaEnable(false)
{}

ModelTexture::ModelTexture( const char* filename )
	: m_ptex(NULL)
	, m_isSpecularEnable(false)
	, m_isAlphaEnable(false)
	, FileReadBase( filename )
{}

ModelTexture::ModelTexture( DataSection* rootSec )
	: m_ptex(NULL)
	, m_isSpecularEnable(false)
	, m_isAlphaEnable(false)
	, FileReadBase( rootSec )
{}

ModelTexture::~ModelTexture()
{
	if( m_ptex )
	{
		m_ptex->Release();
		m_ptex = NULL;
	}
};

bool ModelTexture::OnLoadByDataSection( DataSection* rootSec )
{
	DataSection* childSec = NULL;
	if( rootSec->GetChildByName( "specularEnable", childSec ) )
	{
		m_isSpecularEnable = childSec->GetData<bool>();
	}
	if( rootSec->GetChildByName( "alphaEnable", childSec ) )
	{
		m_isAlphaEnable = childSec->GetData<bool>();
	}

	if( rootSec->GetChildByName( "texture", childSec ) )
	{
		std::string filename = childSec->GetData<std::string>();
		return FileReaderManager::GetFileReaderManager().ReadFile_texture( filename.c_str(), m_ptex );
	}
	else
	{
		return false;
	}

	ZeroMemory( &m_mtl, sizeof(m_mtl) );
	if( rootSec->GetChildByName( "material", childSec ) )
	{
		DataSection* childchild = NULL;
		if( childSec->GetChildByName( "Ambient", childchild ) )
		{
			m_mtl.Ambient.a = childchild->GetData<float>();
			m_mtl.Ambient.r = childchild->GetData<float>();
			m_mtl.Ambient.g = childchild->GetData<float>();
			m_mtl.Ambient.b = childchild->GetData<float>();
		}

		if( childSec->GetChildByName( "Diffuse", childchild ) )
		{
			m_mtl.Diffuse.a = childchild->GetData<float>();
			m_mtl.Diffuse.r = childchild->GetData<float>();
			m_mtl.Diffuse.g = childchild->GetData<float>();
			m_mtl.Diffuse.b = childchild->GetData<float>();
		}

		if( childSec->GetChildByName( "Specular", childchild ) )
		{
			m_mtl.Specular.a = childchild->GetData<float>();
			m_mtl.Specular.r = childchild->GetData<float>();
			m_mtl.Specular.g = childchild->GetData<float>();
			m_mtl.Specular.b = childchild->GetData<float>();
		}

		if( childSec->GetChildByName( "Emissive", childchild ) )
		{
			m_mtl.Emissive.a = childchild->GetData<float>();
			m_mtl.Emissive.r = childchild->GetData<float>();
			m_mtl.Emissive.g = childchild->GetData<float>();
			m_mtl.Emissive.b = childchild->GetData<float>();
		}

		if( childSec->GetChildByName( "Power", childchild ) )
		{
			m_mtl.Power = childchild->GetData<float>();
		}
	}

	return true;
}

void ModelTexture::Render( LPDIRECT3DDEVICE9 device )
{
	if( !IsLoaded() )
		return;

	device->SetRenderState( D3DRS_ALPHABLENDENABLE, m_isAlphaEnable );
	if( m_isAlphaEnable )
	{
		device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

		device->SetTextureStageState( 0, D3DTSS_ALPHAARG0, D3DTA_TEXTURE );
		device->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1 );
	}

	device->SetRenderState( D3DRS_SPECULARENABLE, m_isSpecularEnable );

	device->SetMaterial( &m_mtl );

	device->SetTexture( 0, m_ptex );
}