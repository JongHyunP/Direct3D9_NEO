#include "Triangle.h"

DEFINITION_SINGLE(Triangle)

Triangle::Triangle()
{
}


Triangle::~Triangle()
{
}

HRESULT Triangle::Init(LPDIRECT3DDEVICE9 device)
{
	m_pD3DDeviceTriangle = device;

	CUSTOMVECTEX vertices[] =
	{
		{ 150.0f , 50.0f , 0.5f , 1.0f , 0xffff0000} ,
		{ 250.0f , 250.0f , 0.5f , 1.0f , 0xff00ff00 } ,
		{ 50.0f , 250.0f , 0.5f , 1.0f , 0xff00ffff },
	};
	
	if (FAILED(m_pD3DDeviceTriangle->CreateVertexBuffer(3 * sizeof(CUSTOMVECTEX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVB, NULL)))
		return E_FAIL;

	void* pVertices; //OFFSETLOCK
	if (FAILED(m_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
		return E_FAIL;

	memcpy(pVertices, vertices, sizeof(vertices));

	m_pVB->Unlock();
	
	return S_OK;
}

void Triangle::Render(LPDIRECT3DDEVICE9 device)
{
	m_pD3DDeviceTriangle->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVECTEX));
	m_pD3DDeviceTriangle->SetFVF(D3DFVF_CUSTOMVERTEX);
	m_pD3DDeviceTriangle->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}

void Triangle::Release()
{
	SAFE_RELEASE(m_pVB);
}
