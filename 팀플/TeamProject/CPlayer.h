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
	bool IsSkill;

	CImage mSkillMesh[15];
	CImage mEffectMesh[10];
public:
	vector<CBullet*> mBullet;
	bool IsSkillRender = false;
	int mEffectTimer = 0;
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
	void ScoreUp(int);
	void DamageUp() { mDamage++; }
};

