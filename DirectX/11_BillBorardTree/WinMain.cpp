#include "CCore.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR		IpCmdLine,
	_In_ int		nCmdShow)
{

	if (!GET_SINGLE(CCore)->Init(hInstance, nCmdShow))
	{
		DESTROY_SINGLE(CCore);
		return 0;
	}

	int iRev = GET_SINGLE(CCore)->Run();

	DESTROY_SINGLE(CCore);

	return iRev;
}