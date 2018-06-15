#include "CScene.h"

CScene::CScene()
{
	MeshCount = 0;
	// Main State Mesh
	mTitleMesh[0].Load(TEXT("배경1.png"));
	mTitleMesh[1].Load(TEXT("배경2.png"));
	mTitleMesh[2].Load(TEXT("배경3.png"));
	mTitleMesh[3].Load(TEXT("배경4.png"));

	// Button
	Button[CHANGE] = { 646,606,741,670 };
	Button[GAMEPLAY] = { 714,485,843,577 };
	Button[EXIT] = { 815,606,914,670 };
	
	// Play State Mesh
	mPlayMesh.Load(TEXT("게임.png"));
}

CScene::~CScene()
{
	mTitleMesh->Destroy();
	mPlayMesh.Destroy();
}

GAMESTATE CScene::MouseDown(POINT Point)
{
	if (PtInRect(&Button[CHANGE], Point))
		return CHANGE;
	if (PtInRect(&Button[GAMEPLAY], Point))
		return GAMEPLAY;
	if (PtInRect(&Button[EXIT], Point))
		return EXIT;
	return TITLE;
}

void CScene::Render(HDC Buffer, GAMESTATE State)
{
	if (State == TITLE)
	{
		if (MeshCount == 60)
			MeshCount = 0;
		mTitleMesh[MeshCount++ / 15].Draw(Buffer, 0, 0, WIDTH, HEIGHT);
	}

	if (State == GAMEPLAY)
	{
		mPlayMesh.Draw(Buffer, MeshAnimate, 0, WIDTH, HEIGHT);
		mPlayMesh.Draw(Buffer, MeshAnimate+WIDTH, 0, WIDTH, HEIGHT);
		MeshAnimate--;
		if (MeshAnimate < -WIDTH)
			MeshAnimate = 0;
	}
}
