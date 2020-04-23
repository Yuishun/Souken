#pragma once

#include "IGameScene.h"
#include "Selector.h"

enum GameOverPhase {
	GAMEOVER_INIT = 0,
	GAMEOVER_RANK = 1,
	GAMEOVER_FADE = 2,
	GAMEOVER_DONE = 3
};



struct ID2D1Bitmap;
class CScore;
class CGameOver :public IGameScene
{
public:
	CGameOver(ID2D1RenderTarget *pRenderTarget);
	virtual ~CGameOver();
	virtual GameSceneResultCode move() override;
	virtual void draw(ID2D1RenderTarget *pRenderTarget) override;
private:
	void	TextAlphaRun(float frame);

	ID2D1Bitmap		*m_pText;
	ID2D1Bitmap		*m_pLogo;
	ID2D1Bitmap		*m_pLogo2;
	ID2D1SolidColorBrush	*m_pBlack;
	GameOverPhase		m_ePhase;
	CScore			*m_pScore;
	float	m_fAlpha;
	int		m_iPhase;
	int		m_iFadeTimer;		//!	Fadetimer
	bool	FadeFlag;
	bool	KeyFlag;
};

