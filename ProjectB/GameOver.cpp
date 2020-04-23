#include "stdafx.h"
#include <d2d1.h>
#include "GameOver.h"
#include "TextureLoader.h"
#include "Score.h"

CGameOver::CGameOver(ID2D1RenderTarget *pRenderTarget)
{
	if (pRenderTarget) {
		CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\ResultBG.png"), &m_pText);
		CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\botan2.png"), &m_pLogo);
		CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\gameover.png"), &m_pLogo2);
		pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f), &m_pBlack);
		m_pScore = new CScore(pRenderTarget);
	}
	m_iFadeTimer = 0;
	m_fAlpha = 0.0f;
	m_iPhase = 0;
	FadeFlag = false;
	KeyFlag = true;
}

CGameOver::~CGameOver()
{
	SAFE_RELEASE(m_pText);
	SAFE_RELEASE(m_pLogo);
	SAFE_RELEASE(m_pLogo2);
	SAFE_DELETE(m_pScore);
}

GameSceneResultCode CGameOver::move() {
	TextAlphaRun(30.0f);
	switch (m_ePhase) {
	case GAMEOVER_INIT:
		if (GetAsyncKeyState(VK_SPACE) && !KeyFlag) {
			m_ePhase = GAMEOVER_RANK;
			KeyFlag = true;
		}
		else if(!GetAsyncKeyState(VK_SPACE)){ KeyFlag = false; }
		break;
	case GAMEOVER_RANK:
		if (GetAsyncKeyState(VK_SPACE) && !KeyFlag) {
			FadeFlag = true;
			m_ePhase = GAMEOVER_FADE;
		}
		else if(!GetAsyncKeyState(VK_SPACE)){ KeyFlag = false; }
		break;
	case GAMEOVER_FADE:
		m_iFadeTimer++;
		if (m_iFadeTimer < 60)
			break;
		m_ePhase = GAMEOVER_DONE;
	case GAMEOVER_DONE:
		return GameSceneResultCode::GAMESCENE_END_OK;
		break;
	}
	return GameSceneResultCode::GAMESCENE_DEFAULT;
}

void CGameOver::draw(ID2D1RenderTarget *pRenderTarget)
{
	D2D1_SIZE_F		size = pRenderTarget->GetSize();
	D2D1_RECT_F rc;
	rc.left = 0.0f;
	rc.right = size.width;
	rc.top = 0.0f;
	rc.bottom = size.height;
	pRenderTarget->DrawBitmap(m_pText, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);

	rc.left = size.width * 0.25f;
	rc.right = size.width * 0.75f;
	rc.top = 68.f;
	rc.bottom = rc.top + 102.f;
	pRenderTarget->DrawBitmap(m_pLogo2, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);

	rc.left = size.width * 0.5f;
	rc.right = size.width;
	rc.top = size.height * 0.85f;
	rc.bottom = size.height;
	pRenderTarget->DrawBitmap(m_pLogo, rc, m_fAlpha, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);

	switch (m_ePhase) {
	case GAMEOVER_INIT:
		m_pScore->draw(pRenderTarget);
		break;
	case GAMEOVER_RANK:
		m_pScore->Ranikngdraw(pRenderTarget);
		break;
	}

	if(FadeFlag == true){
		rc.left = 0.0f;
		rc.right = size.width;
		rc.top = 0.0f;
		rc.bottom = size.height;
		m_pBlack->SetOpacity(m_iFadeTimer / 60.0f);
		pRenderTarget->FillRectangle(rc, m_pBlack);
	}
}

void	CGameOver::TextAlphaRun(float frame)
{
	float AlphaAdd = 0.5f / (frame * 0.5);

	switch (m_iPhase) {
	case 0:
		if (m_fAlpha < 1.0f)
			m_fAlpha += AlphaAdd;
		else
			m_iPhase = 1;
		break;
	case 1:
		if (m_fAlpha > 0.0f)
			m_fAlpha -= AlphaAdd;
		else
			m_iPhase = 0;
		break;
	}
}