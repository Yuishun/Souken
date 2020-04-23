#pragma once

#ifndef __IGAMEOBJECT_H__
#include "IGameObject.h"
#endif

#define ENEMY_NUM 12
class CStage;

class CEnemy;
class CEnemyManager
{
public:
	CEnemyManager(CStage *pStage);
	virtual ~CEnemyManager();
	virtual bool move();
	virtual void draw(ID2D1RenderTarget *pRenderTarget);
	void SetESpawnNum();
protected:
	CStage			*m_pStage;
	CEnemy *enemy[ENEMY_NUM];
	ID2D1RenderTarget *pTarget;
	ID2D1Bitmap *pEnemy0;
	ID2D1Bitmap *pEnemy1;
	unsigned char ESpawnMAXnum;		//敵が出てくる最大数
	unsigned char ESpawnMINnum;		//敵が出てくる最低数
	unsigned char ESpawnType;		//敵のタイプ制御用

private:
	void Spawn(int num);
	bool GetState();
	void EShuffle();
	char Esetplace[ENEMY_NUM];
};

