#pragma once

#include "Header.h"
#include "CGameObject.h"
#include "CBullet.h"

class CPlayer : public CGameObject
{
	int mMeshCount;
	int mDirect;
	int mBulletCount = 0;
	int mPlayerType;
	int mBulletRate;
	int mBulletSpeed;
	int mSpeed;

	int mScore;
	int mLevel;
	TYPE mType;
	bool IsBullet = false;
	bool IsRevolution;
	bool mAnimationCut;
	int mDamage;
public:
	vector<CBullet*> mBullet;

public:
	CPlayer() {}
	CPlayer(TYPE,int );
	~CPlayer();

public:
	void Move(WPARAM);
	void Render(HDC);
	void MakeBullet();
	void Animate();
	void StopBullet();
	void ScoreUp() { mScore++; }
	void DamageUp() { mDamage++; }
};

