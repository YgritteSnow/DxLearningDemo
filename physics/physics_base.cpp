#include "physics/physics_base.h"

bool OnCollision( BallCollisionObject* ball, PolyCollisionObject* cube )
{
	// 分 4 种情况：
	// 1. 球与面接触
	//	1) 球心在面上的投影在面的内部
	//  2) 球在面的正面
	//  3) 球心与面的距离小于球半径
	// 2. 球与棱接触
	//  1) 以上条件均不满足
	//  2) 球心与边的距离小于球半径
	// 3. 球与角接触
	//  1) 以上条件均不满足
	//  2) 球心与角的距离小于求半径

	for( size_t i = 0; i < cube->m_primitive_indecies.size(); ++i )
	{
		// 遍历每一个面，寻找以上三种情况
		PolyCollisionObject::PrimitiveStruct primi = cube->m_primitive_indecies[i];

		// 1. 球与面接触：
	}

	for( size_t i = 0; i < cube->m_edge_indecies.size(); ++i )
	{
		PolyCollisionObject::EdgeStruct primi = cube->m_edge_indecies[i];

		// 2. 球与边接触：
	}

	for( size_t i = 0; i < cube->m_points.size(); ++i )
	{
		D3DXVECTOR3 primi = cube->m_points[i];

		// 3. 球与角接触：
	}

	return false;
}

bool OnCollision( PolyCollisionObject* ball, BallCollisionObject* cube )
{
	return OnCollision( cube, ball );
}

bool OnCollision( PolyCollisionObject* ball, PolyCollisionObject* cube )
{
	// 分 2 种情况：
	// 1. 边与边接触
	// 2. 点与面接触

	return false;
}

bool OnCollision( BallCollisionObject* ball, BallCollisionObject* cube )
{
	// 分 1 种情况：
	// boom！

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