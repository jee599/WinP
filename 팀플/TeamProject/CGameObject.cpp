#include "CGameObject.h"

CGameObject::CGameObject()
{
}

CGameObject::~CGameObject()
{
}

POINT CGameObject::GetPosition()
{
	return mPosition;
}
void CGameObject::Render(HDC) {}

CItem::CItem(POINT Position)
{
	mSpeed = 1;
	mObjectSize = 20;
	mPosition = Position;
	mDir = 0;
	mType = rand() % 5;
	mMesh[0].Load(TEXT("meta.png"));
	mMesh[1].Load(TEXT("item1.png"));
	mMesh[2].Load(TEXT("item2.png"));
	mMesh[3].Load(TEXT("item3.png"));
	mMesh[4].Load(TEXT("item4.png"));
}
void CItem::Animate()
{
	switch (mDir)
	{
	case 0:
		mPosition.x += mSpeed;
		mPosition.y += mSpeed;
		if (mPosition.x > 950 || mPosition.y > 750)
			mDir = 3;
		break;
	case 1:
		mPosition.x += mSpeed;
		mPosition.y -= mSpeed;
		if (mPosition.x > 950 || mPosition.y < 50)
			mDir = 2;
		break;
	case 2:
		mPosition.x -= mSpeed;
		mPosition.y += mSpeed;
		if (mPosition.x < 50 || mPosition.y > 750)
			mDir = 0;
		break;
	case 3:
		mPosition.x -= mSpeed;
		mPosition.y -= mSpeed;
		if (mPosition.x < 50 || mPosition.y < 50)
			mDir = 1;
		break;
	}
}
void CItem::Render(HDC Buffer)
{
	mMesh[mType].Draw(Buffer, mPosition.x, mPosition.y, mObjectSize*2, mObjectSize*2);
}
CItem::CItem()
{

}

CItem::~CItem()
{
}