#pragma once
#include "CGameObject.h"
#include "CEffect.h"

class CEnemy : public CGameObject
{
	int mLife;
	CEffect* mEffect;
	ENEMYSTATE mState;
	int IsEnd = 0;
	int mMoving;
	int mType;
	int mDir;
public:
	CEnemy();
	~CEnemy();

	void Render(HDC);
	void Collision();
	int Animate();
};

