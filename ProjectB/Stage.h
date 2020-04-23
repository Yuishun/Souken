#pragma once

#include "Selector.h"
#ifndef __IGAMESCENE_H__
#include "IGameScene.h"
#endif

#ifndef __IGAMEOBJECT_H__
#include "IGameObject.h"
#endif

//class CSelector;
class CBG;
class CEnemyManager;
class CPlayerManager;
class CUI;
class CItemManager;
class CStarShot;
/**
* @brief ゲーム本体を動かす部分
*/
class CStage :
	public IGameScene
{
public:
	CStage(CSelector *pSystem);
	virtual ~CStage(void);
	virtual GameSceneResultCode move() override;	//	シーンのアニメート
	virtual void draw(ID2D1RenderTarget *pRenderTarget) override;	//	シーンの描画

	ID2D1RenderTarget *GetRenderTarget();
protected:
	void SetStagePhase();		//状態遷移
	CSelector		*m_pSystem;
	CPlayerManager	*m_pPManager;
	CBG				*m_pBG;
	CUI				*m_pUI;
	CEnemyManager	*m_pEManager;
	CItemManager	*m_pIManager;
	CStarShot		*m_pStarShot;
	typedef struct {
		float x;
		float y;
	}Vector2D;
	typedef struct {
		ID2D1Bitmap *pImage;
		Vector2D	Pos;
	}GState;
	GState			m_pOPDirection[2];
	ID2D1Bitmap		*m_pEndDirection;
	void GameState(ID2D1RenderTarget *pRenderTarget);
	void FADE_direction(ID2D1RenderTarget *pRenderTarget);
	unsigned char directionPhase;
	float edge[2];
	bool StateFlag;
};

