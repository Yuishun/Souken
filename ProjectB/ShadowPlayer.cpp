#include "stdafx.h"
#include <d2d1.h>
#include "ShadowPlayer.h"
#include "TextureLoader.h"
#include "GameData.h"
#include "Player.h"


CShadowPlayer::CShadowPlayer(ID2D1RenderTarget *pRenderTarget, CPlayer	*pPlayer)
{
	g_pCharaImage_RedS = NULL;
	g_pCharaImage_RedSjump = NULL;
	g_pCharaImage_RedSdown = NULL;
	g_pCharaImage_BlueS = NULL;
	g_pCharaImage_BlueSjump = NULL;
	g_pCharaImage_BlueSdown = NULL;
	S_PlayerPhase = DEFOULT;
	wait = 0;
	FramePhase = 0;
	g_pRenderTarget = pRenderTarget;
	frameTime = 0;
	//S_Distination = CENTERpoint_b;
	rc = { GameData::PlayerPoint[0] - 50.f,GameData::PlayerPoint[1] - 30.f,
		GameData::PlayerPoint[2] - 50.f, GameData::PlayerPoint[3] };
	pDistination = pPlayer;
	S_Damageflash = 1.f;

	CTextureLoader::shadow = true;
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\kyara_un.png"), &g_pCharaImage_RedS);
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\kyara_un_jnp.png"), &g_pCharaImage_RedSjump);
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\kyara_un_dwn.png"), &g_pCharaImage_RedSdown);
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\kyara_a.png"), &g_pCharaImage_BlueS);
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\kyara_a_jnp.png"), &g_pCharaImage_BlueSjump);
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\kyara_a_dwn.png"), &g_pCharaImage_BlueSdown);
	CTextureLoader::shadow = false;

}


CShadowPlayer::~CShadowPlayer()
{
	SAFE_RELEASE(g_pCharaImage_RedS);
	SAFE_RELEASE(g_pCharaImage_RedSjump);
	SAFE_RELEASE(g_pCharaImage_RedSdown);
	SAFE_RELEASE(g_pCharaImage_BlueS);
	SAFE_RELEASE(g_pCharaImage_BlueSjump);
	SAFE_RELEASE(g_pCharaImage_BlueSdown);
}

/**
* @brief エラー回避
*/
bool CShadowPlayer::move() {
	return GameSceneResultCode::GAMESCENE_DEFAULT;
}

