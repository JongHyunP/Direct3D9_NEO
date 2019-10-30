#include <Windows.h>
#include <math.h>
#include <d3dx9.h>
#include <mmsystem.h>
#include "SAFE_DELETE.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("First");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0; //��� 0��
	WndClass.cbWndExtra = 0; //��� 0��
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//���ȭ�� �귯��,�̸������ִ� �귯���� (F12 ���� �ö󰡼� ����������)
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	//Ŀ�� ����
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//������ ����
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	//���ν����� �Լ� ������
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	//âũ��

	RegisterClass(&WndClass); //��Ʈ��Ʈ �� ����, ���� ������ �ɼ����� Ŀ���� Ŭ������ �����.

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	//����
	while (GetMessage(&Message, NULL, 0, 0))
	{

		TranslateMessage(&Message);

		DispatchMessage(&Message);

	}

	return (int)Message.wParam;
}
//void DrawCircle(HDC hdc, int x, int y, int xR, int yR)

#define PI 3.141592

float DegreeToRadian(float degree)
{
	return (PI / 180) * degree;
}

struct Vector
{
	float x, y, z, w;
};

struct Camera
{
	Vector vec_Camera;
};

void DrawTriangle(HDC hdc, MatrixF* tri)
{
	MoveToEx(hdc, 150, 50, NULL);
	LineTo(hdc, 250, 250);
	MoveToEx(hdc, 250, 250, NULL);
	LineTo(hdc, 50, 250);
	MoveToEx(hdc, 50, 250, NULL);
	LineTo(hdc, 150, 50);
}

void InitGeo()
{
	//���� ��ȯ

	//ī�޶� ��ȯ

	//������ȯ (��������)

}

struct MatrixF
{
	float x1,x2,x3,x4; //float x1,x2,x3,x4;
	float y1,y2,y3,y4; //float y1,y2,y3,y4;
	float z1,z2,z3,z4; //float z1,z2,z3,z4;
	float w1,w2,w3,w4; //float w1,w2,w3,w4;

};

//��Ʈ���� * ��Ʈ����

MatrixF MatrixMultiply(MatrixF* matrix, MatrixF* matrix2)
{
	MatrixF tempMatrix;

	tempMatrix.x1 = (matrix->x1 * matrix2->x1) + (matrix->x2 * matrix2->y1) + (matrix->x3 * matrix2->z1) + (matrix->x4 * matrix2->w1);
	tempMatrix.x2 = (matrix->x1 * matrix2->x2) + (matrix->x2 * matrix2->y2) + (matrix->x3 * matrix2->z2) + (matrix->x4 * matrix2->w2);
	tempMatrix.x3 = (matrix->x1 * matrix2->x3) + (matrix->x2 * matrix2->y3) + (matrix->x3 * matrix2->z3) + (matrix->x4 * matrix2->w3);
	tempMatrix.x4 = (matrix->x1 * matrix2->x4) + (matrix->x2 * matrix2->y4) + (matrix->x3 * matrix2->z4) + (matrix->x4 * matrix2->w4);

	tempMatrix.y1 = (matrix->y1 * matrix2->x1) + (matrix->y2 * matrix2->y1) + (matrix->y3 * matrix2->z1) + (matrix->y4 * matrix2->w1);
	tempMatrix.y2 = (matrix->y1 * matrix2->x2) + (matrix->y2 * matrix2->y2) + (matrix->y3 * matrix2->z2) + (matrix->y4 * matrix2->w2);
	tempMatrix.y3 = (matrix->y1 * matrix2->x3) + (matrix->y2 * matrix2->y3) + (matrix->y3 * matrix2->z3) + (matrix->y4 * matrix2->w3);
	tempMatrix.y4 = (matrix->y1 * matrix2->x4) + (matrix->y2 * matrix2->y4) + (matrix->y3 * matrix2->z4) + (matrix->y4 * matrix2->w4);

	tempMatrix.z1 = (matrix->z1 * matrix2->x1) + (matrix->z2 * matrix2->y1) + (matrix->z3 * matrix2->z1) + (matrix->z4 * matrix2->w1);
	tempMatrix.z2 = (matrix->z1 * matrix2->x2) + (matrix->z2 * matrix2->y2) + (matrix->z3 * matrix2->z2) + (matrix->z4 * matrix2->w2);
	tempMatrix.z3 = (matrix->z1 * matrix2->x3) + (matrix->z2 * matrix2->y3) + (matrix->z3 * matrix2->z3) + (matrix->z4 * matrix2->w3);
	tempMatrix.z4 = (matrix->z1 * matrix2->x4) + (matrix->z2 * matrix2->y4) + (matrix->z3 * matrix2->z4) + (matrix->z4 * matrix2->w4);

	tempMatrix.w1 = (matrix->w1 * matrix2->x1) + (matrix->w2 * matrix2->y1) + (matrix->w3 * matrix2->z1) + (matrix->w4 * matrix2->w1);
	tempMatrix.w2 = (matrix->w1 * matrix2->x2) + (matrix->w2 * matrix2->y2) + (matrix->w3 * matrix2->z2) + (matrix->w4 * matrix2->w2);
	tempMatrix.w3 = (matrix->w1 * matrix2->x3) + (matrix->w2 * matrix2->y3) + (matrix->w3 * matrix2->z3) + (matrix->w4 * matrix2->w3);
	tempMatrix.w4 = (matrix->w1 * matrix2->x4) + (matrix->w2 * matrix2->y4) + (matrix->w3 * matrix2->z4) + (matrix->w4 * matrix2->w4);

	return tempMatrix;
}

