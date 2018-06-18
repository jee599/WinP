#pragma once
#include "Header.h"

class CScene
{
	CImage mPlayMesh[10];
	CImage mTitleMesh[10];
	int mMeshCount;
	int mMeshAnimate[3];
	RECT Button[3];			// 버튼의 RECT값 저장
	int mTimer = 0;
public:
	CScene();
	~CScene();
public:
	void Render(HDC, GAMESTATE);
	void Animation(ANIMATION);
	GAMESTATE MouseDown(POINT,GAMESTATE);
};

