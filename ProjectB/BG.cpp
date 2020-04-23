/**
* @file		BG.cpp
* @brief	îwåi
* @author	yshimada
* @data		20190820
**/
#include "stdafx.h"
#include <d2d1.h>
#include "BG.h"
#include "TextureLoader.h"
#include "GameData.h"

CBG::CBG(CStage *pStage)
{
	g_pBGImage = NULL;
	g_pBG = pStage;

	ID2D1RenderTarget	*pTarget = pStage->GetRenderTarget();

	CTextureLoader::CreateD2D1BitmapFromFile(pTarget, _T("res\\BG1.png"), &g_pBG1.pImage);
	CTextureLoader::CreateD2D1BitmapFromFile(pTarget, _T("res\\BG2.png"), &g_pBG2.pImage);
	CTextureLoader::CreateD2D1BitmapFromFile(pTarget, _T("res\\BG3.png"), &g_pBG3.pImage);
	CTextureLoader::CreateD2D1BitmapFromFile(pTarget, _T("res\\BG4.png"), &g_pBG4.pImage);
	g_pBG1.Pos = { 0.0f,0.0f };
}


CBG::~CBG()
{
	SAFE_RELEASE(g_pBG1.pImage);
	SAFE_RELEASE(g_pBG2.pImage);
	SAFE_RELEASE(g_pBG3.pImage);
	SAFE_RELEASE(g_pBG4.pImage);

	SAFE_DELETE(g_pBGImage);
}

BOOL CBG::move() {
	return true;
}

void CBG::draw(ID2D1RenderTarget *pRenderTarget)
{
	D2D1_SIZE_F size = pRenderTarget->GetSize();
	D2D1_RECT_F rc;


	rc.left = g_pBG1.Pos.x;
	rc.right = g_pBG1.Pos.x + size.width;
	rc.top = g_pBG1.Pos.y;
	rc.bottom = 310.f;
	switch (GameData::StagePhase) {
	case NOON:
		pRenderTarget->DrawBitmap(g_pBG1.pImage, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
		break;
	case TWILIGHT:
		pRenderTarget->DrawBitmap(g_pBG2.pImage, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
		break;
	case NIGHT:
		pRenderTarget->DrawBitmap(g_pBG3.pImage, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
		break;
	case BLOODMOON:
		pRenderTarget->DrawBitmap(g_pBG4.pImage, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
		break;
	}
}
