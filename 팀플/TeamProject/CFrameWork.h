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
	CGameObject* mEnemy[100];			// 적
	CGameObject* mItem[20];
	CGameObject* mBoss;
	CScene* mScene;					// 씬
	
	GAMESTATE GameState;			// 게임의 현재 상태

	HDC BackBuffer;
	HBITMAP hBitmap;
	 
	int mBossState = 0;
	int Timer = 0;
	int mBossCount = 0;
	int mEnemyCount = 0;
	int mItemCount = 0;
	bool IsBoss = false;
	bool IsInit = true;
public:
	CFrameWork();
	~CFrameWork();
public:
	void InitialObject();
	void DestroyObject();
	void Render(HDC);
	void Animate();
	void CollCheck();

	void MakeFood(POINT);
	void MouseDown(LPARAM);
	void KeyDown(WPARAM);
	void KeyUp(WPARAM);
};

