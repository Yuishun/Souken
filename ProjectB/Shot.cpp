#include "stdafx.h"
#include "d2d1.h"
#include "Shot.h"
#include "TextureLoader.h"
#include "GameData.h"


CShot::CShot(ID2D1RenderTarget *pRenderTarget)
{
	g_pShotImage = NULL;
	g_pRenderTarget = pRenderTarget;

	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\ohuda.png"), &g_pShotImage);


}


CShot::~CShot()
{
	SAFE_RELEASE(g_pShotImage);
}

bool CShot::move() {
	//ShotåÇÇ¡ÇΩéûÇÃèàóù
	if (GameData::ShotFlag == true) {
		for (int i = 0; i < PSHOT_NUM; ++i) {
			if (GameData::shot[i].flag == false) {
				GameData::shot[i].flag = true;
				GameData::shot[i].right = GameData::PlayerPoint[2] + (100.0f - Shotspeed);
				GameData::shot[i].top = GameData::PlayerPoint[1] - 30.0f;
				GameData::shot[i].Shotcolor = GameData::NowPlayerColor;
				break;
			}
		}
		GameData::ShotFlag = false;
	}
	//ShotÇÃà⁄ìÆèàóù
	for (int i = 0; i < PSHOT_NUM; ++i) {
		if (GameData::shot[i].flag) {
			GameData::shot[i].right += Shotspeed;
			if (GameData::shot[i].right >= 2020) {
				GameData::shot[i].flag = false;
			}
		}
	}
	return GameSceneResultCode::GAMESCENE_DEFAULT;
}

void CShot::draw(ID2D1RenderTarget *pRenderTarget) {
	D2D1_RECT_F rc, src;

	for (int i = 0; i < PSHOT_NUM; ++i) {
		if (GameData::shot[i].flag) {
			rc.left = GameData::shot[i].right - 100.0f;
			rc.right = GameData::shot[i].right;
			rc.top = GameData::shot[i].top;
			rc.bottom = GameData::shot[i].top + 100.0f;

			src.top = 0;
			src.bottom = 100;
			if (GameData::shot[i].Shotcolor == Red_) {
				src.left = 0;
				src.right = 100;
			}
			else if (GameData::shot[i].Shotcolor == Blue_) {
				src.left = 100;
				src.right = 200;
			}
			else if (GameData::shot[i].Shotcolor == Purple_) {
				src.left = 200;
				src.right = 300;
			}
			g_pRenderTarget->DrawBitmap(g_pShotImage, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);
		}
	}
}

