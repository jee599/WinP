#pragma once
#include "Header.h"

class CScene
{
	CImage mPlayMesh[3];
	CImage mTitleMesh[8];
	int mMeshCount;
	int mMeshAnimate[3];
	RECT Button[3];			// ��ư�� RECT�� ����
	int mTimer = 0;
public:
	CScene();
	~CScene();
public:
	void Render(HDC, GAMESTATE);
	void Animation(ANIMATION);
	GAMESTATE MouseDown(POINT);
};

