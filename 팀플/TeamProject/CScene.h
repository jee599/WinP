#pragma once
#include "Header.h"

class CScene
{
	CImage mPlayMesh;
	CImage mTitleMesh[4];
	int MeshCount;
	int MeshAnimate = 0;
	RECT Button[3];			// 버튼의 RECT값 저장
public:
	CScene();
	~CScene();
public:
	void Render(HDC, GAMESTATE);
	void Animation(ANIMATION);
	GAMESTATE MouseDown(POINT);
};

