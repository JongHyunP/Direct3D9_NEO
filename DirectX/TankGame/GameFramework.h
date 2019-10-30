#pragma once
#include "../Common/value.h"

class GameFramework
{
	DECLARE_SINGLE(GameFramework)

private:
	HINSTANCE					m_hInst;
	HWND						m_hWnd;
	LPDIRECT3D9					m_pD3D; // LP 롱 포인터 ,  DIRECT3D9	의 포인터 객체
	static LPDIRECT3DDEVICE9	m_pD3DDevice;
	DWORD						m_dwMouseX;
	DWORD						m_dwMouseY;

private:
	D3DXMATRIXA16			m_matAni;
	D3DXMATRIXA16			m_matWorld;
	D3DXMATRIXA16			m_matView;
	D3DXMATRIXA16			m_matProj;

public:
	bool Init(HINSTANCE hInst, int _nCmdShow);
	void InitMatrix();
	int Run();

public:
	HWND GetWindowHandle() const
	{
		return m_hWnd;
	}
private:
	void Input();
	int Update();
	static void Render();
	void Release();
private:
	ATOM CoreRegisterClass();
	BOOL Create(int _nCmdShow);
	HRESULT InitD3D(HWND hWnd);
	HRESULT InitGeometry();
public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

};

