#pragma once

#ifndef __IGAMEOBJECT_H__
#include "IGameObject.h"
#endif

class CStage;

class CGround;
class CPlayer;
class CShadowPlayer;
class CShot;
class CPlayerManager
{
public:
	CPlayerManager(CStage *pStage);
	virtual ~CPlayerManager();
	virtual bool move() ;
	virtual void draw(ID2D1RenderTarget *pRenderTarget);

protected:
	CStage			*m_pStage;

	CGround			*m_pGround;
	CPlayer			*m_pPlayer;
	CShadowPlayer	*m_pS_Player;
	CShot			*m_pShot;

};

