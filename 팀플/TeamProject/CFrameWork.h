#pragma once
#include "Header.h"
#include "CPlayer.h"
#include "CScene.h"
#include "CEnemy.h"

class CFrameWork
{
	CImage mMesh;						// ����ȭ��
	CGameObject* mPlayer;			// �÷��̾�
	CGameObject* mDuo;				// 2�ο�
	CGameObject* mEnemy[100];			// ��
	CGameObject* mItem[20];
	CGameObject* mBoss;
	CScene* mScene;					// ��
	
	GAMESTATE GameState;			// ������ ���� ����

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

