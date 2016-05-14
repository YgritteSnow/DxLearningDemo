#ifndef __MESH_FACTORY_H__
#define __MESH_FACTORY_H__

#include <math.h>
#include <random>
#include <time.h>
#include <Windows.h>

template <typename VertexStruct>
void GenerateBallMesh( VertexStruct*& vbuffer, int& vcount, WORD*& ibuffer, int& icount, float radius )
{
	int theta_count = 13;
	float theta_step = 2 * 3.14f / theta_count;	// 绕着y轴旋转一圈

	int fai_count = 13;
	float fai_step = 3.14f / fai_count;			// 绕着z轴旋转一圈

	// vertex buffer datas below
	vcount = theta_count * fai_count;
	vbuffer = new VertexStruct[vcount];
	for( int j = 0; j < fai_count; ++j )			// 绕着z轴旋转一圈
	{
		float fai = j * fai_step;
		float y = cos(fai) * radius;
		float xz_radius = sin(fai) * radius;

		for( int i = 0; i < theta_count; ++i )	// 绕着y轴旋转一圈
		{
			float theta = i * theta_step;
			vbuffer[j * theta_count + i]._x = cos(theta) * xz_radius;
			vbuffer[j * theta_count + i]._y = y;
			vbuffer[j * theta_count + i]._z = sin(theta) * xz_radius;

			vbuffer[j * theta_count + i]._nx = vbuffer[j * theta_count + i]._x;
			vbuffer[j * theta_count + i]._ny = vbuffer[j * theta_count + i]._y;
			vbuffer[j * theta_count + i]._nz = vbuffer[j * theta_count + i]._z;
		}
	}

	// index buffer datas below
	icount = 3 * (fai_count-1) * (theta_count) * 2;
	(ibuffer) = new WORD[icount];
	int idx = 0;
	for( int j = 0; j < fai_count-1; ++j )
	{
		for( int i = 0; i < theta_count-1; ++i )
		{
			ibuffer[idx++] = j * theta_count + i;
			ibuffer[idx++] = (j+1) * theta_count + i + 1;
			ibuffer[idx++] = j * theta_count + i + 1;
		}
		ibuffer[idx++] = j * theta_count + theta_count - 1;
		ibuffer[idx++] = (j+1) * theta_count;
		ibuffer[idx++] = j * theta_count;
	}
	for( int j = 0; j < fai_count-1; ++j )
	{
		for( int i = 0; i < theta_count-1; ++i )
		{
			ibuffer[idx++] = j * theta_count + i;
			ibuffer[idx++] = (j+1) * theta_count + i;
			ibuffer[idx++] = (j+1) * theta_count + i + 1;
		}
		ibuffer[idx++] = j * theta_count + theta_count-1;
		ibuffer[idx++] = (j+1) * theta_count + theta_count-1;
		ibuffer[idx++] = (j+1) * theta_count;
	}
}

template <typename VertexStruct>
void PaintMesh( VertexStruct*& vbuffer, const int& vcount )
{
	srand((unsigned)time(0));
	for( int i = 0; i < vcount; ++i )
	{
		vbuffer[i]._color = (( DWORD(rand()) ) << 8) + (( DWORD(rand()) ) << 16) + 0xff;
	}
}

template <typename VertexStruct>
void GenerateTerrainMeshByFunc( VertexStruct*& vbuffer, int& vcount, WORD*& ibuffer, int& icount, float (*pf)(float, float) )
{
	int x_count = 2;
	int y_count = 2;
	float x_range = 3.f;
	float y_range = 3.f;

	vcount = ( x_count + 1 ) * ( y_count + 1 );
	vbuffer = new VertexStruct[vcount];

	for( int x = 0; x <= x_count; ++x )
	{
		for( int y = 0; y <= y_count; ++y )
		{
			float x_real = (((float)x / x_count) - 0.5f ) * x_range;
			float y_real = (((float)y / y_count) - 0.5f ) * y_range;
			vbuffer[x * (y_count + 1) + y]._x = x_real;
			vbuffer[x * (y_count + 1) + y]._z = y_real;
			vbuffer[x * (y_count + 1) + y]._y = (*pf)(x_real, y_real);
		}
	}

	icount = x_count * y_count * 3 * 2;
	int idx = 0;
	ibuffer = new WORD[icount];
	for( int x = 0; x < x_count; ++x )
	{
		for( int y = 0; y < y_count; ++y )
		{
			ibuffer[idx++] = x * (y_count+1) + y;
			ibuffer[idx++] = (x+1) * (y_count+1) + (y+1);
			ibuffer[idx++] = x * (y_count+1) + (y+1);

			ibuffer[idx++] = x * (y_count+1) + y;
			ibuffer[idx++] = (x+1) * (y_count+1) + y;
			ibuffer[idx++] = (x+1) * (y_count+1) + (y+1);
		}
	}
}

#endif