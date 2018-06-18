#include "CScene.h"

CScene::CScene()
{
	mMeshCount = 0;
	// Main State Mesh
	PlaySound("Main_Sound.wav", NULL, SND_ASYNC | SND_LOOP); // 배경음악-이거는 캐릭터선택창까지 나오게하면될거같음
	mTitleMesh[0].Load(TEXT("메인화면1.png"));
	mTitleMesh[1].Load(TEXT("캐릭터선택.png"));
	mTitleMesh[2].Load(TEXT("Start.png"));
	mTitleMesh[3].Load(TEXT("Cancle.png"));

	mTitleMesh[4].Load(TEXT("Win.png"));
	mPlayMesh[9].Load(TEXT("stage11.png"));
	// Font
	mFontMesh[0].Load(TEXT("Morning.png"));
	mFontMesh[1].Load(TEXT("Night.png"));
	
	mPlayerMesh[ELEC].Load(TEXT("피카츄1.png"));
	mPlayerMesh[FIRE].Load(TEXT("파이리1.png"));
	mPlayerMesh[WATER].Load(TEXT("꼬부기1.png"));
	mPlayerMesh[GRASS].Load(TEXT("이상해씨1.png"));
	// Button
	Button[BATTLE] = { 400,670,650,755 };
	Button[GAMEPLAY] = { 120,650,380,750 };
	Button[EXIT] = { 650,650,950,750 };
	
	PickType[ELEC] = {78,580,183,722};
	PickType[WATER] = {337,582,440,745};
	PickType[FIRE] = {615,595,715,725};
	PickType[GRASS] = {820,592,922,725};
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
	RECT Temp = { 400, 350, 550, 425 };
	RECT Temp1 = { 400, 450, 550, 525 };
	RECT Temp2 = { 0,0,WIDTH,HEIGHT };

	if (State == WIN)
		if (PtInRect(&Temp2, Point))
			return TITLE;
	if (State == PICK)
	{
		for (int i = 1; i < 5; ++i)
			if (PtInRect(&PickType[(PICKTYPE)i], Point))
			{
				if (Player1 == NONE)
					Player1 = (PICKTYPE)i;
				else if(Player2 == NONE)
					Player2 = (PICKTYPE)i;
			}
		if (Player2 == NONE && Player1 != NONE && PtInRect(&Temp1, Point))
			Player1 = NONE;
		if (Player2 != NONE && PtInRect(&Temp1, Point))
			Player2 = NONE;
		if(Player2 != NONE && PtInRect(&Temp, Point))
			return mGameMode;
		return PICK;
	}
	if (State == TITLE)
	{
		if (PtInRect(&Button[BATTLE], Point))
		{
			mGameMode = BATTLE;
			return PICK;
		}
		if (PtInRect(&Button[GAMEPLAY], Point))
		{
			mGameMode = GAMEPLAY;
			PlaySound(NULL, NULL, NULL);
			PlaySound("Boss.wav", NULL, SND_ASYNC | SND_LOOP);
			return PICK;
		}

		if (PtInRect(&Button[EXIT], Point))
			return EXIT;
	}
	return TITLE;
}

void CScene::Animation(ANIMATION State)
{
}

void CScene::Render(HDC Buffer, GAMESTATE State)
{
	if (State == WIN)
		mTitleMesh[4].Draw(Buffer, 0, 0, WIDTH, HEIGHT);
	if (State == TITLE)
		mTitleMesh[0].Draw(Buffer, 0, 0, WIDTH, HEIGHT);
	if (State == PICK)
	{
		mTitleMesh[1].Draw(Buffer, 0, 0, WIDTH, HEIGHT);
		mTitleMesh[2].Draw(Buffer, 400, 350, 150, 75);
		mTitleMesh[3].Draw(Buffer, 400, 450, 150, 75);
		if (Player1 != NONE)
			mPlayerMesh[Player1].Draw(Buffer, 120, 255, 200, 200);
		if (Player2 != NONE)
			mPlayerMesh[Player2].Draw(Buffer, 680, 250, 200, 200);
	}
	if (State == BATTLE)
		mPlayMesh[9].Draw(Buffer, 0, 0, WIDTH, HEIGHT);
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
		if (FontMoving > 400)
			FontMoving--;

		if (State == BOSS)
			mFontMesh[1].Draw(Buffer, FontMoving, 20);
		else
			mFontMesh[0].Draw(Buffer, FontMoving, 20);
	}
}
