#include "CScene.h"

CScene::CScene()
{
	mMeshCount = 0;
	// Main State Mesh
	mTitleMesh[0].Load(TEXT("메인화면.png"));
	mTitleMesh[1].Load(TEXT("제목블루.png"));
	mTitleMesh[2].Load(TEXT("start.png"));
	mTitleMesh[3].Load(TEXT("exit.png"));
	// Button
	Button[CHANGE] = { 646,606,741,670 };
	Button[GAMEPLAY] = { 714,485,843,577 };
	Button[EXIT] = { 815,606,914,670 };
	
	// Play State Mesh
	mPlayMesh[0].Load(TEXT("stage21.png"));
	mPlayMesh[1].Load(TEXT("stage22.png"));
	mPlayMesh[2].Load(TEXT("stage23.png"));

	memset(mMeshAnimate, 0, sizeof(mMeshAnimate));
}

CScene::~CScene()
{
	mTitleMesh->Destroy();
	mPlayMesh->Destroy();
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

void CScene::Animation(ANIMATION State)
{
	switch (State)
	{
	case START:
		break;

	}
}

void CScene::Render(HDC Buffer, GAMESTATE State)
{
	if (State == TITLE)
	{
		mTitleMesh[0].Draw(Buffer, 0, 0, WIDTH, HEIGHT);
		mTitleMesh[1].Draw(Buffer, 325, 70, 400, 200);
		mTitleMesh[2].Draw(Buffer, 200, 450, 300, 100);
		mTitleMesh[3].Draw(Buffer, 500 ,500, 300, 50);
	}

	if (State == CHANGE)
	{

	}
	if (State == GAMEPLAY)
	{
		mPlayMesh[0].Draw(Buffer, mMeshAnimate[0] + mMeshAnimate[0] % 2, 0, WIDTH, 400);
		mPlayMesh[0].Draw(Buffer, mMeshAnimate[0] + WIDTH + mMeshAnimate[0] % 2, 0, WIDTH, 400);
		if (mTimer++ % 5 == 0)
			mMeshAnimate[0]--;
		if (mMeshAnimate[0] < -WIDTH)
			mMeshAnimate[0] = 0;
		mPlayMesh[1].Draw(Buffer, mMeshAnimate[1] + mMeshAnimate[1] % 2, 0 , WIDTH, 800);
		mPlayMesh[1].Draw(Buffer, mMeshAnimate[1] + WIDTH + mMeshAnimate[1] % 2, 0, WIDTH, 800);
		mMeshAnimate[1]--;
		if (mMeshAnimate[1] < -WIDTH)
			mMeshAnimate[1] = 0;
		mPlayMesh[2].Draw(Buffer, mMeshAnimate[2] + mMeshAnimate[2] % 2, 0, WIDTH, 800);
		mPlayMesh[2].Draw(Buffer, mMeshAnimate[2] + WIDTH + mMeshAnimate[2] % 2, 0, WIDTH, 800);
		mMeshAnimate[2] -= 4;
		if (mMeshAnimate[2] < -WIDTH)
			mMeshAnimate[2] = 0;
	}
}