/**
* @brief プレイヤーでない狛犬を描画
*/
void CShadowPlayer::draw(ID2D1RenderTarget *pRenderTarget) {
	if (S_PlayerPhase != GameData::PlayerPhase) {
		++wait;
		if (wait > 2 || GameData::PlayerPhase >= UP) {
			S_PlayerPhase = GameData::PlayerPhase;
			wait = 0;
			FramePhase = 0;
		}
	}
	D2D1_RECT_F  src;
	/*rc = { GameData::PlayerPoint[0] - 50.f,GameData::PlayerPoint[1],
		GameData::PlayerPoint[2] - 50.f, GameData::PlayerPoint[3] };*/
		//! 各モーション
	switch (S_PlayerPhase) {
	case DEFOULT:
		if (JumpFlag)
			JumpFlag = false;
		if(rc.top != rc.bottom - 150)
			rc.top = rc.bottom - 150;
		src.left = FramePhase * 300.f;
		src.right = src.left + 300;
		src.top = 0;
		src.bottom = 150;
		if (frametime(pDistination->framewait)) {
			++FramePhase %= 5;
		}
		break;
	case UP:
		switch (FramePhase) {
		case 0:
			rc = { rc.left,rc.top,rc.right,rc.bottom };
			src = { 0,0,300,150 };
			if (frametime(4)) {
				JumpFlag = true;
				FramePhase++;
				S_Distination = pDistination->GetDis();
			}
			break;
		case 1:
			//rc.left = rc.right - 150.f;
			rc.top = rc.bottom - 238.f;
			//src = { 0,0,300,150 };
			if (frametime(4))
				FramePhase++;
			break;
		case 2:
			if (frameTime == 0)
				rc = { rc.left - 10.f,rc.top - 100.f,rc.right - 10.f,rc.bottom - 100.f };
			//src = { 0,0,300,150 };
			if (frametime(4))
				FramePhase++;
			break;
		case 3:
			if (frameTime == 0)
				rc = { rc.left + 10.f,rc.top - 125.f,rc.right + 10.f,rc.bottom - 125.f };
			//src = { 0,0,300,150 };
			if (frametime(4))
				FramePhase++;
			break;
		case 4:
			rc = { rc.left,rc.top + 30.f,rc.right,rc.bottom + 30.f };
			//src = { 0,0,300,150 };
			if (rc.bottom >= S_Distination) {
				rc.bottom = S_Distination;
				rc.top = rc.bottom - 150.f;
				rc.left = rc.right - 300.f;
				src = { 600,0,900,150 };
				FramePhase++;
			}
			break;
		case 5:
			if (rc.bottom != S_Distination)
				rc.bottom = S_Distination;
			rc.top = rc.bottom - 150.f;
			src = { 0,0,300,150 };
			FramePhase = 0;
			JumpFlag = false;
			break;
		}
		break;
	case DOWN:
		switch (FramePhase) {
		case 0:
			rc = { rc.left,rc.top,rc.right,rc.bottom };
			src = { 0,0,300,150 };
			if (frametime(4)) {
				FramePhase++;
				S_Distination = pDistination->GetDis();
				JumpFlag = true;
			}
			break;
		case 1:
			//rc.left -= 20.f;
			rc.bottom = rc.top + 238.f ;
			//src = { 0,0,300,150 };
			if (frametime(4))
				FramePhase++;
			break;
		case 2:
			if (frameTime == 0)
				rc = { rc.left + 10.f,rc.top + 100.f,rc.right + 10.f,rc.bottom + 100.f };
			src = { 0,0,300,150 };
			if (frametime(4))
				FramePhase++;
			break;
		case 3:
			if (frameTime == 0)
				rc = { rc.left - 10.f,rc.top + 50.f,rc.right - 10.f,rc.bottom + 50.f };
			//src = { 0,0,300,150 };
			if (frametime(4))
				FramePhase++;
			break;
		case 4:
			rc = { rc.left,rc.top + 20.f,rc.right,rc.bottom + 20.f };
			//src = { 0,0,300,150 };
			if (rc.bottom >= S_Distination) {
				rc.bottom = S_Distination;
				rc.top = rc.bottom - 150.f;
				rc.left = rc.right - 300.f;
				src = { 600,0,900,150 };
				FramePhase++;
			}
			break;
		case 5:
			if (rc.bottom != S_Distination)
				rc.bottom = S_Distination;
			rc.top = rc.bottom - 150.f;
			src = { 0,0,300,150 };
			FramePhase = 0;
			JumpFlag = false;
			break;
		}
		break;
	case CHANGE:
		switch (FramePhase) {
		case 0:
			rc = { rc.left,rc.top,rc.right,rc.bottom };
			src = { 0,0,300,150 };
			if (frametime(4)) {
				FramePhase++;
				S_Distination = pDistination->GetDis();
			}
			break;
		case 1:
			if (frameTime == 0)
				rc = { rc.left + 20.f,rc.top - 10.f,rc.right + 20.f,rc.bottom - 10.f };
			src = { 900,0,1200,150 };
			if (frametime(2))
				FramePhase++;
			break;
		case 2:
			if (frameTime == 0)
				rc = { rc.left + 10.f,rc.top - 30.f,rc.right + 10.f,rc.bottom - 30.f };
			src = { 1200,0,1500,150 };
			if (frametime(5))
				FramePhase++;
			break;
		case 3:
			if (frameTime % 5 == 0)
				rc = { rc.left + 10.f,rc.top + 20.f,rc.right + 10.f,rc.bottom + 20.f };
			src = { 0,0,300,150 };
			if (frametime(8)) {
				FramePhase++;
			}
			break;
		case 4:
			rc.left -= 50.f;
			rc.right -= 50.f;
			rc.bottom = S_Distination;
			rc.top = rc.bottom - 150.f;
			src = { 0,0,300,150 };
			FramePhase = 0;
			JumpFlag = false;
			break;
		}
		break;
	case DAMAGE:
		switch (FramePhase) {
		case 0:
			if (JumpFlag) {
				rc.bottom = S_Distination;
				rc.top = rc.bottom - 150.0f;
				rc.left = 250.f;
				rc.right = rc.left + 300;
				JumpFlag = false;
			}
			src = { 600,0,900,150 };
			FramePhase++;
			break;
		case 1:
			src = { 600,0,900,150 };
			if (frametime(7) == true)
				FramePhase++;
			break;
		case 2:
			src = { 0,0,300,150 };
			FramePhase = 0;
			break;
		}
		break;
	case FADE:
	case DIE:
		rc.top = rc.bottom - 150;
		rc.left = rc.right - 300;
		src = { 600,0,900,150 };

		break;
	}

	if (S_PlayerPhase != UP && S_PlayerPhase != DOWN) {
		if (rc.top!=rc.bottom-150 || 
			((rc.right >= GameData::PlayerPoint[2]||rc.bottom>=GameData::PlayerPoint[3])
				&& S_PlayerPhase == DEFOULT)) {
    		rc.left = 250;
			rc.right = rc.left + 300;
			rc.bottom = GameData::PlayerPoint[3];
			rc.top = rc.bottom - 150;
		}
	}

	S_Damageflash = pDistination->Damageflash;
	//! 描画
	if (GameData::NowPlayerColor == Blue_) {
		if (GameData::PlayerPhase == UP && JumpFlag) {
			Scale();
			g_pRenderTarget->DrawBitmap(g_pCharaImage_RedSjump, rc, S_Damageflash, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
			//! 座標変換を元に戻す
			g_pRenderTarget->SetTransform(
				D2D1::Matrix3x2F::Identity()
			);
		}
		else if (GameData::PlayerPhase == DOWN && JumpFlag) {
			Scale();
			g_pRenderTarget->DrawBitmap(g_pCharaImage_RedSdown, rc, S_Damageflash, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
			//! 座標変換を元に戻す
			g_pRenderTarget->SetTransform(
				D2D1::Matrix3x2F::Identity()
			);
		}
		else
			g_pRenderTarget->DrawBitmap(g_pCharaImage_RedS, rc, S_Damageflash, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);
	}
	else {
		if (S_PlayerPhase == UP && JumpFlag) {
			Scale();
			g_pRenderTarget->DrawBitmap(g_pCharaImage_BlueSjump, rc, S_Damageflash, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
			//! 座標変換を元に戻す
			g_pRenderTarget->SetTransform(
				D2D1::Matrix3x2F::Identity()
			);
		}
		else if (S_PlayerPhase == DOWN && JumpFlag) {
			Scale();
			g_pRenderTarget->DrawBitmap(g_pCharaImage_BlueSdown, rc, S_Damageflash, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
			//! 座標変換を元に戻す
			g_pRenderTarget->SetTransform(
				D2D1::Matrix3x2F::Identity()
			);
		}
		else
			g_pRenderTarget->DrawBitmap(g_pCharaImage_BlueS, rc, S_Damageflash, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);
	}
}

bool CShadowPlayer::frametime(char framewait) {
	++frameTime;
	if (frameTime >= framewait) {
		frameTime = 0;
		return true;
	}
	return false;
}

void CShadowPlayer::Scale() {
	D2D_POINT_2F tRotateCenter = D2D1::Point2F(
		(rc.left + rc.right) / 2
		, (rc.top + rc.bottom) / 2
	);
	g_pRenderTarget->SetTransform(
		D2D1::Matrix3x2F::Scale(1.05f, 1.05f
			, tRotateCenter)
	);
}