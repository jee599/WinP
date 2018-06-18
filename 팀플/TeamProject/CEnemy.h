#pragma once
#include "CGameObject.h"
#include "CEffect.h"

class CEnemy : public CGameObject
{
	int mLife;
	CEffect* mEffect;
	int mMoving;
	int mType;
	int mDir;
	int IsEnd = 0;
public:
	CEnemy();
	CEnemy(GAMESTATE);
	~CEnemy();

	void GetDamage();
	void Render(HDC);
	bool Collision(int);
	int Animate();

public:
	ENEMYSTATE mState;
	int mBossState = 1;
};

