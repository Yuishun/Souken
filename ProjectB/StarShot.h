#pragma once

#include "IGameObject.h"
#include "Selector.h"

#define StarShot_width 300
#define BackStar_width 900
#define Star_Dis_l 810.f
#define Star_Dis_t 430.f

struct ID2D1Bitmap;
struct ID2D1RenderTarget;

class CStarShot : public IGameObject
{
public:
	CStarShot(ID2D1RenderTarget *pRenderTarget);
	virtual ~CStarShot();
	virtual bool move() override;
	virtual void draw(ID2D1RenderTarget *pRenderTarget) override;
protected:
	ID2D1Bitmap *pStarShot;
	ID2D1Bitmap *pBGStar;
	ID2D1Bitmap *pBGStar_2;
	D2D1_RECT_F rc, rc2;

	unsigned int StarTime;
	float Angle_rotation;
	float b, m, speed, scale;

};

