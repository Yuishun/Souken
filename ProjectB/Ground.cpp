/**
* @file		Ground.cpp
* @brief	’·‰®
* @author	yshimada
* @data		20190820
**/
#include "stdafx.h"
#include <d2d1.h>
#include "Ground.h"
#include "TextureLoader.h"
#include "GameData.h"


CGround::CGround(ID2D1RenderTarget *pRenderTarget)
{
	g_Pos[0] = { 0.f,0.f };
	g_Pos[0] = { pRenderTarget->GetSize().width,0.0f };
	g_pGroundImage = NULL;
	g_pRenderTarget = pRenderTarget;

	//ID2D1RenderTarget	*pRenderTarget = pRenderTarget->GetRenderTarget();
	D2D1_SIZE_F size = g_pRenderTarget->GetSize();

	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\nagaya1.png"), &g_pGround1.pImage);
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\nagaya2.png"), &g_pGround2.pImage);
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\nagaya3.png"), &g_pGround3.pImage);
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\nagaya4.png"), &g_pGround4.pImage);	
}

CGround::~CGround(void)
{
		SAFE_RELEASE(g_pGround1.pImage);
		SAFE_RELEASE(g_pGround2.pImage);
		SAFE_RELEASE(g_pGround3.pImage);
		SAFE_RELEASE(g_pGround4.pImage);
	
	SAFE_DELETE(g_pGroundImage);
}

bool CGround::move()
{
	SetRunspeed();

	D2D1_SIZE_F size = g_pRenderTarget->GetSize();

	for (int i = 0; i < 2; ++i) {
		g_Pos[i].x -= GameData::RunSpeed;
		if (g_Pos[i].x <= -size.width) {
			char k;
			if (i == 0) {
				k = 1;
			}
			else {
				k = 0;
			}
			g_Pos[i].x = g_Pos[k].x + size.width - GameData::RunSpeed;
		}
	}

	return GameSceneResultCode::GAMESCENE_DEFAULT;
}

void CGround::draw(ID2D1RenderTarget *pRenderTarget)
{
	D2D1_SIZE_F size = g_pRenderTarget->GetSize();

	D2D1_RECT_F rc;
	for (int i = 0; i < 2; ++i) {
		rc.left = g_Pos[i].x;
		rc.right = g_Pos[i].x + size.width;
		rc.top = g_Pos[i].y + 300.f;
		rc.bottom = g_Pos[i].y + size.height;

		switch (GameData::StagePhase) {
		case NOON:
			pRenderTarget->DrawBitmap(g_pGround1.pImage, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
			break;
		case TWILIGHT:
			pRenderTarget->DrawBitmap(g_pGround2.pImage, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
			break;
		case NIGHT:
			pRenderTarget->DrawBitmap(g_pGround3.pImage, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
			break;
		case BLOODMOON:
			pRenderTarget->DrawBitmap(g_pGround4.pImage, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
			break;
		}
	}

}

void CGround::SetRunspeed() {
	switch (GameData::StagePhase) {
	case NOON:
		break;
	case TWILIGHT:
		if (GameData::RunSpeed < 5.f) {
			GameData::RunSpeed += 0.1f;
			if (GameData::RunSpeed >= 5.f) {
				GameData::RunSpeed = 5.f;

			}
		}
		break;
	case NIGHT:
		if (GameData::RunSpeed < 8.f) {
			GameData::RunSpeed += 0.1f;
			if (GameData::RunSpeed >= 8.f) {
				GameData::RunSpeed = 8.f;
			}
		}
		break;
	case BLOODMOON:
		if (GameData::RunSpeed < 12.f) {
			GameData::RunSpeed += 0.1f;
			if (GameData::RunSpeed >= 12.f) {
				GameData::RunSpeed = 12.f;
			}
		}
		if (GameData::Score >= 50000) {
			if (GameData::RunSpeed < 18.f) {
				GameData::RunSpeed += 0.1f;
				if (GameData::RunSpeed >= 18.f) {
					GameData::RunSpeed = 18.f;
				}
			}

		}
		break;
	}
}