//��Ʈ���� * ����


//���� ��� �Լ�
MatrixF  Identity()
{
	MatrixF tempMatrix;

	tempMatrix.x1 = 1.0f;
	tempMatrix.x2 = 0.0f;
	tempMatrix.x3 = 0.0f;
	tempMatrix.x4 = 0.0f;

	tempMatrix.y1 = 0.0f;
	tempMatrix.y2 = 1.0f;
	tempMatrix.y3 = 0.0f;
	tempMatrix.y4 = 0.0f;

	tempMatrix.z1 = 0.0f;
	tempMatrix.z2 = 0.0f;
	tempMatrix.z3 = 1.0f;
	tempMatrix.z4 = 0.0f;

	tempMatrix.w1 = 0.0f;
	tempMatrix.w2 = 0.0f;
	tempMatrix.w3 = 0.0f;
	tempMatrix.w4 = 1.0f;


	return tempMatrix;
}
//�̵� ���

MatrixF Translation(MatrixF* matrix, float x, float y, float z)
{
	MatrixF tempMatrix;

	tempMatrix.x1 = matrix->x1;
	tempMatrix.x2 = matrix->x2;
	tempMatrix.x3 = matrix->x3;
	tempMatrix.x4 = matrix->x4;

	tempMatrix.y1 = matrix->y1;
	tempMatrix.y2 = matrix->y2;
	tempMatrix.y3 = matrix->y3;
	tempMatrix.y4 = matrix->y4;

	tempMatrix.z1 = matrix->z1;
	tempMatrix.z2 = matrix->z2;
	tempMatrix.z3 = matrix->z3;
	tempMatrix.z4 = matrix->z4;

	tempMatrix.w1 = matrix->w1 + x;
	tempMatrix.w2 = matrix->w2 + y;
	tempMatrix.w3 = matrix->w3 + z;
	tempMatrix.w4 = matrix->w4;

	return tempMatrix;
}

MatrixF RotationX(MatrixF* matrix, double rotationnum)
{
	double  seta = rotationnum * (PI / 180);
	MatrixF tempMatrix;

	tempMatrix.x1 = 1.0f;
	tempMatrix.x2 = 0.0f;
	tempMatrix.x3 = 0.0f;
	tempMatrix.x4 = 0.0f;

	tempMatrix.y1 = 0.0f;
	tempMatrix.y2 = cos(seta);
	tempMatrix.y3 = sin(seta);
	tempMatrix.y4 = 0.0f;

	tempMatrix.z1 = 0.0f;
	tempMatrix.z2 = -sin(seta);
	tempMatrix.z3 = cos(seta);
	tempMatrix.z4 = 0.0f;

	tempMatrix.w1 = 0.0f;
	tempMatrix.w2 = 0.0f;
	tempMatrix.w3 = 0.0f;
	tempMatrix.w4 = 1.0f;

	return tempMatrix;
}

