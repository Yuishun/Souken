#include "stdafx.h"
#include <d2d1.h>
#include "StarShot.h"
#include "TextureLoader.h"
#include "GameData.h"
#include <math.h>

CStarShot::CStarShot(ID2D1RenderTarget *pRenderTarget)
{
	StarTime = 0;
	Angle_rotation = 0.f;
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\Starshot.png"), &pStarShot);
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\Stareffect.png"), &pBGStar);
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\BGStar.png"), &pBGStar_2);

}


CStarShot::~CStarShot()
{
	SAFE_RELEASE(pStarShot);
	SAFE_RELEASE(pBGStar);
	SAFE_RELEASE(pBGStar_2);
}

bool CStarShot::move() {
	switch (GameData::StarShot) {
	case 1:
		if (StarTime == 0) {
			rc.left = GameData::PlayerPoint[2];
			rc.top = GameData::PlayerPoint[1];
			rc2.left = Star_Dis_l-150;
			rc2.right = rc2.left + 600;
			rc2.top = Star_Dis_t-150;
			rc2.bottom = rc2.top + 600;
			m = (Star_Dis_t - rc.top) / (Star_Dis_l - rc.left);
			b = rc.top + (m * -rc.left);
			speed = (Star_Dis_l - rc.left) / 120.f;
			scale = 0.3f;
		}
		StarTime++;
		Angle_rotation += 30.f;
		if (Angle_rotation >= 360)
			Angle_rotation = 0;
		rc.left += speed;
		if (rc.left >= Star_Dis_l)
			rc.left = Star_Dis_l;
		rc.top = m * rc.left + b;
		break;
	case 2:
		StarTime++;
		Angle_rotation += 2.4f;
		if (Angle_rotation >= 360)
			Angle_rotation = 0;

	}
	return GameSceneResultCode::GAMESCENE_DEFAULT;
}

void CStarShot::draw(ID2D1RenderTarget *pRenderTarget) {
	switch (GameData::StarShot) {
	case 1:
		rc.right = rc.left + StarShot_width;
		rc.bottom = rc.top + StarShot_width;

		if (StarTime >= 120) {
			Angle_rotation = 0;
			if (scale <= 6.f) {
				scale += 0.01f;
			}
			else if (scale < 1.f) {
				scale += 0.02f;
			}
			if (scale >= 1.f)
				scale = 1.f;
		}
		if (StarTime > 180) {
			StarTime = 0;
			GameData::StarShot = 2;
			rc2.left = 510;
			rc2.right = rc2.left + 900;
			rc2.top = 130;
			rc2.bottom = rc2.top + 900;
		}

		{
		//! 回転中心座標
		D2D_POINT_2F tRotateCenter = D2D1::Point2F(
			(rc.left + rc.right) / 2
			, (rc.top + rc.bottom) / 2
		);
		D2D1::Matrix3x2F matrix1 = D2D1::Matrix3x2F::Rotation(Angle_rotation, tRotateCenter);
		D2D1::Matrix3x2F matrix2 = D2D1::Matrix3x2F::Scale(scale, scale, tRotateCenter);
		D2D1::Matrix3x2F matrix3 = matrix1 * matrix2;
		//! 座標変換（回転）
		pRenderTarget->SetTransform(matrix3);

		pRenderTarget->DrawBitmap(pStarShot, rc, 1.f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
		
		if (StarTime > 120)
			pRenderTarget->DrawBitmap(pBGStar, rc2, 1.f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);

		//! 座標変換を元に戻す
		pRenderTarget->SetTransform(
			D2D1::Matrix3x2F::Identity()
		);
		}
		break;
	case 2:
		//! 回転中心座標
		D2D_POINT_2F tRotateCenter = D2D1::Point2F(
			(rc2.left + rc2.right) / 2
			, (rc2.top + rc2.bottom) / 2
		);

		//! 回転（BG)
		pRenderTarget->SetTransform(
			D2D1::Matrix3x2F::Rotation(-Angle_rotation, tRotateCenter)
		);
		rc2.left += 200;
		rc2.right -= 200;
		rc2.top += 200;
		rc2.bottom -= 200;
		pRenderTarget->DrawBitmap(pBGStar_2, rc2, 0.8f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
		rc2.left -= 200;
		rc2.right += 200;
		rc2.top -= 200;
		rc2.bottom += 200;

		//! 座標変換を元に戻す
		pRenderTarget->SetTransform(
			D2D1::Matrix3x2F::Identity()
		);
		pRenderTarget->DrawBitmap(pStarShot, rc, 1.f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);

		//! 座標変換（回転）
		pRenderTarget->SetTransform(
			D2D1::Matrix3x2F::Rotation(Angle_rotation, tRotateCenter)
		);

		pRenderTarget->DrawBitmap(pBGStar, rc2, 1.f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
		
		//! 座標変換を元に戻す
		pRenderTarget->SetTransform(
			D2D1::Matrix3x2F::Identity()
		);


		if (StarTime % 150==0) {
			GameData::Stargauge -= 1;
			if (GameData::Stargauge <= 0) {
				StarTime = 0;
				GameData::StarShot = 0;
			}
		}
		break;
	}
}