#include "CEnemy.h"

CEnemy::CEnemy()
{
	mMesh[0].Load(TEXT("��.png"));
	mPosition = { WIDTH - 30, HEIGHT / 2 };
}

CEnemy::~CEnemy()
{
}

void CEnemy::Render()
{

}
