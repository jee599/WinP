#pragma once
#include "CGameObject.h"

class CEnemy : public CGameObject
{
	int mLife;
public:
	CEnemy();
	~CEnemy();

	void Render(HDC);
	void CollCheck();
};

