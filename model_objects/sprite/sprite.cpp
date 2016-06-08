#include "model_objects/sprite/sprite.h"
#include "tool_funcs/tool_funcs.h"

DWORD SpriteVertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE ;
const static size_t c_render_size_of_sprite_at_one_shot = 1000;

#define TEX_FILE_PATH L"tex_alpha.png"

void Sprite::PreRender( LPDIRECT3DDEVICE9 device )
{
}

void Sprite::Render( LPDIRECT3DDEVICE9 device )
{
	m_ptex.Render( device );
	m_spirte_mesh.Render( device );
}

void Sprite::Update( DWORD timeDelta )
{
	OnResetSprites( timeDelta );
}

bool Sprite::OnLoadByDataSection( DataSection* rootSec )
{
	bool ret = true;

	DataSection* childSec = NULL;
	if( !( rootSec->GetChildByName( "spritemesh", childSec ) && m_spirte_mesh.OnLoadByDataSection( childSec ) ) )
		return false;

	if( !( rootSec->GetChildByName( "texture", childSec ) && m_ptex.OnLoadByDataSection( childSec ) ) )
		return false;

	return true;
}