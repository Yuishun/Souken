#pragma once

#include "IGameScene.h"

#define Score_width 75.f

struct ID2D1Bitmap;

class CRanking;
class CScore :
	public IGameScene
{
public:
	CScore(ID2D1RenderTarget *pRenderTarget);
	virtual ~CScore();
	virtual GameSceneResultCode move() override;
	virtual void draw(ID2D1RenderTarget *pRenderTarget) override;
	void Ranikngdraw(ID2D1RenderTarget *pRenderTarget);
protected:
	UINT score;
	ID2D1Bitmap *pScoreUI;
	ID2D1Bitmap *p_Ten;
	ID2D1Bitmap *pRankStar;
	ID2D1Bitmap *pRanknum;
	CRanking	*pRanking;
	bool RankFlag;
};

