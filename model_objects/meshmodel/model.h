#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MODEL_OBJECTS_MESHMODEL_MODEL_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MODEL_OBJECTS_MESHMODEL_MODEL_H__

#include <d3dx9.h>
#include <d3dx9math.h>
#pragma comment(lib, "d3dx9.lib")
#include "render_interface/render_object_base.h"
#include "model_objects/meshmodel/model_mesh.h"
#include "model_objects/meshmodel/texture.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/

struct ModelVertex;
class Model : public RenderObjectBase, public FileReadBase
{
public:
	Model( const char* filename ):FileReadBase( filename ){}
	virtual ~Model(){};

	virtual void Config(){}
	virtual void PreRender( LPDIRECT3DDEVICE9 device );
	virtual void Render( LPDIRECT3DDEVICE9 device );

protected:
	bool OnLoadByDataSection( DataSection* rootSec );

	ModelMesh m_model_mesh;
	ModelTexture m_model_texture;
};

#endif 