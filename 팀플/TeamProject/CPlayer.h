#pragma once

#include "Header.h"
#include "CGameObject.h"
#include "CBullet.h"

class CPlayer : public CGameObject
{
	vector<CBullet*> mBullet;
	int mMeshCount;
	int mDirect;
	int mBulletCount = 0;
	int mBulletNumber = 3;
	bool IsBullet = false;
public:
	CPlayer();
	CPlayer(int);
	~CPlayer();
public:
	void Move(WPARAM);
	void Render(HDC);
	void MakeBullet();
	void Animate();
	void StopBullet();
};

