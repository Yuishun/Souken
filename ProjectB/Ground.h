#pragma once

#include "IGameObject.h"
#include "Selector.h"

struct ID2D1RenderTarget;
struct ID2D1Bitmap;
class CGround : public IGameObject
{
public:
	CGround(ID2D1RenderTarget *pRenderTarget);
	virtual ~CGround();
	virtual bool move();
	virtual void draw(ID2D1RenderTarget *pRenderTarget);
	void SetRunspeed();
private:
	ID2D1Bitmap			*g_pGroundImage;
	ID2D1RenderTarget	*g_pRenderTarget;

	typedef struct {
		float x;
		float y;
	}Vector2D;
	Vector2D g_Pos[2];

	typedef struct {
		ID2D1Bitmap *pImage;
	}GroundState;
	GroundState g_pGround1;
	GroundState g_pGround2;
	GroundState g_pGround3;
	GroundState g_pGround4;
	

	HRESULT hr;
};

