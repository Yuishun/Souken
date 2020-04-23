#pragma once

#include "IGameObject.h"
#include "Selector.h"
#include "GameData.h"

#define ETYPE0WIDTH 120.f
#define ETYPE1WIDTH 240.f
#define ENEMY_LEFT 2030.f

#define ENEMY0_TOP_B 250.f
#define ENEMY0_CENTER_B 570.f
#define ENEMY0_BOTTOM_B 930.f

#define ENEMY1_TOP_B 295.f
#define ENEMY1_CENTER_B 615.f
#define ENEMY1_BOTTOM_B 975.f

#define PI 3.1415926f

struct ID2D1Bitmap;
struct ID2D1Rendertarget;
class CEnemy : public IGameObject
{
public:
	CEnemy(ID2D1RenderTarget *pRenderTarget,ID2D1Bitmap *pEnemy0,ID2D1Bitmap *pEnemy1);
	virtual ~CEnemy();
	virtual bool move();
	virtual void draw(ID2D1RenderTarget *pRenderTarget);
	bool GetFlag() { return flag; }
	void SetSpawn(int pos_,bool color_,char type_);
	bool PointinRect(float x1,float y1,float x2,float y2);
protected:
	int hp;
	COLOR Ecolor;
	char type;
	D2D1_RECT_F rc, src;
	float fluffy;
	bool flag;
	unsigned char score;
	float width;
	float opacity;

	ID2D1Bitmap *e_pEnemy0;
	ID2D1Bitmap *e_pEnemy1;
	float srcplus;
	unsigned int count;
};

