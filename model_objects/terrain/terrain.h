#ifndef __MODEL_OBJECTS_TERRAIN_TERRAIN_H__
#define __MODEL_OBJECTS_TERRAIN_TERRAIN_H__

#include "model_objects/meshmodel/model.h"

class Terrain : public Model
{
public:
	Terrain( const char* filename ):Model(filename){}

private:
	float m_range_x;
	float m_range_y;
};

#endif 