#include "model_objects/model_vertex.h"

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

DWORD ModelVertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1;
DWORD MtlTexVertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1;
