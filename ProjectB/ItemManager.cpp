#include "stdafx.h"
#include <d2d1.h>
#include "ItemManager.h"
#include "Stage.h"
#include <stdlib.h>
#include <time.h>
#include "TextureLoader.h"

#include "Item.h"


CItemManager::CItemManager(CStage *pStage)
{
	m_pStage = pStage;

	ID2D1RenderTarget	*pTarget = pStage->GetRenderTarget();
	CTextureLoader::CreateD2D1BitmapFromFile(pTarget, _T("res\\konpeitou.png"), &pItem);

	//	Item[num]の初期化
	for (int num = 0; num < ITEM_NUM; ++num) {
		Item[num] = NULL;
	}

	srand(time(NULL));
	rand();
}


CItemManager::~CItemManager()
{
	SAFE_RELEASE(pItem);
	for (int num = 0; num < ITEM_NUM; num++) {
		if (Item[num] != NULL)
			SAFE_DELETE(Item[num]);
	}

}

bool CItemManager::move()
{

	// スポーン確率
	if ((rand() >> 4) % 200 == 0) {
		char itemlimit = SetISpawnNum();
		Spown(itemlimit);
	}

	// 敵と同じ色で倒しても出てくるようにする
	else if (GameData::ItemCounter >= 20) {
		GameData::ItemCounter = 0;
		Spown(ITEM_NUM);
	}

	for (int num = 0; num < ITEM_NUM; num++) {
		//	NULLでない場合
		if (Item[num] != NULL) {
			Item[num]->move();
			//	アイテムが画面外に出たら
			if ((Item[num])->GetFlag() == false)
				SAFE_DELETE(Item[num]);
		}
	}
	return GameSceneResultCode::GAMESCENE_DEFAULT;
}

void CItemManager::draw(ID2D1RenderTarget *pRenderTarget)
{
	for (int num = 0; num < ITEM_NUM; ++num) {
		//	NULL出ない場合
		if (Item[num] != NULL) {
			Item[num]->draw(pRenderTarget);
		}
	}
}

char CItemManager::SetISpawnNum() {
	switch (GameData::StagePhase) {
	case NOON:
		 return ITEM_NUM;
		break;
	case TWILIGHT:
		return ITEM_NUM;
		break;
	case NIGHT:
		return ITEM_NUM - 1;
		break;
	case BLOODMOON:
		return ITEM_NUM - 2;
		break;
	}
}

void CItemManager::Spown(char itemlimit)
{
	for (int i = 0; i < itemlimit; ++i) {
		int pos_ = (rand() >> 4) % 3;
		int color_ = (rand() >> 4) % 3;
		if (Item[i] == NULL) {
			if (GameData::PlayerHP <= 1200) {
				if (i == 1)
					color_ = 2;
			}
			Item[i] = new CItem(pTarget, pItem);
			Item[i]->SetSpawn(pos_, color_);
			break;
		}
	}
}