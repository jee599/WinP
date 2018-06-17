#pragma once
#include "CGameObject.h"
#include "CEffect.h"

class CEnemy : public CGameObject
{
	int mLife;
	CEffect* mEffect;
	int IsEnd = 0;
	int mMoving;
	int mType;
	int mDir;
public:
	CEnemy();
	~CEnemy();

	void Render(HDC);
	bool Collision(int);
	int Animate();

public:
	ENEMYSTATE mState;

};

