#include "stdafx.h"
#include <d2d1.h>
#include "Player.h"
#include "TextureLoader.h"
#include "GameData.h"

CPlayer::CPlayer(ID2D1RenderTarget *pRenderTarget)
{
	g_pCharaImage_Red = NULL;
	g_pCharaImage_Redjump = NULL;
	g_pCharaImage_Reddown = NULL;
	g_pCharaImage_Blue = NULL;
	g_pCharaImage_Bluejump = NULL;
	g_pCharaImage_Bluedown = NULL;
	g_pRenderTarget = pRenderTarget;


	KeyFlag = false;
	ShotFlag = false;
	JumpFlag = false;
	InvincibleTime = 0;
	FramePhase = 0;
	plus = 0.2f;
	shotwait = 0;
	frameTime = 0;
	Distination = TOPpoint_b;
	Damageflash = 1.f;
	framewait = 8;

	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\kyara_un.png"), &g_pCharaImage_Red);
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\kyara_un_jnp.png"), &g_pCharaImage_Redjump);
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\kyara_un_dwn.png"), &g_pCharaImage_Reddown);
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\kyara_a.png"), &g_pCharaImage_Blue);
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\kyara_a_jnp.png"), &g_pCharaImage_Bluejump);
	CTextureLoader::CreateD2D1BitmapFromFile(pRenderTarget, _T("res\\kyara_a_dwn.png"), &g_pCharaImage_Bluedown);
}


CPlayer::~CPlayer()
{
	SAFE_RELEASE(g_pCharaImage_Red);
	SAFE_RELEASE(g_pCharaImage_Redjump);
	SAFE_RELEASE(g_pCharaImage_Reddown);
	SAFE_RELEASE(g_pCharaImage_Blue);
	SAFE_RELEASE(g_pCharaImage_Bluejump);
	SAFE_RELEASE(g_pCharaImage_Bluedown);
}

bool CPlayer::move() {

	//! ダメージフラグが建ったら
	if (GameData::PlayerDamage && InvincibleTime <= 0) {
		KeyFlag = true;
		GameData::PlayerHP -= 300;
		GameData::PlayerPhase = DAMAGE;
		FramePhase = 0;
	}
	else {
		//! プレイヤーの動き関連　(操作)
		if (GetAsyncKeyState(VK_UP) && !KeyFlag
			&& (GameData::PlayerPoint[3] > TOPpoint_b)) {
			KeyFlag = true;
			JumpFlag = true;
			GameData::PlayerPhase = UP;
			FramePhase = 0;
			if (GameData::PlayerPoint[3] == BOTTOMpoint_b)
				Distination = CENTERpoint_b;
			else if (GameData::PlayerPoint[3] == CENTERpoint_b)
				Distination = TOPpoint_b;
		}
		else if (GetAsyncKeyState(VK_DOWN) && !KeyFlag
			&& (GameData::PlayerPoint[3] < BOTTOMpoint_b)) {
			KeyFlag = true;
			JumpFlag = true;
			GameData::PlayerPhase = DOWN;
			FramePhase = 0;
			if (GameData::PlayerPoint[3] == TOPpoint_b)
				Distination = CENTERpoint_b;
			else if (GameData::PlayerPoint[3] == CENTERpoint_b)
				Distination = BOTTOMpoint_b;
		}
		else if ((GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT)) && !KeyFlag) {
			KeyFlag = true;
			JumpFlag = true;
			GameData::PlayerPhase = CHANGE;
			FramePhase = 0;
			if (GameData::PlayerPoint[3] == TOPpoint_b)
				Distination = TOPpoint_b;
			else if (GameData::PlayerPoint[3] == CENTERpoint_b)
				Distination = CENTERpoint_b;
			else if (GameData::PlayerPoint[3] == BOTTOMpoint_b)
				Distination = BOTTOMpoint_b;
		}
		else if (!KeyFlag) {
			SetFramewait();
			GameData::PlayerPhase = DEFOULT;
		}

		//! ショット関連処理
		if (GetAsyncKeyState(VK_RETURN) && !KeyFlag && (GameData::Stargauge == 5)) {
			GameData::StarShot = 1;
			GameData::Stargauge = 6;
			//GameData::framewait = 250;
		}
		else if (GetAsyncKeyState(VK_SPACE)) {
			++shotwait;
			if (shotwait >= 40) {
				ShotFlag = false;
				shotwait = 0;
			}
			if (!KeyFlag && !ShotFlag) {
				ShotFlag = true;
				GameData::ShotFlag = true;
			}
		}
		else if (!GetAsyncKeyState(VK_SPACE)) {
			ShotFlag = false;
			shotwait = 0;
		}
		if (GetAsyncKeyState(VK_TAB)) {	//チート
			//GameData::Stargauge = 5;
			GameData::PlayerHP -= 400;
			//GameData::Score += 10000;
		}
	}
	//! HP0の時の処理
	if (GameData::PlayerHP <= 0) {
		GameData::PlayerPhase = FADE;
		framewait = 255;
		return GameSceneResultCode::GAMESCENE_END_OK;
	}

	return GameSceneResultCode::GAMESCENE_DEFAULT;
}


