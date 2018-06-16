#include "CGameObject.h"

CGameObject::CGameObject()
{
}

CGameObject::~CGameObject()
{
}

RECT CGameObject::GetRect()
{
	return { mPosition.x - mObjectSize, mPosition.y - mObjectSize,mPosition.x + mObjectSize ,mPosition.y + mObjectSize };
}
POINT CGameObject::GetPosition()
{
	return mPosition;
}
void CGameObject::Render(HDC) {}