MatrixF RotationY(MatrixF* matrix, double rotationnum)
{
	double  seta = rotationnum * (PI / 180);

	MatrixF tempMatrix;

	tempMatrix.x1 = cos(seta);
	tempMatrix.x2 = 0.0f;
	tempMatrix.x3 = -sin(seta);
	tempMatrix.x4 = 0.0f;

	tempMatrix.y1 = 0.0f;
	tempMatrix.y2 = 1.0f;
	tempMatrix.y3 = 0.0f;
	tempMatrix.y4 = 0.0f;

	tempMatrix.z1 = sin(seta);
	tempMatrix.z2 = 0.0f;
	tempMatrix.z3 = cos(seta);
	tempMatrix.z4 = 0.0f;

	tempMatrix.w1 = 0.0f;
	tempMatrix.w2 = 0.0f;
	tempMatrix.w3 = 0.0f;
	tempMatrix.w4 = 1.0f;

	return tempMatrix;
}

MatrixF RotationZ(MatrixF* matrix, double rotationnum)
{
	double  seta = rotationnum * (PI / 180);

	MatrixF tempMatrix;

	tempMatrix.x1 = cosf(seta);
	tempMatrix.x2 = -sin(seta);
	tempMatrix.x3 = 0.0f;
	tempMatrix.x4 = 0.0f;

	tempMatrix.y1 = -sin(seta);
	tempMatrix.y2 = cos(seta);
	tempMatrix.y3 = 0.0f;
	tempMatrix.y4 = 0.0f;

	tempMatrix.z1 = 0.0f;
	tempMatrix.z2 = 0.0f;
	tempMatrix.z3 = 1.0f;
	tempMatrix.z4 = 0.0f;

	tempMatrix.w1 = 0.0f;
	tempMatrix.w2 = 0.0f;
	tempMatrix.w3 = 0.0f;
	tempMatrix.w4 = 1.0f;

	return tempMatrix;
}

MatrixF Scale(MatrixF* matrix, float scale)
{
	MatrixF tempMatrix;

	tempMatrix.x1 = matrix->x1 * scale;
	tempMatrix.x2 = 0.0f;
	tempMatrix.x3 = 0.0f;
	tempMatrix.x4 = 0.0f;

	tempMatrix.y1 = 0.0f;
	tempMatrix.y2 = matrix->y2* scale;
	tempMatrix.y3 = 0.0f;
	tempMatrix.y4 = 0.0f;

	tempMatrix.z1 = 0.0f;
	tempMatrix.z2 = 0.0f;
	tempMatrix.z3 = matrix->z3 * scale;
	tempMatrix.z4 = 0.0f;

	tempMatrix.w1 = 0.0f;
	tempMatrix.w2 = 0.0f;
	tempMatrix.w3 = 0.0f;
	tempMatrix.w4 = 1.0f;

	return tempMatrix;
}


//cosf(s) = x/r  ->> cosf(s)*r = _x(�������̵�) + x;
void DrawCircle(HDC hdc, int x, int y, int xR)
{
	MoveToEx(hdc, x + xR, y, NULL);

	for (int i = 0; i < 360; i++)
	{
		int _x = cosf(DegreeToRadian(i)) * xR + x;
		int _y = sinf(DegreeToRadian(i)) * xR + y;

		//SetPixel(hdc, _x, _y, RGB(255, 0, 0));
		LineTo(hdc, _x, _y);
	}

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) // W�Ķ���� L�Ķ���ʹ� �޽��� �̿��� �ΰ��������� �ʿ��Ҷ�
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage) //�ַ� �޽����� ������ �ϴµ� �ڵ��� ��.
	{
	case WM_DESTROY: //WM = ������޽��� ���Ӹ�
		PostQuitMessage(0); //����޽���
		return 0;//ó���޴�.
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

	
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));

}