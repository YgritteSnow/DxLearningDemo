#include "model_objects/meshmodel/model.h"
#include "model_objects/meshmodel/mesh_factory.h"
#include "render_interface/manager.h"
#include "model_objects/model_vertex.h"
#include "file_reader/file_reader.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/

bool Model::OnLoadByDataSection( DataSection* rootSec )
{
	bool ret = true;

	DataSection* childSec = NULL;
	if( !( rootSec->GetChildByName("mesh", childSec ) && m_model_mesh.OnLoadByDataSection( childSec ) ) )
		return false;

	if( !(rootSec->GetChildByName("texture", childSec ) && m_model_texture.OnLoadByDataSection( childSec ) ) )
		return false;

	return true;
}

void Model::PreRender( LPDIRECT3DDEVICE9 device )
{
	m_model_mesh.PreRender( device );
}

void Model::Render( LPDIRECT3DDEVICE9 device )
{
	m_model_texture.Render( device );
	m_model_mesh.Render( device );
}