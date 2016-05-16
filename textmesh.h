#ifndef __TEXT_H__
#define __TEXT_H__

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

#include <string>

#include "render_object_base.h"

class MeshText
{
public:
	MeshText();
	virtual ~MeshText();

	void Config();
	void PreRender( LPDIRECT3DDEVICE9 device );
	void Render( LPDIRECT3DDEVICE9 device );

private:
	std::string m_str;
};
#endif