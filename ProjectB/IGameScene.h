#pragma once

enum GameSceneResultCode;
struct ID2D1RenderTarget;		//	Œ^Žw’è

class IGameScene
{
public:
	virtual ~IGameScene() = 0;
	virtual GameSceneResultCode		move() = 0;
	virtual void	draw(ID2D1RenderTarget *pRenderTarget) = 0;
};