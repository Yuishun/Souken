#pragma once

#ifdef __IGAMEOBJECT_H__
#include "IGameObject.h"
#endif

//	ÉAÉCÉeÉÄêî
#define ITEM_NUM 3
class CStage;
class CItem;
class CItemManager
{
public:
	CItemManager(CStage *pStage);
	virtual ~CItemManager();
	virtual bool move();
	virtual void draw(ID2D1RenderTarget *pRenderTarget);
	char SetISpawnNum();
protected:
	CItem				*Item[ITEM_NUM];
	CStage				*m_pStage;
	ID2D1RenderTarget	*pTarget;
	ID2D1Bitmap			*pItem;
private:
	void Spown(char itemlimit);
};