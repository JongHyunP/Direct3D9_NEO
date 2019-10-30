
#include "..\TankGame\CCore.h"
#include "CCore.h"

DEFINITION_SINGLE(CCore)
bool CCore::m_bLoop = true;

CCore::CCore()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(); // �ּ���ȣ �˻�()
}


CCore::~CCore()
{
	SAFE_RELEASE(m_pd3dDevice);
	SAFE_RELEASE(m_pD3D);
}


bool CCore::Init(HINSTANCE hInst, int nCmdShow)
{
	m_hInst = hInst;
	m_iCmdshow = nCmdShow;
	m_pd3dDevice = NULL;
	m_pD3D = NULL;

	CoreRegisterClass();

	//â �����
	Create();

	return true;
}


int CCore::Run()
{
	MSG msg;

	while (m_bLoop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//������ ����Ÿ���� ���
		else
		{
			Render();
		}
	}

	return (int)msg.wParam;
}


HRESULT CCore::InitD3D(HWND hWnd)
{
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp; // ��� �Ķ����

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE; // â���
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; // ��� D3DSWAPEFFECT_DISCARD , ������ ����
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // D3DFMT_UNKNOWN ������ �ػ� , 32��Ʈ, ���ȭ�� �״�� ���ڴ� �ǹ�.

	//D3DADAPTER_DEFAULT ���, D3DDEVTYPE_HAL ���, �������ڵ�, D3DCREATE_SOFTWARE_VERTEXPROCESSING �����Ŷ�, ���������� -> &g_pD3DDevice ���� ä���
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pd3dDevice)))
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CCore::InitGeometry()
{

	return S_OK;
}

void CCore::SetupCamera()
{
	//D3DXMATRIXA16 matWorld;
	//D3DXMatrixIdentity(&matWorld);
	//m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

	//D3DXVECTOR3 vEyePt(0.0f, 100.0f, -50.f);
	//D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	//D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	//D3DXMATRIXA16 matView;
	//D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	//m_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	//D3DXMATRIXA16 matProj;
	//D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f);
	//m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	//ZCamera::GetInstance()->SetView(&vEyePt, &vLookatPt, &vUpVec);
}

void CCore::Render()
{
	if (m_pd3dDevice == NULL)
		return;

	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	if (SUCCEEDED(m_pd3dDevice->BeginScene()))
	{


		m_pd3dDevice->EndScene();
	}

	m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}


ATOM CCore::CoreRegisterClass()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = CCore::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "DirectX";

	return RegisterClassEx(&wcex);
}

BOOL CCore::Create()
{
	m_hWnd = CreateWindow("DirectX", "DirectX", WS_OVERLAPPEDWINDOW,
		100, 100, 300, 300, NULL, NULL, m_hInst, NULL);

	if (!m_hWnd) //������ ���� �ڵ� ���п���(null �� ���)
	{
		return FALSE;
	}

	if (FAILED(InitD3D(m_hWnd)))
		return -1;

	if (FAILED(InitGeometry()))
		return -1;

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return TRUE;
}

LRESULT CCore::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostMessage(hWnd, WM_DESTROY, 0, 0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}