#include "model/terrain.h"
#include "model/mesh_factory.h"

float terrainFunc( float x, float z ) // 二元函数
{
	return sin(x) * sin(z);
}

void terrainDiffFunc( float x, float z, float& dx, float& dy, float& dz ) // 二元函数的导数的三个分量
{
	dx = - cos(x) * sin(z);
	dy = - sin(x) * cos(z);
	dz = 1;
	D3DXVECTOR3 t_vec(dx, dy, dz);
	D3DXVec3Normalize( &t_vec, &t_vec );
	dx = t_vec.x;
	dy = t_vec.y;
	dz = t_vec.z;
}

void Terrain::Config()
{
	m_range_x = 20.f;
	m_range_y = 20.f;
	GenerateTerrainMeshByFunc<ModelVertexStruct>( m_vertex_arr, m_vertex_size, m_index_arr, m_index_size, &terrainFunc, &terrainDiffFunc, m_range_x, m_range_y );

	D3DXMatrixTranslation( &m_matrix, 0, 0, 0 );
}