#include "physics/physics_base.h"

bool OnCollision( BallCollisionObject* ball, PolyCollisionObject* cube )
{
	// �� 4 �������
	// 1. ������Ӵ�
	//	1) ���������ϵ�ͶӰ������ڲ�
	//  2) �����������
	//  3) ��������ľ���С����뾶
	// 2. ������Ӵ�
	//  1) ����������������
	//  2) ������ߵľ���С����뾶
	// 3. ����ǽӴ�
	//  1) ����������������
	//  2) ������ǵľ���С����뾶

	for( size_t i = 0; i < cube->m_primitive_indecies.size(); ++i )
	{
		// ����ÿһ���棬Ѱ�������������
		PolyCollisionObject::PrimitiveStruct primi = cube->m_primitive_indecies[i];

		// 1. ������Ӵ���
	}

	for( size_t i = 0; i < cube->m_edge_indecies.size(); ++i )
	{
		PolyCollisionObject::EdgeStruct primi = cube->m_edge_indecies[i];

		// 2. ����߽Ӵ���
	}

	for( size_t i = 0; i < cube->m_points.size(); ++i )
	{
		D3DXVECTOR3 primi = cube->m_points[i];

		// 3. ����ǽӴ���
	}

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