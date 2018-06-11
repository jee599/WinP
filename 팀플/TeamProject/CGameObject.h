#pragma once
#include"Header.h"

class CGameObject
{
protected:
	CImage mMesh[3];
	POINT mPosition;
public:
	CGameObject();
	~CGameObject();
public:
	virtual void Render(HDC);
};

