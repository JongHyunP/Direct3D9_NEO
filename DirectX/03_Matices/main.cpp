#include <d3dx9.h>
#include <mmsystem.h>
#include "SAFE_DELETE.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
char g_szClassName[256] = "Hello World!!";

LPDIRECT3D9					g_pD3D = NULL;
LPDIRECT3DDEVICE9			g_pD3DDevice = NULL;
LPDIRECT3DVERTEXBUFFER9		g_pVB = NULL;

float			g_fX=0.0f;
float			g_fY=3.0f;
float			g_fZ=-5.0f;

struct CUSTOMVECTEX
{
	float x, y, z;
	DWORD color;
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

HRESULT InitD3D(HWND hWnd)
{
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
	{
		return E_FAIL;
	}

	//중요 -> 
	//D3DRS_CULLMODE =
	//D3DCULL_NONE , 기본은 CCW
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//자체 발광하겠다.
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


	return S_OK;
}

HRESULT InitGeometry()
{
	CUSTOMVECTEX vertices[] =
	{
		{ -1.0f , -1.0f , 0.0f , 0xffff0000 } ,
		{ 1.0f , -1.0f , 0.0f , 0xff0000ff } ,
		{ 0.0f , 1.0f ,  0.0f , 0xffffffff }
	};

	if (FAILED(g_pD3DDevice->CreateVertexBuffer(3 * sizeof(CUSTOMVECTEX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &g_pVB, NULL)))
		return E_FAIL;

	void* pVertices;
	if (FAILED(g_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
		return E_FAIL;

	memcpy(pVertices, vertices, sizeof(vertices));
	g_pVB->Unlock();

	return S_OK;
}

void CleanUp()
{
	SAFE_RELEASE(g_pVB);
	SAFE_RELEASE(g_pD3DDevice);
	SAFE_RELEASE(g_pD3D);
}

void SetupMareices()
{
	D3DXMATRIXA16 matWorld;
	UINT iTime = timeGetTime() % 1000;
	FLOAT fAngle = iTime * (2.0f * D3DX_PI) / 1000.0f;
	//D3DXMatrixIdentity(&matWorld2);
	//D3DXMatrixTranslation(&matWorld , )
	//D3DXMatrixScaling()
	D3DXMatrixRotationY(&matWorld, fAngle); // Y축 기준으로 앵글 회전
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld); // 월드메트리스 셋팅



	//카메라 클래스 하나만들기
	//WASD 카메라
	//상하좌우 앞, 뒤

	//뷰 메트릭스, 카메라
	//내 눈이 어디있는지
	D3DXVECTOR3 vEyept(g_fX, g_fY, -g_fZ);
	//어디를 보고있는지
	D3DXVECTOR3 vLootatPt(g_fX, g_fY-3.0f, g_fZ+5.0f);
	//회전이 되고있는지 // 기본 0,1,0 거의 고정
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);

	//메트릭스 선언
	D3DXMATRIXA16 matView;
	//왼손좌표계로 채워준다
	D3DXMatrixLookAtLH(&matView, &vEyept, &vLootatPt, &vUpVec);

	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	//원근 투영해보겠다(일반적인 3D 월드)
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
										//보는 시야각/

	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void Render()
{
	if (g_pD3DDevice == NULL)
		return;

	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		SetupMareices();

		g_pD3DDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVECTEX));
		g_pD3DDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 1);

		//g_pMesh->DrawSubset(0);

		g_pD3DDevice->EndScene();
	}

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = g_szClassName;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(g_szClassName, g_szClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);


	if (SUCCEEDED(InitD3D(hWnd)))
	{
		if (SUCCEEDED(InitGeometry()))
		{
			ShowWindow(hWnd, nCmdShow);
			UpdateWindow(hWnd);

			ZeroMemory(&Message, sizeof(Message));
			while (Message.message != WM_QUIT)
			{
				if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}
				else
					Render();
			}
		}

	}

	CleanUp();

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	SYSTEMTIME st;

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 100, NULL);
		return 0;
	case WM_TIMER: //1초마다 한번씩 실행됨.
		GetLocalTime(&st);

		return 0;
	case WM_LBUTTONUP:
	{
		D3DXVECTOR3 posPlayer = { 10 , 10 , 10 };
		D3DXVECTOR3 posEnemy = { 20 , 20 , 10 };
		D3DXVECTOR3 dir = posEnemy - posPlayer;
		D3DXVec3Normalize(&dir, &dir);

		MessageBox(hWnd, "", "", MB_OK);
	}
	return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			g_fX -= 1.0f;
			break;
		case VK_RIGHT:
			g_fX += 1.0f;
			break;
		case VK_UP:
			g_fY -= 1.0f;
			break;
		case VK_DOWN:
			g_fY += 1.0f;
			break;
		case 0x5A:
			g_fZ += 1.0f;
			break;
		case 0x58:
			g_fZ -= 1.0f;
			break;
		}
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

