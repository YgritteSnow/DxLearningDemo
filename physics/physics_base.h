#ifndef __PHYSICS_PHYSICS_BASE_H__
#define __PHYSICS_PHYSICS_BASE_H__

#include <vector>
#include <d3dx9.h>
#include <d3dx9math.h>
#pragma comment(lib, "d3dx9.lib")

#include "render_interface/update_base.h"

/************************************************************************/
/** 分为两种物体：
 *	1. 球
 *	2. 多面体
/************************************************************************/

class PhysicsObject : public UpdateBase
{
public:
	PhysicsObject(){}
	virtual ~PhysicsObject(){}

	virtual bool OnCollision( PhysicsObject* otherObj );

	virtual void ResetAccelerate(){ m_accelerate.x = m_accelerate.y = m_accelerate.z = 0; }

	// todo 带有受力点的受力
	virtual void OnElastic( const D3DXVECTOR3& direct, const D3DXVECTOR3& point ){ /*????*/ }
	// todo 受力点作用在质心上的受力
	virtual void OnElastic( const D3DXVECTOR3& direct ){ m_accelerate += direct * m_elasticity; }

	virtual void Update( DWORD timeDelta ){ /*????*/ };

protected:
	D3DXMATRIX m_mat; // 模型的矩阵

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
	virtual bool OnCollision( BallCollisionObject* otherObj )
	{
		return ::OnCollision( this, otherObj );
	}

protected:
	std::vector< D3DXVECTOR3 > m_points; // 局部坐标系下的坐标
	
	struct PrimitiveStruct
	{
		DWORD idx_1;
		DWORD idx_2;
		DWORD idx_3;
	};
	std::vector< PrimitiveStruct > m_primitive_indecies; // 三角形面片的列表

	struct EdgeStruct
	{
		DWORD idx_1;
		DWORD idx_2;
	};
	std::vector< EdgeStruct > m_edge_indecies; // 三角形面片的列表
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
	virtual bool OnCollision( BallCollisionObject* otherObj )
	{
		return ::OnCollision( this, otherObj );
	}

	const float GetRadius() const { return m_radius; }
	const float GetRadiusSqare() const { return m_radius * m_radius; }

protected:
	float m_radius;
};

#endif 