void CPlayer::draw(ID2D1RenderTarget *pRenderTarget) {

	D2D1_RECT_F rc, src;
	rc = { GameData::PlayerPoint[0],GameData::PlayerPoint[1],
		GameData::PlayerPoint[2], GameData::PlayerPoint[3] };
	//! 各モーション
	switch (GameData::PlayerPhase) {
	case DEFOULT:
		src.left = FramePhase * 300.f;
		src.right = src.left + 300;
		src.top = 0;
		src.bottom = 150;
		if (frametime(framewait)) {
			++FramePhase %= 5;
		}
		break;
	case UP:
		switch (FramePhase) {
		case 0:
			rc = { rc.left,rc.top,rc.right,rc.bottom };
			src = { 0,0,300,150 };
			if (frametime(4))
				FramePhase++;
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
			rc = { rc.left,rc.top + 15.f,rc.right,rc.bottom + 15.f };
			//src = { 0,0,300,150 };
			if (rc.bottom >= Distination) {
				rc.bottom = Distination;
				rc.top = rc.bottom - 120.f;
				rc.left = rc.right - 300.f;
				src = { 600,0,900,150 };
				FramePhase++;
			}
			break;
		case 5:
			src = { 0,0,300,150 };
			FramePhase = 0;
			KeyFlag = false;
			JumpFlag = false;
			break;
		}
		break;
	case DOWN:
		switch (FramePhase) {
		case 0:
			rc = { rc.left,rc.top,rc.right,rc.bottom };
			src = { 0,0,300,150 };
			if (frametime(4))
				FramePhase++;
			break;
		case 1:
			//rc.left = rc.right - 150.f;
			rc.bottom = rc.top + 238.f;
			//src = { 0,0,300,150 };
			if (frametime(4))
				FramePhase++;
			break;
		case 2:
			if (frameTime == 0)
				rc = { rc.left + 10.f,rc.top + 100.f,rc.right + 10.f,rc.bottom + 100.f };
			//src = { 0,0,300,150 };
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
			rc = { rc.left,rc.top + 15.f,rc.right,rc.bottom + 15.f };
			//src = { 0,0,300,150 };
			if (rc.bottom >= Distination) {
				rc.bottom = Distination;
				rc.top = rc.bottom - 120.f;
				rc.left = rc.right - 300.f;
				src = { 600,0,900,150 };
				FramePhase++;
			}
			break;
		case 5:
			rc = { rc.left,rc.top,rc.right,rc.bottom };
			//src = { 0,0,300,150 };
			FramePhase = 0;
			KeyFlag = false;
			JumpFlag = false;
			break;
		}
		break;
	case CHANGE:
		switch (FramePhase) {
		case 0:
			rc = { rc.left,rc.top,rc.right,rc.bottom };
			src = { 0,0,300,150 };
			if (frametime(4))
				FramePhase++;
			break;
		case 1:
			if (frameTime == 0)
				rc = { rc.left - 20.f,rc.top - 10.f,rc.right - 20.f,rc.bottom - 10.f };
			src = { 900,0,1200,150 };
			if (frametime(2))
				FramePhase++;
			break;
		case 2:
			if (frameTime == 0)
				rc = { rc.left - 10.f,rc.top - 30.f,rc.right - 10.f,rc.bottom - 30.f };
			src = { 1200,0,1500,150 };
			if (frametime(5))
				FramePhase++;
			break;
		case 3:
			if (frameTime % 5 == 0)
				rc = { rc.left - 10.f,rc.top + 20.f,rc.right - 10.f,rc.bottom + 20.f };
			src = { 0,0,300,150 };
			if (frametime(8)) {
				FramePhase++;
			}
			break;
		case 4:
			rc.left += 50.f;
			rc.right += 50.f;
			rc.bottom = Distination;
			rc.top = rc.bottom - 120.f;
			src = { 0,0,300,150 };
			FramePhase = 0;
			KeyFlag = false;
			JumpFlag = false;
			if (GameData::NowPlayerColor == Red_) {
				GameData::NowPlayerColor = Blue_;
			}
			else {
				GameData::NowPlayerColor = Red_;
			}
			break;
		}
		break;
	case DAMAGE:
		switch (FramePhase) {
		case 0:
			if (JumpFlag) {
				rc.bottom = Distination;
				rc.top = rc.bottom - 120.0f;
				rc.left = 300.f;
				rc.right = rc.left + 300;
				JumpFlag = false;
			}
			src = { 600,0,900,150 };
			FramePhase++;
			break;
		case 1:
			rc = { rc.left,rc.top,rc.right,rc.bottom };
			src = { 600,0,900,150 };
			if (frametime(7) == true)
				FramePhase++;
			break;
		case 2:
			rc = { rc.left,rc.top,rc.right,rc.bottom };
			src = { 0,0,300,150 };
			FramePhase = 0;
			KeyFlag = false;
			break;
		}
		break;
	case FADE:
	case DIE:
		rc.top = rc.bottom - 120;
		rc.left = rc.right - 300;
		src = { 600,0,900,150 };

		break;
	}

	//! 被弾時の無敵時間作りと点滅
	if (GameData::PlayerDamage) {
		++InvincibleTime;
		if (Damageflash >= 1.0f || Damageflash <= 0.2f)
			plus = -plus;
		Damageflash += plus;
		if (InvincibleTime >= 180) {
			InvincibleTime = 0;
			Damageflash = 1.0f;
			GameData::PlayerDamage = false;
		}
	}

	GameData::PlayerPoint[0] = rc.left;
	GameData::PlayerPoint[1] = rc.top;
	GameData::PlayerPoint[2] = rc.right;
	GameData::PlayerPoint[3] = rc.bottom;
	if (GameData::PlayerPhase == UP || GameData::PlayerPhase == DOWN) {
		
	}
	else {
		rc.top -= 30.0f;
	}
	//! 描画
	if (GameData::NowPlayerColor == Red_) {
		if (GameData::PlayerPhase == UP && JumpFlag) {
			Scale(rc);
			g_pRenderTarget->DrawBitmap(g_pCharaImage_Redjump, rc, Damageflash, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
			//! 座標変換を元に戻す
			g_pRenderTarget->SetTransform(
				D2D1::Matrix3x2F::Identity()
			);
		}
		else if (GameData::PlayerPhase == DOWN && JumpFlag) {
			Scale(rc);
			g_pRenderTarget->DrawBitmap(g_pCharaImage_Reddown, rc, Damageflash, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
			//! 座標変換を元に戻す
			g_pRenderTarget->SetTransform(
				D2D1::Matrix3x2F::Identity()
			);
		}
		else
			g_pRenderTarget->DrawBitmap(g_pCharaImage_Red, rc, Damageflash, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);
	}
	else {
		if (GameData::PlayerPhase == UP && JumpFlag) {
			Scale(rc);
			g_pRenderTarget->DrawBitmap(g_pCharaImage_Bluejump, rc, Damageflash, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
			//! 座標変換を元に戻す
			g_pRenderTarget->SetTransform(
				D2D1::Matrix3x2F::Identity()
			);
		}
		else if (GameData::PlayerPhase == DOWN && JumpFlag) {
			Scale(rc);
			g_pRenderTarget->DrawBitmap(g_pCharaImage_Bluedown, rc, Damageflash, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);
			//! 座標変換を元に戻す
			g_pRenderTarget->SetTransform(
				D2D1::Matrix3x2F::Identity()
			);
		}
		else
			g_pRenderTarget->DrawBitmap(g_pCharaImage_Blue, rc, Damageflash, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);
	}
}

void CPlayer::SetFramewait() {
	switch (GameData::StagePhase) {
	case NOON:
		framewait = 8;
		break;
	case TWILIGHT:
		framewait = 7;
		break;
	case NIGHT:
		framewait = 6;
		break;
	case BLOODMOON:
		framewait = 5;
		break;
	}
}

/**
* @brief 指定されたフレームごとにtrueを送る
*/
bool CPlayer::frametime(char framewait) {
	++frameTime;
	if (frameTime >= framewait) {
		frameTime = 0;
		return true;
	}
	return false;
}

void CPlayer::Scale(D2D1_RECT_F rc) {
	D2D_POINT_2F tRotateCenter = D2D1::Point2F(
		(rc.left + rc.right) / 2
		, (rc.top + rc.bottom) / 2
	);
	g_pRenderTarget->SetTransform(
		D2D1::Matrix3x2F::Scale(1.05f, 1.05f
			, tRotateCenter)
	);
}