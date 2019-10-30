#include "GameFramework.h"
#include "Planet.h"
#include "CameraManager.h"

DEFINITION_SINGLE(GameFramework)

LPDIRECT3DDEVICE9 GameFramework::m_pD3DDevice = NULL;

GameFramework::GameFramework()
{
}


GameFramework::~GameFramework()
{
}

bool GameFramework::Init(HINSTANCE hInst, int _nCmdShow)
{
	m_hInst = hInst;
	m_pD3D = NULL;

	CoreRegisterClass();

	//â �����
	Create(_nCmdShow);

	/*if (!SUCCEEDED(GET_SINGLE(Triangle)->Init(m_pD3DDevice)))
	{
		return false;
	}*/

	return true;
}

void GameFramework::InitMatrix()
{
	/// ���� ��� ����
	D3DXMatrixIdentity(&m_matWorld);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	/// �� ����� ����
	D3DXVECTOR3 vEyePt(0.0f, 50.0f, (float)-30.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_matView, &vEyePt, &vLookatPt, &vUpVec);
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &m_matView);

	/// ���� �������� ���
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f);
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);

	/// �������� �ø��� �������� ���
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4, 1.0f, 1.0f, 200.0f);

	/// ī�޶� �ʱ�ȭ
	GET_SINGLE(CameraManager)->SetView(&vEyePt, &vLookatPt, &vUpVec);

}

int GameFramework::Run()
{
	MSG msg;

	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			Render();
	}

	Release();

	return (int)msg.wParam;
}


void GameFramework::Input()
{
}

int GameFramework::Update()
{
	return 0;
}

void GameFramework::Render()
{
	if (m_pD3DDevice == NULL)
		return;

	// 
	m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	//Begine paint
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		//print �ڵ� ��ġ
		//GET_SINGLE(Triangle)->Render(m_pD3DDevice);
		m_pD3DDevice->EndScene();
	}

	//����-�ĸ� ������ �ٲٴ±�� (�����)
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void GameFramework::Release()
{
	//GET_SINGLE(Triangle)->Release();
	SAFE_RELEASE(m_pD3DDevice);
	SAFE_RELEASE(m_pD3D);
}

ATOM GameFramework::CoreRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = GameFramework::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"SolarSystem";
	wcex.hIconSm = LoadIcon(wcex.hInstance, NULL);

	return RegisterClassExW(&wcex);
}

BOOL GameFramework::Create(int _nCmdShow)
{
	MSG Message;

	m_hWnd = CreateWindow("SolarSystem", "SolarSystem", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, m_hInst, NULL);

	if (!m_hWnd) //������ ���� �ڵ� ���п���(null �� ���)
	{
		return FALSE;
	}

	if (SUCCEEDED(InitD3D(m_hWnd)))
	{
		ShowWindow(m_hWnd, _nCmdShow);
		UpdateWindow(m_hWnd);
	}

	return TRUE;
}

/**-----------------------------------------------------------------------------
 * Direct3D �ʱ�ȭ
 *------------------------------------------------------------------------------
 */
HRESULT GameFramework::InitD3D(HWND hWnd)
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
	{
		return E_FAIL;
	}


	return S_OK;
}

HRESULT GameFramework::InitGeometry()
{
	InitMatrix();

	// ������ ���콺 ��ġ ����
	POINT	pt;
	GetCursorPos(&pt);
	m_dwMouseX = pt.x;
	m_dwMouseY = pt.y;
	return S_OK;
}

LRESULT GameFramework::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
