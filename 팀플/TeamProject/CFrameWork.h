#pragma once
#include "Header.h"
#include "CPlayer.h"
#include "CScene.h"
#include "CEnemy.h"

class CFrameWork
{
	CImage mMesh;						// 바탕화면
	CGameObject* mPlayer;			// 플레이어
	CGameObject* mDuo;				// 2인용
	CGameObject* mEnemy;			// 적
	CScene* mScene;					// 씬
	
	GAMESTATE GameState;			// 게임의 현재 상태

	HDC BackBuffer;
	HBITMAP hBitmap;

public:
	CFrameWork();
	~CFrameWork();
public:
	void InitialObject();
	void DestroyObject();
	void Render(HDC);
	void Animate();
	void MouseDown(LPARAM);
	void KeyDown(WPARAM);
	void KeyUp(WPARAM);
};

