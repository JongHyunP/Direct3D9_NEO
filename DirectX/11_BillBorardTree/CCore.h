#pragma once
#include "../Common/value.h"

#define MAX_LOADSTRING 100

class CCore
{
	DECLARE_SINGLE(CCore)

private:
	static	bool m_bLoop;

private:
	HINSTANCE					m_hInst;
	HWND						m_hWnd;
	LPDIRECT3D9					m_pD3D;
	LPDIRECT3DDEVICE9			m_pd3dDevice;
	int							m_iCmdshow;

public:
	bool Init(HINSTANCE hInst, int nCmdShow);
	int Run();

private:
	HRESULT InitD3D(HWND hWnd);
	HRESULT InitGeometry();
	void Render();
	void SetupCamera();

public:

private:
	ATOM CoreRegisterClass();
	BOOL Create();

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

