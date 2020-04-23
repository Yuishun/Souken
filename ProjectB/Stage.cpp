#include "stdafx.h"
#include <d2d1.h>
#include "Stage.h"
#include "TextureLoader.h"

#include "BG.h"
#include "EnemyManager.h"
#include "PlayerManager.h"
#include "UI.h"
#include "ItemManager.h"
#include "StarShot.h"
#include "GameData.h"


CStage::CStage(CSelector *pSystem)
{
	m_pSystem = pSystem;

	ID2D1RenderTarget *pTarget = pSystem->GetRenderTarget();

	m_pBG = new CBG(this);
	m_pEManager = new CEnemyManager(this);
	m_pPManager = new CPlayerManager(this);
	m_pUI = new CUI(this);
	m_pIManager = new CItemManager(this);
	m_pStarShot = new CStarShot(pTarget);
	directionPhase = 0;
	edge[0] = 0; edge[1] = 1920.f;
	CTextureLoader::CreateD2D1BitmapFromFile(pTarget, _T("res\\TitleBG.png"), &m_pOPDirection[0].pImage);
	CTextureLoader::CreateD2D1BitmapFromFile(pTarget, _T("res\\ResultBG.png"), &m_pEndDirection);
	m_pOPDirection[0].Pos = { 1920 * 0.5f, 1080 };
	m_pOPDirection[1].Pos = { 1920, 1080 };

	StateFlag = true;
}


CStage::~CStage()
{
	SAFE_DELETE(m_pBG);
	SAFE_DELETE(m_pEManager);
	SAFE_DELETE(m_pPManager);
	SAFE_DELETE(m_pUI);
	SAFE_DELETE(m_pIManager);
	SAFE_DELETE(m_pStarShot);
	SAFE_RELEASE(m_pOPDirection[0].pImage);
	SAFE_RELEASE(m_pEndDirection);
	CTextureLoader::Destroy();
}


/**
* @breaf move
**/
GameSceneResultCode CStage::move() {
	if (GameData::PlayerPhase == DIE)
		return GameSceneResultCode::GAMESCENE_END_OK;

	if (GameData::PlayerPhase < FADE && GameData::StarShot != 1) {

		SetStagePhase();

		if (m_pEManager)
			m_pEManager->move();

		if (m_pPManager)
			m_pPManager->move();

		if (m_pUI)
			m_pUI->move();

		if (m_pIManager)
			m_pIManager->move();

	}
	if (GameData::StarShot >= 1)
		m_pStarShot->move();

	return GameSceneResultCode::GAMESCENE_DEFAULT;
}

/**
* @breaf 描画
* @prame [in] レンダーターゲット
**/
void CStage::draw(ID2D1RenderTarget *pRenderTarget) {

	if (m_pBG)
		m_pBG->draw(pRenderTarget);

	if (m_pPManager)
		m_pPManager->draw(pRenderTarget);

	if (m_pEManager)
		m_pEManager->draw(pRenderTarget);

	if (GameData::StarShot >= 1)
		m_pStarShot->draw(pRenderTarget);

	if (m_pIManager)
		m_pIManager->draw(pRenderTarget);

	if (m_pUI)
		m_pUI->draw(pRenderTarget);

	if (StateFlag == true)
		GameState(pRenderTarget);

	if (GameData::PlayerPhase == FADE) {
		FADE_direction(pRenderTarget);
	}
}

ID2D1RenderTarget *CStage::GetRenderTarget()
{
	ID2D1RenderTarget *result = NULL;
	if (m_pSystem) {
		result = m_pSystem->GetRenderTarget();
	}
	return result;
}

