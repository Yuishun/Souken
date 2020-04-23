#include "stdafx.h"
#include <d2d1.h>
#include "Item.h"
#include "TextureLoader.h"


CItem::CItem(ID2D1RenderTarget *pRenderTarget, ID2D1Bitmap *pItem)
{
	Pos = { 1920,TOPpoint_b };
	g_pItem = pItem;
	m_bItemFlag = true;
}


CItem::~CItem()
{
}


/*******************************
* @method	move
* @return	true:on		false:can get or can't get
*******************************/
bool CItem::move()
{
	Pos.x -= GameData::RunSpeed;

	if (Pos.x <= -100.0f) {
		m_bItemFlag = false;
		return GameSceneResultCode::GAMESCENE_DEFAULT;
	}

	if (GameData::PurpleTime == true)
		Purplemove();

	//!	ƒvƒŒƒCƒ„[‚Æ‚Ì“–‚½‚è”»’è
	if (PointinRect(GameData::PlayerPoint[0], GameData::PlayerPoint[1],
		GameData::PlayerPoint[2], GameData::PlayerPoint[3])) {
		if (ItemColor == White) {
			GameData::PlayerHP += 800;
			if (GameData::PlayerHP >= PHP_NUM)
				GameData::PlayerHP = PHP_NUM;
		}
		else if (ItemColor == Paple) {
			if (GameData::PurpleTime == false) {
				++GameData::Purplegauge;
				if (GameData::Purplegauge >= 2) {
					GameData::PurpleTime = true;
					GameData::Purplegauge = 2;
				}
			}
			else if (GameData::PurpleTime == true) {
				GameData::Score += 20;
			}
		}
		else if (ItemColor == Yellow) {
			if (GameData::StarShot == 0) {
				++GameData::Stargauge;
				if (GameData::Stargauge > 5) {
					GameData::Stargauge = 5;

				}
			}
		}
		m_bItemFlag = false;
	}

	return GameSceneResultCode::GAMESCENE_DEFAULT;
}

/************************************
* @method	draw
************************************/
void CItem::draw(ID2D1RenderTarget *pRenderTarget)
{
	D2D1_SIZE_F size = pRenderTarget->GetSize();
	rc.left = Pos.x;
	rc.right = Pos.x + 100.f;
	rc.top = Pos.y - 100.f;
	rc.bottom = Pos.y;
	src.top = 0.0f;
	src.right = src.left + 150.0f;
	src.bottom = 150.0f;
	pRenderTarget->DrawBitmap(g_pItem, rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);

}

void CItem::SetSpawn(int pos_, int color_)
{
	switch (color_) {
	case(0):
		ItemColor = Paple;
		break;
	case(1):
		ItemColor = Yellow;
		break;
	case(2):
		ItemColor = White;
		break;
	}
	src.left = color_ * 150.0f;

	switch (pos_) {
	case(0):
		Pos.y = TOPpoint_b;
		break;
	case(1):
		Pos.y = CENTERpoint_b;
		break;
	case(2):
		Pos.y = BOTTOMpoint_b;
		break;
	}
}

bool CItem::PointinRect(float x1, float y1, float x2, float y2)
{
	if (x1 <= rc.right&&rc.left <= x2) {
		if (y1 <= rc.bottom&& rc.top <= y2)
			return true;
	}
	return false;
}

void CItem::Purplemove()
{
	float PlayerGetX = Pos.x - GameData::PlayerPoint[0];
	float PlayerGetY = Pos.y - GameData::PlayerPoint[3];

	if (PlayerGetX != 0.0f) {
		if (PlayerGetX > 0.0f)
			Pos.x -= 10.0f;
		if (PlayerGetX < 0.0f)
			Pos.x += 20.0f;
	}

	if (PlayerGetY != 0.0f) {
		if (PlayerGetY > 0.0f)
			Pos.y -= 10.0f;
		else
			Pos.y += 20.0f;
	}
}