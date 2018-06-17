#pragma once
#include "Header.h"

class CEffect
{
	CImage mMesh[10];
	int mMeshCount;
	int mSceneCount;
	int mLeftRight;

public:
	CEffect();
	~CEffect();

	bool Render(HDC, POINT);
};

