#pragma once

#include "IGameObject.h"
#include "Selector.h"
#include "GameData.h"


struct ID2D1Bitmap;
struct ID2D1RenderTarget;
class CItem : public IGameObject
{
public:
	CItem(ID2D1RenderTarget *pRenderTarget,ID2D1Bitmap *pItem);
	virtual ~CItem();
	virtual bool move();
	virtual void draw(ID2D1RenderTarget *pRenderTarget);
	void SetSpawn(int pos_, int color_);
	bool GetFlag() { return m_bItemFlag; }
	bool PointinRect(float x1, float y1, float x2, float y2);
protected:
	void Purplemove();

	bool				m_bItemFlag;	//アイテムのゲット
	ICOLOR				ItemColor;
	ID2D1Bitmap			*g_pItem;
	ID2D1RenderTarget	*pRenderTarget;

	typedef struct {
		float x;
		float y;
	}Vector2D;
	
	Vector2D		Pos;

	D2D1_RECT_F rc,src;

};

