#include <d3d9.h>
#include <d3dx9.h>
#include <mmsystem.h>
#include "SAFE_DELETE.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
char g_szClassName[256] = "Hello World!!";

LPDIRECT3D9					g_pD3D = NULL;
LPDIRECT3DDEVICE9			g_pD3DDevice = NULL;
LPD3DXMESH					g_pMesh = NULL;
D3DMATERIAL9*				g_pMeshMaterials = NULL;
LPDIRECT3DTEXTURE9*			g_pMeshTextures = NULL;
DWORD						g_dwNumMaterials = 0;

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
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;


	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
	{
		return E_FAIL;
	}

	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);

	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return S_OK;
}


HRESULT InitGeometry()
{
	LPD3DXBUFFER pD3dXMtrlBuffer;

	//x는 마이크로 소프트 기준, 실제 게임에선 안씀, 일반적으론 max에서 플러그인, 파싱
	if (FAILED(D3DXLoadMeshFromXA("Tiger.x", D3DXMESH_SYSTEMMEM, g_pD3DDevice, NULL, &pD3dXMtrlBuffer,
		NULL, &g_dwNumMaterials, &g_pMesh))) //g_dwNumMaterials 머테리얼 갯수는 규정에 따르면됨.
	{
		MessageBox(NULL,"Could not find tiger.x", "ERROR", MB_OK);
	}

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3dXMtrlBuffer->GetBufferPointer();
	g_pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];
	g_pMeshTextures = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];

	//갯수만큼 돌린다.
	for (int i = 0; i < g_dwNumMaterials; i++)
	{
		g_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		g_pMeshMaterials[i].Ambient = g_pMeshMaterials[i].Diffuse;
		g_pMeshTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL && strlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, d3dxMaterials[i].pTextureFilename, &g_pMeshTextures[i])))
			{
				MessageBox(NULL, "Could not find texture map", "Textrue", MB_OK);
				return E_FAIL;
			}
		}
	}

	pD3dXMtrlBuffer->Release();

	return S_OK;

}


void CleanUp()
{
	SAFE_DELETE_ARRAY(g_pMeshMaterials);
	if (g_pMeshTextures)
	{
		for (int i = 0; i < g_dwNumMaterials; i++)
		{
			SAFE_RELEASE(g_pMeshTextures[i]);
		}
	}

	SAFE_RELEASE(g_pMesh);
	SAFE_RELEASE(g_pD3DDevice);
	SAFE_RELEASE(g_pD3D);
}

void SetupMareices()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationY(&matWorld, timeGetTime() / 1000.0f);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXVECTOR3 vEyept(0.0f, 3.0f, -5.0f);
	D3DXVECTOR3 vLootatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyept, &vLootatPt, &vUpVec);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void Render()
{
	if (g_pD3DDevice == NULL)
		return;

	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		SetupMareices();

		for (int i = 0; i < g_dwNumMaterials; i++)
		{
			g_pD3DDevice->SetMaterial(&g_pMeshMaterials[i]);
			g_pD3DDevice->SetTexture(0, g_pMeshTextures[i]);

			//한뭉탱이를 출력 메시함수로 자주씀.
			g_pMesh->DrawSubset(i);
		}

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
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

