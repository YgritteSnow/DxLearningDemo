#include "model_objects/meshmodel/model.h"
#include "model_objects/meshmodel/mesh_factory.h"
#include "render_interface/manager.h"
#include "model_objects/model_vertex.h"
#include "file_reader/file_reader.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/

Model::~Model()
{}

void Model::LoadFromFile( const char* filename )
{
	DataSection* rootSec;
	FileReaderManager::GetFileReaderManager().ReadFile_dataSec( filename, rootSec );
	LoadByDataSection( rootSec );
}

void Model::LoadByDataSection( DataSection* rootSec )
{
	DataSection* childSec = NULL;
	rootSec->GetChildByName("mesh", childSec );
	m_model_mesh.LoadByDataSection( childSec );
	rootSec->GetChildByName("texture", childSec );
	m_model_texture.LoadByDataSection( childSec );
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