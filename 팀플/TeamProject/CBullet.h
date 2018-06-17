#pragma once
#include "CGameObject.h"

class CBullet : public CGameObject
{
public:
	CBullet();
	CBullet(POINT, TYPE);
	~CBullet();

	bool Animate();
	void Render(HDC);
	bool CollCheck(RECT);

};

