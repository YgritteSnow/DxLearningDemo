#ifndef __F__MYPROJECTS_DXDEMO_1_DXMO_1__MODEL_MODEL_MATERIAL_H__
#define __F__MYPROJECTS_DXDEMO_1_DXMO_1__MODEL_MODEL_MATERIAL_H__

#include <d3dx9.h>
#include <d3dx9math.h>
#pragma comment(lib, "d3dx9.lib")

#include "update_base.h"

/************************************************************************/
/** ��Ϊ�������壺
 *	1. ��
 *	2. ������
/************************************************************************/

class PhysicsObject : public UpdateBase
{
public:
	PhysicsObject(){}
	virtual ~PhysicsObject(){}

	virtual bool OnCollision( PhysicsObject* otherObj );

	virtual void ResetAccelerate(){ m_accelerate.x = m_accelerate.y = m_accelerate.z = 0; }

	// todo ���������������
	virtual void OnElastic( const D3DXVECTOR3& direct, const D3DXVECTOR3& point ){ /*????*/ }
	// todo �����������������ϵ�����
	virtual void OnElastic( const D3DXVECTOR3& direct ){ m_accelerate += direct * m_elasticity; }

	virtual void Update( DWORD timeDelta ){ /*????*/ };

protected:
	D3DXMATRIX m_mat; // ģ�͵ľ���

private:
	D3DXVECTOR3 m_speed;
	D3DXVECTOR3 m_accelerate;
	float m_elasticity;
};

class BallCollisionObject;
class PolyCollisionObject : public PhysicsObject
{
public:
	friend bool OnCollision( BallCollisionObject* ball, PolyCollisionObject* cube );
	friend bool OnCollision( PolyCollisionObject* ball, BallCollisionObject* cube );
	friend bool OnCollision( PolyCollisionObject* ball, PolyCollisionObject* cube );
	friend bool OnCollision( BallCollisionObject* ball, BallCollisionObject* cube );

	virtual bool OnCollision( PolyCollisionObject* otherObj )
	{
		return ::OnCollision( this, otherObj );
	}
	virtual bool OnCollision( BallCollisionObject* otherObj );
	{
		return ::OnCollision( this, otherObj );
	}

protected:
	std::vector< D3DXVECTOR3 > m_points; // �ֲ�����ϵ�µ�����
};

class BallCollisionObject : public PhysicsObject
{
public:
	friend bool OnCollision( BallCollisionObject* ball, PolyCollisionObject* cube );
	friend bool OnCollision( PolyCollisionObject* ball, BallCollisionObject* cube );
	friend bool OnCollision( PolyCollisionObject* ball, PolyCollisionObject* cube );
	friend bool OnCollision( BallCollisionObject* ball, BallCollisionObject* cube );

	virtual bool OnCollision( PolyCollisionObject* otherObj )
	{
		return ::OnCollision( this, otherObj );
	}
	virtual bool OnCollision( BallCollisionObject* otherObj );
	{
		return ::OnCollision( this, otherObj );
	}

	const float GetRadius() const { return m_radius; }
	const float GetRadiusSqare() const { return m_radius * m_radius; }

protected:
	float m_radius;
};


bool OnCollision( BallCollisionObject* ball, PolyCollisionObject* cube )
{
	// �� 4 �������
	// 1. ������Ӵ�
	// 2. ������Ӵ�
	// 3. ����ǽӴ�

	return false;
}

bool OnCollision( PolyCollisionObject* ball, BallCollisionObject* cube )
{
	return OnCollision( cube, ball );
}

bool OnCollision( PolyCollisionObject* ball, PolyCollisionObject* cube )
{
	// �� 2 �������
	// 1. ����߽Ӵ�
	// 2. ������Ӵ�

	return false;
}

bool OnCollision( BallCollisionObject* ball, BallCollisionObject* cube )
{
	// �� 1 �������
	// boom��

	D3DXVECTOR3 dist;
	dist.x = ball->m_mat._41 - cube->m_mat._41;
	dist.y = ball->m_mat._42 - cube->m_mat._42;
	dist.z = ball->m_mat._43 - cube->m_mat._43;
	float elastic_dist = ball->GetRadius() + cube->GetRadius() - D3DXVec3LengthSq( &dist );

	if( dist > 0 )
	{
		D3DXVec3Normalize( &dist, &dist );
		ball->OnElastic( -dist * elastic_dist );
		cube->OnElastic( dist * elastic_dist );
		return true;
	}
	return false;
}

#endif