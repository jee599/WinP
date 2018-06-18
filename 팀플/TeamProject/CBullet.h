#pragma once
#include "CGameObject.h"

class CBullet : public CGameObject
{
	int mDamage;
	bool mRight;
	int mSpeed;
public:
	CBullet();
	CBullet(POINT, TYPE, int, int ,bool);
	~CBullet();

	bool Animate();
	void Render(HDC);
	bool CollCheck(RECT);
	int GetDamage();
};

