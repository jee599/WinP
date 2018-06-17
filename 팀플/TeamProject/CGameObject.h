#pragma once
#include"Header.h"

class CGameObject
{
protected:
	CImage mMesh[10];
	POINT mPosition;
	int mObjectSize;
	int mMeshCount;
public:
	CGameObject();
	~CGameObject();
public:
	virtual void Render(HDC);
	virtual void Collision() {};
	RECT GetRect() {
		return { mPosition.x - mObjectSize/2 + 2, mPosition.y - mObjectSize/2 + 2,mPosition.x + mObjectSize/2 - 2,mPosition.y + mObjectSize/2 - 2};
	}

	POINT GetPosition();
};

class CItem : public CGameObject
{
	int mDir;
	int mSpeed;
public:
	CItem();
	~CItem();
	CItem(POINT);

public:
	void Animate();
	void Render(HDC);
};

