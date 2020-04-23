#include "stdafx.h"
#include <d2d1.h>
#include "TextureLoader.h"
#include "Stage.h"
#include "UI.h"
#include "HPUI.h"
#include "PurpleUI.h"
#include "StarUI.h"
#include "GameData.h"

#define Score_width 75.f

CUI::CUI(CStage *pStage)
{
	 m_pStage= pStage;

	
	ID2D1RenderTarget *pTarget = pStage->GetRenderTarget();

	CTextureLoader::CreateD2D1BitmapFromFile(pTarget, _T("res\\number.png"), &ScoreUI);
	m_pHP = new CHPUI(pTarget);
	m_pPurple = new CPurpleUI(pTarget);
	m_pStar = new CStarUI(pTarget);
}


CUI::~CUI()
{
	SAFE_DELETE(m_pHP);
	SAFE_DELETE(m_pPurple);
	SAFE_DELETE(m_pStar);
	SAFE_RELEASE(ScoreUI);
}

GameSceneResultCode CUI::move() {
	if (m_pHP)
		m_pHP->move();
	if (m_pPurple)
		m_pPurple->move();
	if (m_pStar)
		m_pStar->move();
	
	return GameSceneResultCode::GAMESCENE_DEFAULT;
}

void CUI::draw(ID2D1RenderTarget *pRenderTarget) {
	if (m_pHP)
		m_pHP->draw(pRenderTarget);
	if (m_pPurple)
		m_pPurple->draw(pRenderTarget);
	if (m_pStar)
		m_pStar->draw(pRenderTarget);

	D2D1_RECT_F rc , src;
	rc.right = 1920;
	rc.left = rc.right - Score_width;
	rc.top = 0;
	rc.bottom = 75;
	src.top = 0;
	src.bottom = 75;
	score = GameData::Score;
	unsigned char digit = 0;
	while (score != 0) {
		score /= 10;
		digit++;
	}
	score = GameData::Score;
	for (int i = 0; i < digit; ++i) {
		char num = score % 10;
		src.left = num * Score_width;
		src.right = src.left + Score_width;
		pRenderTarget->DrawBitmap(ScoreUI, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);
		score /= 10;
		rc.left -= Score_width;
		rc.right -= Score_width;
	}

}