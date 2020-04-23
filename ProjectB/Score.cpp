#include "stdafx.h"
#include "Score.h"
#include <d2d1.h>
#include "TextureLoader.h"
#include "Ranking.h"
#include "GameData.h"


CScore::CScore(ID2D1RenderTarget *pRenderTarget)
{
	pRanking = new CRanking();
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\number.png"), &pScoreUI);
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\score.png"), &p_Ten);
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\BGStar.png"), &pRankStar);
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\ranking.png"), &pRanknum);
	RankFlag = true;
}


CScore::~CScore()
{
	SAFE_DELETE(pRanking);
	SAFE_RELEASE(pScoreUI);
	SAFE_RELEASE(p_Ten);
	SAFE_RELEASE(pRankStar);
}

GameSceneResultCode CScore::move() {
	return GameSceneResultCode::GAMESCENE_DEFAULT;
}

void CScore::draw(ID2D1RenderTarget *pRenderTarget) {
	
	D2D1_RECT_F rc, src, rc2;
	src.top = 0;
	src.bottom = Score_width;
	score = GameData::Score;
	unsigned char digit = 0;
	while (score != 0) {
		score /= 10;
		digit++;
	}
	float r_set = digit / 2.f;	//真ん中寄せにするため
	rc.right = 960 + (Score_width*r_set);
	rc.left = rc.right - Score_width;
	rc.top = 510;
	rc.bottom = rc.top + Score_width;
	rc2.left = 960.f - (103.f / 2.f);
	rc2.right = rc2.left + 103;
	rc2.top = rc.bottom + 30.f;
	rc2.bottom = rc2.top + 97;
	score = GameData::Score;
	for (int i = 0; i < digit; ++i) {
		char num = score % 10;
		src.left = num * Score_width;
		src.right = src.left + Score_width;
		pRenderTarget->DrawBitmap(pScoreUI, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);
		score /= 10;
		rc.left -= Score_width;
		rc.right -= Score_width;
	}
	pRenderTarget->DrawBitmap(p_Ten, rc2, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
}

void CScore::Ranikngdraw(ID2D1RenderTarget *pRenderTarget) {
	if (RankFlag) {
		pRanking->DoRanking();
		RankFlag = false;
	}
	D2D1_RECT_F rc, src, rc2;
	rc.bottom = 910;			//初期値（一番下）
	rc.top = rc.bottom - Score_width;
	src.top = 0;

	for (int i = TOP_NUM - 1; i >= 0; --i) {
		score = pRanking->rank[i];
		unsigned char digit = 0;
		while (score != 0) {
			score /= 10;
			digit++;
		}
		float r_set = digit / 2.f;	//真ん中寄せにするため
		rc.right = 960 + (Score_width*r_set);
		rc.left = rc.right - Score_width;

		src.bottom = Score_width;
		score = pRanking->rank[i];
		for (int i = 0; i < digit; ++i) {
			char num = score % 10;
			src.left = num * Score_width;
			src.right = src.left + Score_width;
			pRenderTarget->DrawBitmap(pScoreUI, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);
			score /= 10;
			rc.left -= Score_width;
			rc.right -= Score_width;
		}
		if (pRanking->ranknum == i) {
			rc2.left = 0;
			rc2.right = rc2.left + Score_width;
			rc2.top = rc.top - 22.5f;
			rc2.bottom = rc.bottom + 22.5f;
			pRenderTarget->DrawBitmap(pRankStar, rc2, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
		}

		rc2.left = 120.f;
		rc2.right = rc2.left + 150.f;
		rc2.top = rc.top - 32.5f;
		rc2.bottom = rc.bottom + 32.5f;
		src.left = 150 * i;
		src.right = src.left + 150;
		src.bottom = 150;
		pRenderTarget->DrawBitmap(pRanknum, rc2, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);
		
		if (i > 2)
			rc.bottom -= 140.f;
		else
			rc.bottom -= 150.f;
		rc.top = rc.bottom - Score_width;
	}
}