#pragma once
#include "CGameObject.h"
#include "CEffect.h"

class CEnemy : public CGameObject
{
	int mLife;
	CEffect* mEffect;
	ENEMYSTATE mState;
	bool IsDead = false;
	int mMoving;
	int mType;
public:
	CEnemy();
	~CEnemy();

	void Render(HDC);
	void Collision();
	bool Animate();
	int GetLife() { return mLife; }
};

