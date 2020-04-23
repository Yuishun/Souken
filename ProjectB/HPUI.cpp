#include "stdafx.h"
#include <d2d1.h>
#include "HPUI.h"
#include "TextureLoader.h"
#include "GameData.h"

#define HPWidth 930
#define HPGaugeWidth 772

CHPUI::CHPUI(ID2D1RenderTarget *pRenderTarget)
{
	m_pHPgauge = NULL;
	m_pHPFrame = NULL;
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\HP2.png"), &m_pHPgauge);
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\ui1.png"), &m_pHPFrame);

	rc.left = 300;
	rc.right = rc.left + HPWidth;
	rc.top = 0;
	rc.bottom = 128;
	//rc2 = { rc.left+141,13.5f,rc.right,102.5f };
	rc2.right = rc.right-5.f;
	rc2.left = rc2.right-HPGaugeWidth;
	rc2.top = 5.f;
	rc2.bottom = rc2.top + 130;
	src = { 0,0,HPWidth,130 };
	src2 = { 0,0,HPGaugeWidth,140 };
	
}

CHPUI::~CHPUI()
{
	SAFE_RELEASE(m_pHPgauge);
	SAFE_RELEASE(m_pHPFrame);
}

GameSceneResultCode CHPUI::move() {
	float rightset = --GameData::PlayerHP;
	rightset /= PHP_NUM;
	rc2.right = rc2.left + ( rightset* HPGaugeWidth);
	src2.right = rightset * HPGaugeWidth;
	return GameSceneResultCode::GAMESCENE_DEFAULT;
}

void CHPUI::draw(ID2D1RenderTarget *pRenderTarget) {
	pRenderTarget->DrawBitmap(m_pHPFrame, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);
	pRenderTarget->DrawBitmap(m_pHPgauge, rc2, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src2);
}