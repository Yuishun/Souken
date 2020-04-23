#include "stdafx.h"
#include <d2d1.h>
#include "PlayerManager.h"
#include "Stage.h"

#include "Ground.h"
#include "Player.h"
#include "ShadowPlayer.h"
#include "Shot.h"


CPlayerManager::CPlayerManager(CStage *pStage)
{
	m_pStage = pStage;

	ID2D1RenderTarget *pTarget = pStage->GetRenderTarget();

	m_pGround = new CGround(pTarget);
	m_pPlayer = new CPlayer(pTarget);
	m_pS_Player = new CShadowPlayer(pTarget,m_pPlayer);
	m_pShot = new CShot(pTarget);
}


CPlayerManager::~CPlayerManager()
{
	SAFE_DELETE(m_pGround);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pS_Player);
	SAFE_DELETE(m_pShot);
}

bool CPlayerManager::move()
{
	if (m_pGround)
		m_pGround->move();

	if (m_pShot)
		m_pShot->move();

	if (m_pPlayer)
		m_pPlayer->move();

	return GameSceneResultCode::GAMESCENE_DEFAULT;
}

void CPlayerManager:: draw(ID2D1RenderTarget *pRenderTarget)
{
	if (m_pGround)
		m_pGround->draw(pRenderTarget);

	if (m_pShot)
		m_pShot->draw(pRenderTarget);

	if (m_pS_Player)
		m_pS_Player->draw(pRenderTarget);

	if (m_pPlayer)
		m_pPlayer->draw(pRenderTarget);

}
