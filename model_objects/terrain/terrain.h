#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MODEL_OBJECTS_TERRAIN_TERRAIN_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__MODEL_OBJECTS_TERRAIN_TERRAIN_H__

#include "model_objects/meshmodel/model.h"

class Terrain : public Model
{
public:
	void Config();

private:
	float m_range_x;
	float m_range_y;
};

#endif 