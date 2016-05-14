#ifndef __CAMERA_SIMPLE_MOVE_H__
#define __CAMERA_SIMPLE_MOVE_H__

#include "camera.h"

class CameraSimpleMove : public Camera
{
public:
	CameraSimpleMove(){}

	virtual void Config();
	virtual bool OnKeyMoveDown( int x, int y, int z );

private:
	D3DXVECTOR3 m_eyepos;
	D3DXVECTOR3 m_eyeypr;
	D3DXMATRIX m_rotMat;
};


#endif 