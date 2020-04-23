#pragma once

#include "Stage.h"

struct ID2D1RenderTarget;
struct ID2D1Bitmap;
class CStage;

class CBG
{
public:
	CBG(CStage *pStage);
	virtual ~CBG();
	virtual BOOL move();
	virtual void draw(ID2D1RenderTarget *pRenderTarget);
protected:
	CStage		*g_pBG;
	ID2D1Bitmap *g_pBGImage;
	ID2D1RenderTarget *g_pRenderTarget;
private:
	typedef struct {
		float x;
		float y;
	}Vector2D;

	typedef struct {
		ID2D1Bitmap *pImage;
		Vector2D	Pos;
	}BGState;

	BGState g_pBG1;
	BGState g_pBG2;
	BGState g_pBG3;
	BGState g_pBG4;

	Vector2D g_Pos;

	HRESULT rc;
};

