#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "SAFE_DELETE.h"

class Matrix
{
protected:
	friend class MatrixManager;

private:
	D3DXMATRIXA16	m_matTrans;
	D3DXMATRIXA16	m_matRotation;

protected:
	Matrix();
	virtual ~Matrix() = 0;

public:
	virtual HRESULT InitVB() = 0;
	virtual HRESULT InitIB() = 0;
	virtual void InitAnimation() = 0;
	virtual VOID Animate() = 0;
	virtual VOID Cleanup() = 0;
	virtual VOID Render() = 0;
};

