#include "stdafx.h"
#include <d2d1.h>
#include "PurpleUI.h"
#include "TextureLoader.h"
#include "GameData.h"

#define Purple_Width 150.f

CPurpleUI::CPurpleUI(ID2D1RenderTarget *pRenderTarget)
{
	m_pPurplegauge = NULL;
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\ui2.png"), &m_pPurplegauge);

	rc = {0,0,Purple_Width,150};
	src = {0,0,Purple_Width,150};
	Time = 0;
}


CPurpleUI::~CPurpleUI()
{
	SAFE_RELEASE(m_pPurplegauge);

}

bool CPurpleUI::move() {
	if (GameData::PurpleTime == true) {
		Time = (Time + 1) % (PurpleTimelimit / 2);
		if ( Time == 0 ) {
			GameData::Purplegauge -= 1;
			if (GameData::Purplegauge <= 0) {
				GameData::PurpleTime = false;
				Time = 0;
			}
		}
	}


	src.left = Purple_Width * GameData::Purplegauge;
	src.right = src.left + Purple_Width;
	return GameSceneResultCode::GAMESCENE_DEFAULT;
}

void CPurpleUI::draw(ID2D1RenderTarget *pRenderTarget) {

	pRenderTarget->DrawBitmap(m_pPurplegauge, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);

}