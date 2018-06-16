#pragma once

#include "Header.h"
#include "CGameObject.h"
#include "CBullet.h"

class CPlayer : public CGameObject
{
	int mMeshCount;
	int mDirect;
	int mBulletCount = 0;
	int mBulletNumber = 1;
	int mType;
	
	bool IsBullet = false;

public:
	vector<CBullet*> mBullet;

public:
	CPlayer() {}
	CPlayer(int);
	~CPlayer();

public:
	void Move(WPARAM);
	void Render(HDC);
	void MakeBullet();
	void Animate();
	void StopBullet();
};

