#pragma once
#include "Header.h"

class CScene
{
	CImage mPlayMesh[10];
	CImage mTitleMesh[10];
	CImage mFontMesh[2];
	CImage mPlayerMesh[10];

	int FontMoving = WIDTH;
	int mMeshCount;
	int mMeshAnimate[3];
	RECT Button[3];			// 버튼의 RECT값 저장
	RECT PickType[6];
	int mTimer = 0;
public:
	PICKTYPE Player1 = NONE;
	PICKTYPE Player2 = NONE;

	GAMESTATE mGameMode;
public:
	CScene();
	~CScene();
public:
	void Render(HDC, GAMESTATE);
	void Animation(ANIMATION);
	GAMESTATE MouseDown(POINT,GAMESTATE);
};

