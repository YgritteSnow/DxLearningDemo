#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "model.h"

class Terrain : public Model
{
public:
	void Config();

private:
	float m_range_x;
	float m_range_y;
};
#endif