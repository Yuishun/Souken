#pragma once

enum GamePhase {
	GAMEPHASE_INIT = 0,
	GAMEPHASE_RESET = 1,
	GAMEPHASE_TITLE = 0x010,
	GAMEPHASE_GAMERULE = 0x050,
	GAMEPHASE_GAME = 0x100,
	GAMEPHASE_GAMEOVER = 0x200
};

enum GameSceneResultCode {
	GAMESCENE_DEFAULT = 0,
	GAMESCENE_END_OK = 1,
	GAMEPHASE_END_TIMEOUT = 2,
	GAMEPHASE_END_FAILURE = 3
};

class   IGameScene;		//	シーン管理
struct  ID2D1RenderTarget;
class CSelector
{
public:
	CSelector(ID2D1RenderTarget *pRenderTarget);
	virtual ~CSelector(void);
	void	doAnim();
	void	doDraw(ID2D1RenderTarget *pRenderTarget);
	ID2D1RenderTarget *GetRenderTarget();
protected:
	ID2D1RenderTarget	*m_pRenderTarget;
	IGameScene		*m_pScene;
	GamePhase		m_ePhase;
};

// マクロ定義
#undef SAFE_RELEASE
#undef SAFE_DELETE
#undef SAFE_DELETE_ARRAY
#define SAFE_RELEASE(o) if (o){ (o)->Release(); o = NULL; }
#define SAFE_DELETE(o)  if (o){ delete (o); o = NULL; }
#define SAFE_DELETE_ARRAY(o) if (o){ delete [] (o); o = NULL; }