#include "stdafx.h"
#include <d2d1.h>
#include "Title.h"
#include "SoundManager.h"
#include "TextureLoader.h"

#define SAFE_RELEASE(o) if(o) { (o)->Release(); o = NULL; };

/**
* @brief	コンストラクタ
* @param	[in]	pRenderTarget	レンダーターゲット
**/
CTitle::CTitle(ID2D1RenderTarget *pRenderTarget)
{
	D2D1_SIZE_F size = pRenderTarget->GetSize();

	if (pRenderTarget) {
		CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\TitleBG.png"), &m_pLogo);
		CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\start.png"), &m_pText);
		CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\Rule.png"), &m_pText2);
		CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\ohuda.png"), &g_pText.pImage);
		CSoundManager::LoadOneShot(_T("res/oneshot.wav"));
		pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f), &m_pBlack);
	}
	g_pText.Pos = { size.width * 0.22f,size.height * 0.65f };

	m_iFadeTimer = 0;
	m_iFadeTimer2 = 60;
	m_fAlpha = 1.0f;
	m_iPhase = 0;
	FadeFlag = 0;
	TextY = size.height * 0.65f;
	TextY2 = size.height * 0.8f;
}

/**
* @brief	デストラクタ
* @param	[in]	pRenderTarget	レンダーターゲット
**/
CTitle::~CTitle()
{
	SAFE_RELEASE(m_pLogo);
	SAFE_RELEASE(m_pText);
	SAFE_RELEASE(m_pText2);
}


GameSceneResultCode CTitle::move() {
	TextAlphaRun(30.0f);
	if (g_pText.Pos.y != TextY) {
		if (GetAsyncKeyState(VK_UP))
			g_pText.Pos.y = TextY;
	}
	if (g_pText.Pos.y == TextY) {
		if (GetAsyncKeyState(VK_DOWN))
			g_pText.Pos.y = TextY2;
	}

	switch (m_ePhase) {
	case TITLE_INIT:
		if (GetAsyncKeyState(VK_SPACE)) {
			CSoundManager::PlayOneShot(0, 3.0f);
			if (g_pText.Pos.y == TextY) {
				m_ePhase = TITLE_FADE2;
				FadeFlag = 1;
			}
			else {
				m_ePhase = TITLE_FADE;
				FadeFlag = 2;
			}
		}
		break;
	case TITLE_FADE:
		m_iFadeTimer++;
		if (m_iFadeTimer < 60)
			break;
		m_ePhase = TITLE_DONE;
	case TITLE_FADE2:
		m_iFadeTimer2--;
		if (m_iFadeTimer2 > 0)
			break;
		m_ePhase = TITLE_DONE;
	case TITLE_DONE:
		if (g_pText.Pos.y == TextY) {
			return GameSceneResultCode::GAMESCENE_END_OK;
		}
		else {
			return GameSceneResultCode::GAMEPHASE_END_TIMEOUT;
		}
		break;
	}
	return GameSceneResultCode::GAMESCENE_DEFAULT;
}

/**
* @breaf	描画
* @prame	[in]	pRenderTarget	レンダーターゲット
**/
void CTitle::draw(ID2D1RenderTarget *pRenderTarget)
{
	D2D1_SIZE_F size = pRenderTarget->GetSize();
	D2D1_RECT_F rc, src;
	rc.left = 0.0f;
	rc.right = size.width;
	rc.top = 0.0f;
	rc.bottom = size.height;
	pRenderTarget->DrawBitmap(m_pLogo, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);

	rc.left = size.width * 0.3f;
	rc.right = size.width * 0.7f;
	rc.top = size.height * 0.65f;
	rc.bottom = size.height * 0.75f;
	if (FadeFlag != 1) {
		if (rc.top == g_pText.Pos.y) {
			pRenderTarget->DrawBitmap(m_pText, rc, m_fAlpha, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
		}
		else {
			pRenderTarget->DrawBitmap(m_pText, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
		}
	}
	if (FadeFlag == 1)
		pRenderTarget->DrawBitmap(m_pText, rc, m_iFadeTimer2 / 60.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);

	rc.left = size.width * 0.3f;
	rc.right = size.width * 0.7f;
	rc.top = size.height * 0.8f;
	rc.bottom = size.height * 0.9f;
	if (FadeFlag != 1) {
		if (rc.top == g_pText.Pos.y) {
			pRenderTarget->DrawBitmap(m_pText2, rc, m_fAlpha, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
		}
		else {
			pRenderTarget->DrawBitmap(m_pText2, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
		}
	}
	if (FadeFlag == 1)
		pRenderTarget->DrawBitmap(m_pText2, rc, m_iFadeTimer2 / 60.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);

	rc.left = g_pText.Pos.x;
	rc.right = g_pText.Pos.x + 100.0f;
	rc.top = g_pText.Pos.y;
	rc.bottom = g_pText.Pos.y + 100.0f;
	src.left = 200.0f;
	src.right = 300.0f;
	src.top = 0.0f;
	src.bottom = 100.0f;
	pRenderTarget->DrawBitmap(g_pText.pImage, rc, m_iFadeTimer2 / 60.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);


	if (FadeFlag == 2) {
		rc.left = 0.0f;
		rc.right = size.width;
		rc.top = 0.0f;
		rc.bottom = size.height;
		m_pBlack->SetOpacity(m_iFadeTimer / 60.0f);
		pRenderTarget->FillRectangle(rc, m_pBlack);
	}
}

/**
* @brief	タイトルのテキストの点滅処理
* @param	[in]	frame	何フレームで点滅するか
*/
void	CTitle::TextAlphaRun(float frame)
{
	float AlphaAdd = 0.5f / (frame * 0.5f);

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