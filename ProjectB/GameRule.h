#pragma once

#include "IGameScene.h"
#include "Selector.h"

enum GameRulePhase {
	GAMERULE_INIT  = 0,
	GAMERULE_FADE  = 1,
	GAMERULE_FADE2 = 2,
	GAMERULE_DONE  = 3
};

struct ID2D1RenderTarget;
class CGameRule :public IGameScene
{
public:
	CGameRule(ID2D1RenderTarget *pRenderTarget);
	virtual ~CGameRule();
	virtual GameSceneResultCode move() override;
	virtual void draw(ID2D1RenderTarget *pRenderTarget) override;
private:
	void	TextAlphaRun(float frame);

	ID2D1Bitmap *m_pLogo;	//! TitleLogoImage
	ID2D1Bitmap *m_pText;	//! TitleTextImage
	ID2D1Bitmap *m_pLogo2;	//! TitleLogoImage2
	ID2D1Bitmap *m_pText2;	//! TitleTextImage2
	ID2D1SolidColorBrush	*m_pBlack;
	GameRulePhase	m_ePhase;
	float	m_fAlpha;		// spacemoveÅ@Ç…égóp
	int		m_iPhase;
	int		m_iFadeTimer;	//! Fadetimer
};

