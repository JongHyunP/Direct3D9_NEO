#include "GameFramework.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR		IpCmdLine,
	_In_ int		nCmdShow)
{

	if (!GET_SINGLE(GameFramework)->Init(hInstance, nCmdShow))
	{
		DESTROY_SINGLE(GameFramework);
		return 0;
	}

	int iRev = GET_SINGLE(GameFramework)->Run();

	DESTROY_SINGLE(GameFramework);

	return iRev;
}