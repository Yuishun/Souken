#pragma once

#include "IGameObject.h"
#include "Selector.h"

#define PurpleTimelimit 720
struct ID2D1Bitmap;
class CPurpleUI :
	public IGameObject
{
public:
	CPurpleUI(ID2D1RenderTarget *pRenderTarget);
	virtual ~CPurpleUI();
	virtual bool move() override;
	virtual void draw(ID2D1RenderTarget *pRenderTarget) override;
protected:
	ID2D1Bitmap *m_pPurplegauge;
	D2D1_RECT_F rc, src;
	USHORT Time;
};

