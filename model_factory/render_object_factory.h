#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MODEL_FACTORY_RENDER_OBJECT_FACTORY_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MODEL_FACTORY_RENDER_OBJECT_FACTORY_H__

class Model;

class RenderObjectFactoryManager
{
public:
	void LoadModel( const char* file_name, Model* model );
};

#endif 