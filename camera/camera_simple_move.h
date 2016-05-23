#ifndef __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__CAMERA_CAMERA_SIMPLE_MOVE_H__
#define __F__MYPROJECTS_DXDEMO_1_DXDEMO_1__CAMERA_CAMERA_SIMPLE_MOVE_H__

#include "camera/camera.h"

class CameraSimpleMove : public Camera
{
public:
	CameraSimpleMove(){}

	virtual void Config();

	virtual bool OnMouseDownMove( int x, int y );
	virtual bool OnKeyMoveDown( int x, int y, int z );

private:
	void ReCalViewMat();

	D3DXVECTOR3 m_eyepos;
	D3DXVECTOR3 m_eyeypr;
	float m_move_speed;
	float m_mouse_speed;

	D3DXMATRIX m_rotMat;
};

#endif 