#pragma once

#include "IGameScene.h"
#include "Selector.h"

enum TitlePhase {
	TITLE_INIT = 0,
	TITLE_FADE = 1,
	TITLE_FADE2 = 2,
	TITLE_DONE = 3
};

struct ID2D1Bitmap;
class CTitle :public IGameScene
{
public:
	CTitle(ID2D1RenderTarget *pRenderTaregt);
	virtual ~CTitle();
	virtual GameSceneResultCode move() override;
	virtual void draw(ID2D1RenderTarget *pRenderTarget) override;
private:
	typedef struct {
		float x;
		float y;
	}Vector2D;
	typedef struct {
		ID2D1Bitmap *pImage;
		Vector2D Pos;
	}TState;
	void	TextAlphaRun(float frame);
	ID2D1Bitmap *m_pLogo;	//! TitleLogoImage
	ID2D1Bitmap *m_pText;	//! TitleTextImage
	ID2D1Bitmap *m_pText2;	//! TitleTextImage
	ID2D1SolidColorBrush	*m_pBlack;
	TState	g_pText;
	Vector2D	g_Pos;
	TitlePhase		m_ePhase;
	int				FadeFlag;
	float			m_fAlpha;		//! spacemove　に使用
	int				m_iPhase;
	int				m_iFadeTimer;	//!	BlackFadeに使用
	int				m_iFadeTimer2;	//!	GameFadeに使用
	float			TextY;
	float			TextY2;
};

