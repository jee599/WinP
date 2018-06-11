#pragma once
#include "CGameObject.h"

class CEnemy : public CGameObject
{
public:
	CEnemy();
	~CEnemy();

	void Render();
};

