#include <d3d9.h>
#include "SAFE_DELETE.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
char g_szClassName[256] = "Hello World!!";

LPDIRECT3D9			g_pD3D = NULL; // LP 롱 포인터 ,  DIRECT3D9	의 포인터 객체
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL; //

HRESULT InitD3D(HWND hWnd) // HRESULT : 윈도우 결과값 처리하는데 쓰임
{
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION); //초기화

	if (g_pD3D == NULL)
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp; // 출력 파라메터

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE; // 창모드
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; // 통상 D3DSWAPEFFECT_DISCARD , 빽버퍼 느낌
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // D3DFMT_UNKNOWN 윈도우 해상도 , 32비트, 배경화면 그대로 쓰겠다 의미.

	//D3DADAPTER_DEFAULT 통상, D3DDEVTYPE_HAL 통상, 윈도우핸들, D3DCREATE_SOFTWARE_VERTEXPROCESSING 옛날거라, 더블포인터 -> &g_pD3DDevice 값을 채운다
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CleanUp()
{
	//역순 지우기
	SAFE_RELEASE(g_pD3DDevice);
	SAFE_RELEASE(g_pD3D);
}

void Render()
{
	if (g_pD3DDevice == NULL)
		return;

	// 
	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	//Begine paint
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//print 코드 위치

		g_pD3DDevice->EndScene();
	}

	//전면-후면 포인터 바꾸는기능 (백버퍼)
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
		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);

		while (GetMessage(&Message, NULL, 0, 0))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}

	CleanUp();

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_PAINT:
		Render();
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

