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
	mPosition = Position;
	mMesh[0].Load(TEXT("item.png"));
}
void CItem::Animate()
{

}
CItem::CItem()
{

}

CItem::~CItem()
{
}