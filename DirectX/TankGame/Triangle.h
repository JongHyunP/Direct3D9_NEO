#pragma once
#include "../Common/value.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

struct CUSTOMVECTEX
{
	float m_PosX;
	float m_PosY;
	float m_PosZ;
	float m_PosRHW;
	DWORD m_Color;
};

class Triangle
{
	DECLARE_SINGLE(Triangle)

private:
	LPDIRECT3DVERTEXBUFFER9		m_pVB = NULL;
	LPDIRECT3DDEVICE9			m_pD3DDeviceTriangle = NULL;
public:
	HRESULT Init(LPDIRECT3DDEVICE9 device);
	void Render(LPDIRECT3DDEVICE9 device);
	void Release();
};

