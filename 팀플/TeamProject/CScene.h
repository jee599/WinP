#pragma once
#include "Header.h"

class CScene
{
	CImage mPlayMesh;
	CImage mTitleMesh[4];
	int MeshCount;
	int MeshAnimate = 0;
	RECT Button[3];			// ��ư�� RECT�� ����
public:
	CScene();
	~CScene();
public:
	void Render(HDC, GAMESTATE);
	void Animation(ANIMATION);
	GAMESTATE MouseDown(POINT);
};

