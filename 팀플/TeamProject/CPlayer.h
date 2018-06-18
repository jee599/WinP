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
	int mMana;
	int mLife;
	int mSkillTimer;

	int mDamage;
	int mScore;
	int mLevel;

	PICKTYPE mType;
	bool IsBullet = false;
	bool IsRevolution;
	bool mAnimationCut;
	bool IsSkillRender = false;
	bool IsSkill;

	CImage mSkillMesh[10];
public:
	vector<CBullet*> mBullet;

public:
	CPlayer() {}
	CPlayer(PICKTYPE, int);
	~CPlayer();

public:
	bool Skill() { return IsSkillRender; }
	void Move(WPARAM);
	void Render(HDC);
	void MakeBullet();
	void Animate();
	void StopBullet();
	void ScoreUp() { mScore++; }
	void DamageUp() { mDamage++; }
};

