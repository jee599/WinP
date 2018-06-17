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
	mObjectSize = 20;
	mPosition = Position;
	mDir = 0;
	mMesh[0].Load(TEXT("meta.png"));
}
void CItem::Animate()
{
	switch (mDir)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	}
}
void CItem::Render(HDC Buffer)
{
	mMesh[0].Draw(Buffer, mPosition.x, mPosition.y, mObjectSize, mObjectSize);
}
CItem::CItem()
{

}

CItem::~CItem()
{
}