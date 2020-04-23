#pragma once

class CStage;

class CHPUI;
class CPurpleUI;
class CStarUI;
class CUI:
	public IGameScene
{
public:
	CUI(CStage *pStage);
	virtual ~CUI();
	virtual GameSceneResultCode move() override;
	virtual void draw(ID2D1RenderTarget *pRenderTarget) override;
protected:
	CStage		*m_pStage;
	ID2D1Bitmap *ScoreUI;

	CHPUI *m_pHP;
	CPurpleUI *m_pPurple;
	CStarUI *m_pStar;

	UINT score;
};

