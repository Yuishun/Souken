#include "stdafx.h"
#include <d2d1.h>
#include "ProjectB.h"
#include "Selector.h"
#include "TextureLoader.h"
#include "Title.h"
#include "GameRule.h"
#include "Stage.h"
#include "GameOver.h"
#include "GameData.h"
#include "SoundManager.h"

//	コンストラクタ
CSelector::CSelector(ID2D1RenderTarget *pRenderTareget)
{
	m_pRenderTarget = pRenderTareget;
	m_pScene = NULL;
	m_ePhase = GamePhase::GAMEPHASE_INIT;

	CSoundManager::LoadStreamSound(_T("res/GameBGM.wav"), true);
	CSoundManager::LoadStreamSound(_T("res/TitleBGM.wav"), true);
	CSoundManager::LoadOneShot(_T("res/oneshot.wav"));
}

//	デストラクタ
CSelector::~CSelector(void)
{
	CSoundManager::Finalize();
	SAFE_DELETE(m_pScene);
}

/**
* @breaf	状態遷移
* @param	[in]	pRenderTarget	レンダーターゲット
**/
void CSelector::doAnim()
{
	GameSceneResultCode rc = GAMESCENE_DEFAULT;

	switch (m_ePhase) {
	case	GAMEPHASE_INIT:
		m_ePhase = GAMEPHASE_RESET;
	case	GAMEPHASE_RESET:
		GameData::Reset();
		SAFE_DELETE(m_pScene);
		CSoundManager::DoneStreamSound(0);
		m_pScene = new CTitle(m_pRenderTarget);
		CSoundManager::PlayStreamSound(1, 0.5f);
		m_ePhase = GAMEPHASE_TITLE;
	case	GAMEPHASE_TITLE:
		if (m_pScene != NULL)
			rc = m_pScene->move();
		if (rc == GAMESCENE_DEFAULT)
			break;
		SAFE_DELETE(m_pScene);
		if (rc == GAMESCENE_END_OK) {
			CSoundManager::DoneStreamSound(1);
			m_pScene = new CStage(this);
			CSoundManager::PlayStreamSound(0, 0.5f);
			m_ePhase = GAMEPHASE_GAME;
		}
		if (rc == GAMEPHASE_END_TIMEOUT) {
			m_pScene = new CGameRule(m_pRenderTarget);
			m_ePhase = GAMEPHASE_GAMERULE;
		}
	case	GAMEPHASE_GAMERULE:
		if (m_pScene != NULL)
			rc = m_pScene->move();
		if (rc == GAMESCENE_DEFAULT)
			break;
		SAFE_DELETE(m_pScene);
		m_pScene = new CTitle(m_pRenderTarget);
		m_ePhase = GAMEPHASE_TITLE;
	case	GAMEPHASE_GAME:
		if (m_pScene != NULL)
			rc = m_pScene->move();
		if (rc == GAMESCENE_DEFAULT)
			break;
		SAFE_DELETE(m_pScene);
		CSoundManager::DoneStreamSound(0);
		m_pScene = new CGameOver(m_pRenderTarget);
		CSoundManager::PlayStreamSound(1, 0.5f);
		m_ePhase = GAMEPHASE_GAMEOVER;
	case	GAMEPHASE_GAMEOVER:
		if (m_pScene != NULL)
			rc = m_pScene->move();
		if (rc == GAMESCENE_DEFAULT)
			break;
		m_ePhase = GAMEPHASE_RESET;
	}

	if (GetAsyncKeyState(VK_F1)) {
		CSoundManager::DoneStreamSound(0);
		CSoundManager::DoneStreamSound(1);
	}
	if (GetAsyncKeyState(VK_F2)) {
		CSoundManager::PlayStreamSound(0, 0.5);
	}

}

/**
* @breaf	描画
* @param	[in]	pRenderTarget	レンダーターゲット
**/
void CSelector::doDraw(ID2D1RenderTarget *pRenderTarget)
{
	if (m_pScene)
		m_pScene->draw(pRenderTarget);
}

/**
* @brief ゲーム画面用のRenderTargetを返す
* @note  このメソッドが返した ID2D1RenderTarget はResult すること
**/
ID2D1RenderTarget *CSelector::GetRenderTarget() {
	m_pRenderTarget->AddRef();
	return m_pRenderTarget;
}