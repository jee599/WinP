#include "CScene.h"

CScene::CScene()
{
	mMeshCount = 0;
	// Main State Mesh
	mTitleMesh[0].Load(TEXT("메인화면.png"));

	mTitleMesh[1].Load(TEXT("제목1.png"));
	mTitleMesh[2].Load(TEXT("시작.png"));
	mTitleMesh[3].Load(TEXT("종료.png"));

	//mTitleMesh[3].Load(TEXT("배경4.png"));


	// Button
	Button[CHANGE] = { 646,606,741,670 };
	Button[GAMEPLAY] = { 120,650,380,750 };
	Button[EXIT] = { 650,650,950,750 };
	
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

		if (mMeshCount == 60)
			mMeshCount = 0;
		//mTitleMesh[mMeshCount++ / 15].Draw(Buffer, 0, 0, WIDTH, HEIGHT);
		mTitleMesh[0].Draw(Buffer, 0, 0, WIDTH, HEIGHT);
		mTitleMesh[1].Draw(Buffer, 90, 20); // Title
		mTitleMesh[2].Draw(Buffer, 120, 650); // Start
		mTitleMesh[3].Draw(Buffer, 650, 650); // Exit
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
