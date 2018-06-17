#pragma once
#include "CGameObject.h"

class CBullet : public CGameObject
{
	int mDamage ;
public:
	CBullet();
	CBullet(POINT, TYPE);
	~CBullet();

	bool Animate();
	void Render(HDC);
	bool CollCheck(RECT);
	int GetDamage();
};

