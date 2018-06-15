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
	CGameObject* mEnemy;			// ��
	CScene* mScene;					// ��
	
	GAMESTATE GameState;			// ������ ���� ����

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