void CStage::SetStagePhase() {
	switch(GameData::StagePhase) {
	case NOON:
		if (GameData::Score >= 1500) {
				GameData::StagePhase = TWILIGHT;
		}
		break;
	case TWILIGHT:
		if (GameData::Score >= 4000) {
				GameData::StagePhase = NIGHT;
		}
		break;
	case NIGHT:
		if (GameData::Score >= 7000) {
				GameData::StagePhase = BLOODMOON;
		}
		break;
	/*case BLOODMOON:
		if (GameData::Score >= 10000) {		スピード早くなるだけの物があってもいいかも
			GameData::StagePhase = NIGHTMARE;
		}
		break;*/
	}
}

/*******************
* @method	move
* @brief	OP用
*******************/
void CStage::GameState(ID2D1RenderTarget *pRenderTarget)
{
	D2D1_SIZE_F size = pRenderTarget->GetSize();
	D2D1_RECT_F rc, rc2, src;
	rc.left = m_pOPDirection[0].Pos.x - 960;
	rc.right = m_pOPDirection[0].Pos.x;
	rc.top = 0.f;
	rc.bottom = m_pOPDirection[0].Pos.y;
	src.left = 0.f;
	src.right = size.width * 0.5f;
	src.top = 0.f;
	src.bottom = m_pOPDirection[0].Pos.y;
	pRenderTarget->DrawBitmap(m_pOPDirection[0].pImage, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);

	rc2.left = m_pOPDirection[1].Pos.x - 960;
	rc2.right = m_pOPDirection[1].Pos.x;
	rc2.top = 0.f;
	rc2.bottom = m_pOPDirection[1].Pos.y;
	src.left = size.width * 0.5f;
	src.right = size.width;
	src.top = 0.f;
	src.bottom = m_pOPDirection[1].Pos.y;
	pRenderTarget->DrawBitmap(m_pOPDirection[0].pImage, rc2, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);

	if (rc.left >= -m_pOPDirection[1].Pos.x) {
		m_pOPDirection[0].Pos.x -= 10.0f;
		m_pOPDirection[1].Pos.x += 10.0f;
	}
	else {
		StateFlag = false;
	}
}

void CStage::FADE_direction(ID2D1RenderTarget *pRenderTarget) {
	D2D1_RECT_F rc, src, rc2;
	rc.top = 0;
	rc.bottom = 1080.f;
	rc2.top = 0;
	rc2.bottom = 1080.f;
	src.top = 0;
	src.bottom = 1080.f;
	if (directionPhase <= 3) {
		float plus;
		switch (directionPhase) {
		case 0:
			plus = 0;
			break;
		case 1:
			plus = 14.f;
			break;
		case 2:
			plus = 0.1f;
		case 3:
			plus = 1.f;
			break;
		}
		edge[0] += plus;
		edge[1] -= plus;
		switch(directionPhase) {
		case 0:
			directionPhase = 1;
			break;
		case 1:
			if (edge[0] >= 900.f && edge[1] <= 1020.f) {
				edge[0] = 900.f;
				edge[1] = 1020.f;
				directionPhase = 2;
			}
			break;
		case 2:
			if (edge[0] >= 903.f && edge[1] <= 1017.f) {
				edge[0] = 903.f;
				edge[1] = 1017.f;
				directionPhase = 3;
			}
			break;
		case 3:
			if (edge[0] >= 960.f && edge[1] <= 960.f) {
				edge[0] = 960.f;
				edge[1] = 960.f;
				directionPhase = 4;
			}
			break;
		}
		rc.right = edge[0];
		rc.left = rc.right - 960.f;
		rc2.left = edge[1];
		rc2.right = rc2.left + 960.f;

			src.left = 0;
			src.right = 960.f;
			pRenderTarget->DrawBitmap(m_pEndDirection, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);

			src.left = 960.f;
			src.right = 1920.f;
			pRenderTarget->DrawBitmap(m_pEndDirection, rc2, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);
	}
	if (directionPhase >= 4) {
		rc.left = 0;
		rc.right = 1920.f;
		src.left = 0;
		src.right = 1920.f;
		pRenderTarget->DrawBitmap(m_pEndDirection, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);
		if (++directionPhase >= 65)
			GameData::PlayerPhase = DIE;
	}
}