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