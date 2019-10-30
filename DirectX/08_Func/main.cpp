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

	WndClass.cbClsExtra = 0; //통상 0임
	WndClass.cbWndExtra = 0; //통상 0임
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//배경화면 브러쉬,미리쓸수있는 브러쉬들 (F12 참조 올라가서 색볼수있음)
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	//커서 변경
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//아이콘 변경
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	//프로시저의 함수 포인터
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	//창크기

	RegisterClass(&WndClass); //스트럭트 로 전달, 위에 설정한 옵션으로 커스텀 클래스를 만든다.

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	//메인
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
	//월드 변환

	//카메라 변환

	//투영변환 (프로젝션)

}

struct MatrixF
{
	float x1,x2,x3,x4; //float x1,x2,x3,x4;
	float y1,y2,y3,y4; //float y1,y2,y3,y4;
	float z1,z2,z3,z4; //float z1,z2,z3,z4;
	float w1,w2,w3,w4; //float w1,w2,w3,w4;

};

//메트릭스 * 메트릭스

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

//메트릭스 * 벡터


//단위 행렬 함수
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
//이동 행렬

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


//cosf(s) = x/r  ->> cosf(s)*r = _x(기준점이동) + x;
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) // W파라미터 L파라미터는 메시지 이외의 부가정보들이 필요할때
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage) //주로 메시지를 재정의 하는데 코딩을 함.
	{
	case WM_DESTROY: //WM = 윈도우메시지 줄임말
		PostQuitMessage(0); //종료메시지
		return 0;//처리햇다.
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

	
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));

}