#pragma once

#include "Selector.h"
#include "IGameObject.h"

#define Shotspeed 20.0f
struct ID2D1Bitmap;
struct ID2D1Rendertarget;
class CShot	: public IGameObject
{
public:
	CShot(ID2D1RenderTarget *pRenderTarget);
	virtual ~CShot();
	virtual bool move() override;
	virtual void draw(ID2D1RenderTarget *pRenderTarget) override;
protected:
	ID2D1Bitmap			*g_pShotImage;
	ID2D1RenderTarget	*g_pRenderTarget;

};

