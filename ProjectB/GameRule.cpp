#include "stdafx.h"
#include <d2d1.h>
#include "GameRule.h"
#include "TextureLoader.h"

CGameRule::CGameRule(ID2D1RenderTarget *pRenderTarget)
{
	if (pRenderTarget) {
		CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\botan1.png"), &m_pLogo);
		CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\Rule1.png"), &m_pText);
		CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\botan2.png"), &m_pLogo2);
		CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\Rule2.png"), &m_pText2);
		pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f), &m_pBlack);
	}
	m_iFadeTimer = 0;
	m_fAlpha = 0.0f;
	m_iPhase = 0;
}

CGameRule::~CGameRule()
{
	SAFE_RELEASE(m_pLogo);
	SAFE_RELEASE(m_pText);
	SAFE_RELEASE(m_pLogo2);
	SAFE_RELEASE(m_pText2);
}

GameSceneResultCode CGameRule::move() {
	TextAlphaRun(30.0f);
	
	switch (m_ePhase) {
	case GAMERULE_INIT:
			if (GetAsyncKeyState(VK_RIGHT)) 
				m_ePhase = GAMERULE_FADE;
			if (GetAsyncKeyState(VK_SPACE))
				m_ePhase = GAMERULE_INIT;
		break;
	case GAMERULE_FADE:
			if (GetAsyncKeyState(VK_SPACE))
				m_ePhase = GAMERULE_FADE2;
			if (GetAsyncKeyState(VK_LEFT))
				m_ePhase = GAMERULE_INIT;
		break;
	case GAMERULE_FADE2:
		m_iFadeTimer++;
		if (m_iFadeTimer < 100)
			break;
		m_ePhase = GAMERULE_DONE;
	case GAMERULE_DONE:
		return GameSceneResultCode::GAMESCENE_END_OK;
		break;
	}
	return GameSceneResultCode::GAMESCENE_DEFAULT;
}

void CGameRule::draw(ID2D1RenderTarget *pRenderTarget)
{
	D2D1_SIZE_F		size = pRenderTarget->GetSize();
	D2D1_RECT_F rc;

	//	一枚目画像
	if (m_ePhase == GAMERULE_INIT) {
		rc.left = 0.0f;
		rc.right = size.width;
		rc.top = 0.0f;
		rc.bottom = size.height;
		pRenderTarget->DrawBitmap(m_pText, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);

		rc.left = size.width * 0.6f;
		rc.right = size.width * 0.98f;
		rc.top = size.height * 0.9f;
		rc.bottom = size.height * 0.98f;
		pRenderTarget->DrawBitmap(m_pLogo, rc, m_fAlpha, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
	}

	// 二枚目画像
	if (m_ePhase != GAMERULE_INIT) {
		rc.left = 0.0f;
		rc.right = size.width;
		rc.top = 0.0f;
		rc.bottom = size.height;
		pRenderTarget->DrawBitmap(m_pText2, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);

		rc.left = size.width * 0.6f;
		rc.right = size.width * 0.98f;
		rc.top = size.height * 0.9f;
		rc.bottom = size.height * 0.98f;
		pRenderTarget->DrawBitmap(m_pLogo2, rc, m_fAlpha, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
	}

	//	ブラックアウト
	if (m_ePhase == GAMERULE_FADE2) {
		rc.left = 0.0f;
		rc.right = size.width;
		rc.top = 0.0f;
		rc.bottom = size.height;
		m_pBlack->SetOpacity(m_iFadeTimer / 60.0f);
		pRenderTarget->FillRectangle(rc, m_pBlack);

	}
}

void	CGameRule::TextAlphaRun(float frame)
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