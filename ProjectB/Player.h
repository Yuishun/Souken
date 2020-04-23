#pragma once

#include "IGameObject.h"
#include "Selector.h"

struct ID2D1Bitmap;
struct ID2D1Rendertarget;
class CPlayer : public IGameObject
{
public:
	CPlayer(ID2D1RenderTarget *pRenderTarget);
	virtual ~CPlayer();
	virtual bool move() override;
	virtual void draw(ID2D1RenderTarget *pRenderTarget) override;
	bool frametime(char framewait);
	float GetDis() { return Distination; }
	float Distination;
	float Damageflash;
	void SetFramewait();
	unsigned char framewait;
protected:
	//âÊëúêÿÇËéÊÇËÇ…Ç¬Ç©Ç§ÅHDWORD		g_dwCount;
	ID2D1Bitmap			*g_pCharaImage_Red;
	ID2D1Bitmap			*g_pCharaImage_Redjump;
	ID2D1Bitmap			*g_pCharaImage_Reddown;
	ID2D1Bitmap			*g_pCharaImage_Blue;
	ID2D1Bitmap			*g_pCharaImage_Bluejump;
	ID2D1Bitmap			*g_pCharaImage_Bluedown;
	ID2D1RenderTarget	*g_pRenderTarget;
	
	bool KeyFlag;
	bool ShotFlag;
	bool JumpFlag;
	unsigned char InvincibleTime;
	char FramePhase;
	float plus;
	char shotwait;
	char frameTime;
	void Scale(D2D1_RECT_F rc);
	/*void DEFOULTmove();
	void UPmove();
	void DOWNmove();
	void CHANGEmove();
	void DAMAGEmove();
	void DIEmove();*/
};

