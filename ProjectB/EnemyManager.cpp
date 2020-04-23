#include "stdafx.h"
#include <d2d1.h>
#include "TextureLoader.h"
#include "EnemyManager.h"
#include "Stage.h"
#include "GameData.h"
#include <stdlib.h>
#include <time.h>

#include "Enemy.h"


CEnemyManager::CEnemyManager(CStage *pStage)
{
	m_pStage = pStage;

	pTarget = pStage->GetRenderTarget();
	CTextureLoader::CreateD2D1BitmapFromFile(pTarget, _T("res\\enemy1.png"), &pEnemy0);
	CTextureLoader::CreateD2D1BitmapFromFile(pTarget, _T("res\\enemy2.png"), &pEnemy1);
	ESpawnMAXnum = 3;
	ESpawnMINnum = 1;
	ESpawnType = 1;


	for (int i = 0; i < ENEMY_NUM; ++i) {
		enemy[i] = NULL;
		Esetplace[i] = i;
	}
	EShuffle();
	srand(time(NULL));
	rand();
}


CEnemyManager::~CEnemyManager()
{
	SAFE_RELEASE(pEnemy0);
	SAFE_RELEASE(pEnemy1);

	for (int i = 0; i < ENEMY_NUM; ++i) {
		if(enemy[i]!=NULL)
			SAFE_DELETE(enemy[i]);
	}
}

bool CEnemyManager::move() {
	//! すべての配列がNULLなら生成開始
	if (GetState()) {
		SetESpawnNum();
		if ((rand() >> 2) % 25 == 0) {	//スポーン確率
			int num = rand() % ESpawnMAXnum + ESpawnMINnum;	//スポーン数の決定
			if (num > ENEMY_NUM)
				num = ENEMY_NUM;
			Spawn(num);
		}
	}
	//! エネミーの移動
	for (int i = 0; i < ENEMY_NUM; ++i) {
		if (enemy[i] != NULL) {
			enemy[i]->move();
			if (enemy[i]->GetFlag() == false) {
				SAFE_DELETE(enemy[i]);
			}
		}
	}
	return GameSceneResultCode::GAMESCENE_DEFAULT;
}

void CEnemyManager::draw(ID2D1RenderTarget *pRenderTarget) {
	for (int i = 0; i < ENEMY_NUM; ++i) {
		if (enemy[i] != NULL) {
			enemy[i]->draw(pRenderTarget);
		}
	}
}

void CEnemyManager::SetESpawnNum() {
	switch (GameData::StagePhase) {
	case NOON:
		ESpawnMAXnum = 3;
		ESpawnMINnum = 1;
		ESpawnType = 1;
		break;
	case TWILIGHT:
		ESpawnMAXnum = 6;
		ESpawnMINnum = 2;
		ESpawnType = 1;
		break;
	case NIGHT:
		ESpawnMAXnum = 8;
		ESpawnMINnum = 4;
		ESpawnType = 2;
		break;
	case BLOODMOON:
		ESpawnMAXnum = 12;
		ESpawnMINnum = 5;
		ESpawnType = 2;
		break;
	}
}

void CEnemyManager::Spawn(int num) {
	for (int i = 0; i < num; ++i) {
		bool color_ = (rand() >> 4) % 2;	//色の乱数
		char type_ = (rand() >> 4) % ESpawnType;		//タイプの乱数
		enemy[i] = new CEnemy(pTarget,pEnemy0,pEnemy1);	//画像のポインターも送る
		enemy[i]->SetSpawn(Esetplace[i],color_,type_);
	}
	EShuffle();
}

bool CEnemyManager::GetState() {
	for (int i = 0; i < ENEMY_NUM; ++i) {
		if (enemy[i] != NULL)
			return false;
	}
	return true;
}

//! 配列の中身のシャッフル
void CEnemyManager::EShuffle() {
	for (int i = ENEMY_NUM - 1; i > 0 ; --i) {
		char r = (rand() >> 2) % i;
		char s = Esetplace[i];
		Esetplace[i] = Esetplace[r];
		Esetplace[r] = s;
	}
}