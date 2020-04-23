#pragma once

#include "Selector.h"
#include "IGameObject.h"

struct ID2D1Bitmap;
class CStarUI :
	public IGameObject
{
public:
	CStarUI(ID2D1RenderTarget *pRenderTarget);
	virtual ~CStarUI();
	virtual bool move() override;
	virtual void draw(ID2D1RenderTarget *pRenderTarget) override;
protected:
	ID2D1Bitmap *m_pStargauge;
	D2D1_RECT_F rc, src;

};