#include "stdafx.h"
#include <d2d1.h>
#include "StarUI.h"
#include "TextureLoader.h"
#include "GameData.h"

#define Star_Width 150.f

CStarUI::CStarUI(ID2D1RenderTarget *pRenderTarget)
{
	m_pStargauge = NULL;
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\ui3.png"), &m_pStargauge);

	rc.left = 150;
	rc.right = rc.left + Star_Width;
	rc.top = 0;
	rc.bottom = 150;
	src = {0,0,Star_Width,150};
}


CStarUI::~CStarUI()
{
	SAFE_RELEASE(m_pStargauge);
}

bool CStarUI::move() {
	src.left = Star_Width * GameData::Stargauge;
	src.right = src.left + Star_Width;
	return	GameSceneResultCode::GAMESCENE_DEFAULT;
}

void CStarUI::draw(ID2D1RenderTarget *pRenderTarget) {

	pRenderTarget->DrawBitmap(m_pStargauge, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);

}