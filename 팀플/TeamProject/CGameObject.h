#pragma once
#include"Header.h"

class CGameObject
{
protected:
	CImage mMesh[15];
	POINT mPosition;
	int mObjectSize;
	int mMeshCount;
public:
	CGameObject();
	~CGameObject();
public:
	virtual void Render(HDC);
	RECT GetRect() {
		return { mPosition.x - mObjectSize/2 , mPosition.y - mObjectSize/2 ,mPosition.x + mObjectSize/2 ,mPosition.y + mObjectSize/2 };
	}

	POINT GetPosition();
};

class CItem : public CGameObject
{
	int mDir;
	int mType;
	int mSpeed;
public:
	CItem();
	~CItem();
	CItem(POINT);

public:

	int GetType() { return mType; }
	void Animate();
	void Render(HDC);
};

