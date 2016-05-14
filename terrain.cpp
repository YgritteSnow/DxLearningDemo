#include "terrain.h"
#include "mesh_factory.h"

float terrainFunc( float x, float y )
{
	return 0.f;
}

void Terrain::Config()
{
	m_vb = NULL;
	m_ib = NULL;
	GenerateTerrainMeshByFunc<ModelVertexStruct>( m_vertex_arr, m_vertex_size, m_index_arr, m_index_size, &terrainFunc );
	PaintMesh<ModelVertexStruct>( m_vertex_arr, m_vertex_size );

	D3DXMatrixTranslation( &m_matrix, 0, 0, 0 );
}