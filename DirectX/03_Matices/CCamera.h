#pragma once
#include <d3dx9.h>
#include <mmsystem.h>

class CCamera
{
private:
	float m_fX;
	float m_fY;
	float m_fZ;


public:
	CCamera();
	~CCamera();

public:
	int Init();
	int Move();
};

