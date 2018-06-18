#include "CScene.h"

CScene::CScene()
{
	mMeshCount = 0;
	// Main State Mesh
	PlaySound("Main_Sound.wav", NULL, SND_ASYNC | SND_LOOP); // 배경음악-이거는 캐릭터선택창까지 나오게하면될거같음
	mTitleMesh[0].Load(TEXT("메인화면1.png"));

	// Button
	Button[BATTLE] = { 400,670,650,755 };
	Button[GAMEPLAY] = { 120,650,380,750 };
	Button[EXIT] = { 650,650,950,750 };
	
	// Play State Mesh
	mPlayMesh[0].Load(TEXT("stage11.png"));
	mPlayMesh[1].Load(TEXT("stage12.png"));
	mPlayMesh[2].Load(TEXT("stage13.png"));

	mPlayMesh[3].Load(TEXT("Stage21.png"));
	mPlayMesh[4].Load(TEXT("stage22.png"));
	mPlayMesh[5].Load(TEXT("stage23.png"));

	memset(mMeshAnimate, 0, sizeof(mMeshAnimate));
}

CScene::~CScene()
{
	mTitleMesh->Destroy();
	mPlayMesh->Destroy();
}

GAMESTATE CScene::MouseDown(POINT Point, GAMESTATE State)
{
	if (State == TITLE)
	{
		if (PtInRect(&Button[BATTLE], Point))
			return BATTLE;
		if (PtInRect(&Button[GAMEPLAY], Point))
		{
			PlaySound(NULL, NULL, NULL);
			PlaySound("Boss.wav", NULL, SND_ASYNC | SND_LOOP);
			return GAMEPLAY;
		}

		if (PtInRect(&Button[EXIT], Point))
			return EXIT;
	}
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
	}

	if (State == BATTLE)
	{

	}
	if (State == GAMEPLAY || State == BOSS)
	{
		int Index;
		if (State == GAMEPLAY)
			Index = 0;
		if (State == BOSS)
			Index = 3;
		mPlayMesh[Index].Draw(Buffer, mMeshAnimate[0] + mMeshAnimate[0] % 2, 0, WIDTH, 400);
		mPlayMesh[Index].Draw(Buffer, mMeshAnimate[0] + WIDTH + mMeshAnimate[0] % 2, 0, WIDTH, 400);
		if (mTimer++ % 5 == 0)
			mMeshAnimate[0]--;
		if (mMeshAnimate[0] < -WIDTH)
			mMeshAnimate[0] = 0;
		mPlayMesh[Index+1].Draw(Buffer, mMeshAnimate[1] + mMeshAnimate[1] % 2, 0 , WIDTH, 800);
		mPlayMesh[Index+1].Draw(Buffer, mMeshAnimate[1] + WIDTH + mMeshAnimate[1] % 2, 0, WIDTH, 800);
		mMeshAnimate[1]--;
		if (mMeshAnimate[1] < -WIDTH)
			mMeshAnimate[1] = 0;
		mPlayMesh[Index+2].Draw(Buffer, mMeshAnimate[2] + mMeshAnimate[2] % 2, 0, WIDTH, 800);
		mPlayMesh[Index+2].Draw(Buffer, mMeshAnimate[2] + WIDTH + mMeshAnimate[2] % 2, 0, WIDTH, 800);
		mMeshAnimate[2] -= 4;
		if (mMeshAnimate[2] < -WIDTH)
			mMeshAnimate[2] = 0;
	}
}
