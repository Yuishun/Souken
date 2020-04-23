#pragma once

#include "IGameScene.h"
#include "Selector.h"

struct ID2D1Bitmap;
class CHPUI :
	public IGameScene
{
public:
	CHPUI(ID2D1RenderTarget *pRenderTarget);
	virtual ~CHPUI();
	virtual GameSceneResultCode move() override;
	virtual void draw(ID2D1RenderTarget *pRenderTarget) override;
protected:
	ID2D1Bitmap *m_pHPgauge;
	ID2D1Bitmap *m_pHPFrame;
	D2D1_RECT_F rc, src, rc2, src2;
};

