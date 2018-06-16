#include "CEffect.h"

CEffect::CEffect()
{
	mMesh[0].Load(TEXT("ball1.png"));
	mMesh[1].Load(TEXT("ball2.png"));
	mMesh[2].Load(TEXT("ball2.png"));
	mMesh[3].Load(TEXT("ball1.png"));
	mMeshCount = 0;
	mLeftRight = 0;
}

CEffect::~CEffect()
{
	mMesh->Destroy();
}

bool CEffect::Render(HDC Buffer, POINT Position)
{
	mMeshCount++;
	if (mMeshCount >= 90)
		return true;
	
	mSceneCount = mMeshCount / 10;
	
	if (mSceneCount > 3)
	{
		mSceneCount = 3;
		if ((mMeshCount % 10) < 5)
			mLeftRight = mMeshCount % 10;
		else
			mLeftRight = -1 * ((mMeshCount % 10) - 5);
	}
	mMesh[mSceneCount].Draw(Buffer, Position.x + mLeftRight, Position.y, 25, 25);
	return false;
}
