#pragma once
#include "CGameObject.h"

class CBullet : public CGameObject
{
public:
	CBullet();
	CBullet(POINT);
	~CBullet();

	bool Animate();
	void Render(HDC);
	bool CollCheck(RECT);

};

