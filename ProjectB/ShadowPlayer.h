#pragma once

#include "IGameObject.h"
#include "Selector.h"
#include "GameData.h"

class CPlayer;
/**
* @brief ‰e‚ð’x‚ç‚¹‚Ä•\Ž¦‚³‚¹‚é‚¾‚¯
*/
class CShadowPlayer : public IGameObject
{
public:
	CShadowPlayer(ID2D1RenderTarget *pRenderTarget, CPlayer	*pPlayer);
	virtual ~CShadowPlayer();
	virtual bool move() override;
	virtual void draw(ID2D1RenderTarget *pRenderTarget) override;
	bool frametime(char framewait);
protected:
	ID2D1Bitmap			*g_pCharaImage_RedS;
	ID2D1Bitmap			*g_pCharaImage_RedSjump;
	ID2D1Bitmap			*g_pCharaImage_RedSdown;
	ID2D1Bitmap			*g_pCharaImage_BlueS;
	ID2D1Bitmap			*g_pCharaImage_BlueSjump;
	ID2D1Bitmap			*g_pCharaImage_BlueSdown;
	ID2D1RenderTarget	*g_pRenderTarget;
	CPlayer				*pDistination;
	PlayerPHASE S_PlayerPhase;
	D2D1_RECT_F rc;
	void Scale();
	char wait;
	char FramePhase;
	char frameTime;
	float S_Distination;
	bool JumpFlag;
	float S_Damageflash;
};

