#include "stdafx.h"
#include <d2d1.h>
#include "Enemy.h"
#include <math.h>
#include"TextureLoader.h"
#include "SoundManager.h"

CEnemy::CEnemy(ID2D1RenderTarget *pRenderTarget, ID2D1Bitmap *pEnemy0, ID2D1Bitmap *pEnemy1)
{
	e_pEnemy0 = pEnemy0;
	e_pEnemy1 = pEnemy1;
	flag = true;
	count = 0;
	opacity = 1.f;
}

CEnemy::~CEnemy()
{
}

bool CEnemy::move() {
	count = (count + 1) % 120;

	if (hp > 0) {
		rc.left -= GameData::RunSpeed;
		rc.bottom = fluffy + sin(PI * 2 / 120 * count) * 10;
		if (count % 8 == 0) {
			if (src.left <= 0 || src.left >= width * 3)
				srcplus = -srcplus;
			src.left += srcplus;
		}
		src.right = src.left + width;

		if (rc.left <= -width) {
			flag = false;
			return GameSceneResultCode::GAMESCENE_DEFAULT;
		}

		//! プレイヤーとの当たり判定
		if (PointinRect(GameData::PlayerPoint[0], GameData::PlayerPoint[1],
			GameData::PlayerPoint[2], GameData::PlayerPoint[3])) {
			GameData::PlayerDamage = true;
		}
		//! ショットとの当たり判定
		for (int i = 0; i < PSHOT_NUM; ++i) {
			if (GameData::shot[i].flag) {
				if (PointinRect(GameData::shot[i].right - SHOT_WIDTH, GameData::shot[i].top,
					GameData::shot[i].right, GameData::shot[i].top + SHOT_WIDTH)) {
					CSoundManager::PlayOneShot(0, 2.0f);
					//! HPを減らすかどうか
					if (type != 1) {
						--hp;
						GameData::shot[i].flag = false;
					}
					else if (type == 1 && GameData::shot[i].Shotcolor == Ecolor) {
						--hp;
						GameData::shot[i].flag = false;
					}
					else {
						GameData::shot[i].flag = false;
					}
					//! スコア計算
					if (hp <= 0 && GameData::shot[i].Shotcolor == Ecolor) {
						GameData::Score += score * 2;
						GameData::ItemCounter += 1;
					}
					else if(hp <= 0)
						GameData::Score += score;
				}
			}
		}
		//! スターショットの処理
		if (GameData::StarShot == 2&&STAR_XLINE >= rc.left) {
			--hp;
			//! スコア計算
			if (hp <= 0 && GameData::NowPlayerColor == Ecolor) {
				GameData::Score += score * 2;
				GameData::ItemCounter += 1;
			}
			else if (hp <= 0)
				GameData::Score += score;

		}
	}
	//! やられモーション
	if (hp <= 0) {
		rc.left += 2.f;
		rc.bottom -= 2.f;
		opacity -= 0.1f;
		if(opacity<=0)
			flag = false;
	}
	return GameSceneResultCode::GAMESCENE_DEFAULT;
}

void CEnemy::draw(ID2D1RenderTarget *pRenderTarget){
	if (rc.left > 1920.f) {
		return;
	}
	rc.right = rc.left + width;
	rc.top = rc.bottom - width;
	switch (type) {
	case 0:
 		pRenderTarget->DrawBitmap(e_pEnemy0, rc, opacity, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);
		break;
	case 1:
		pRenderTarget->DrawBitmap(e_pEnemy1, rc, opacity, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);
		break;
	}
}

void CEnemy::SetSpawn(int pos_,bool color_,char type_) {
	if (color_ == 0)
		Ecolor = Red_;
	else
		Ecolor = Blue_;

	type = type_;
	float l_set, b_set;
	switch (type) {
	case 0:
		width = ETYPE0WIDTH;
		l_set = ETYPE1WIDTH + 30.f;
		b_set = ENEMY0_TOP_B;
		hp = 1;
		score = 100;
		break;
	case 1:
		width = ETYPE1WIDTH;
		l_set = ETYPE1WIDTH + 30.f;
		b_set = ENEMY1_TOP_B;
		hp = 2;
		score = 200;
		break;
	}
	rc.left = ENEMY_LEFT + (l_set*(pos_ % 4));
	switch (pos_ % 3) {
	case 0:
		break;
	case 1:
		b_set += 320.f;
		break;
	case 2:
		b_set += 680.f;
		break;
	}
	rc.bottom = b_set;
	fluffy = rc.bottom;
	src.top = Ecolor * width;
	src.bottom = src.top + width;
	srcplus = -width;
}

bool CEnemy::PointinRect(float x1,float y1,float x2,float y2) {
	if (x1 <= rc.right&&rc.left <= x2) {
		if (y1 <= rc.bottom&&rc.top <= y2) {
			return true;
		}
	}
	return false;
}

