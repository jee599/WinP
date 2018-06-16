#pragma once
#include"Header.h"

class CGameObject
{
protected:
	CImage mMesh[3];
	POINT mPosition;
	int mObjectSize;
public:
	CGameObject();
	~CGameObject();
public:
	virtual void Render(HDC);
	RECT GetRect() {
		return { mPosition.x - mObjectSize/2 + 2, mPosition.y - mObjectSize/2 + 2,mPosition.x + mObjectSize/2 - 2,mPosition.y + mObjectSize/2 - 2};
	}

	POINT GetPosition();
};

