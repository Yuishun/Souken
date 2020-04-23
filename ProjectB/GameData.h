#pragma once

typedef enum {
	NOON = 0,
	TWILIGHT = 1,
	NIGHT = 2,
	BLOODMOON = 3
}DifficultyPhase;

typedef enum {
	Red_ = 0,
	Blue_ = 1,
	Purple_ = 2
}COLOR;

typedef enum {
	White = 0,
	Paple = 1,
	Yellow = 2
}ICOLOR;

typedef enum {
	DEFOULT = 0,
	UP = 1,
	DOWN = 2,
	CHANGE = 3,
	DAMAGE = 4,
	FADE = 5,
	DIE = 6
} PlayerPHASE;
// 接地するY座標
#define TOPpoint_b 350.f
#define CENTERpoint_b 670.f
#define BOTTOMpoint_b 1030.f 

struct Shot {
	bool flag;		//弾が打たれているか
	float right;		//弾の右の座標
	float top;		//弾の上の座標
	COLOR Shotcolor;	//弾の色
};
#define SHOT_WIDTH 100.f
#define PSHOT_NUM 10
#define STAR_XLINE 1320.f 
#define PHP_NUM 2000

class GameData
{
public:
	static void Reset();
	static DifficultyPhase StagePhase;
	//UI関連
	static unsigned int Score;			//スコア
	static char Purplegauge;		//紫のゲージ用
	static bool PurpleTime;			//紫の効果が発動しているか
	static char Stargauge;      //必殺技ゲージ用
	//Player
	static int PlayerHP;     //プレイヤーの体力 //UIにも使う
	static COLOR NowPlayerColor; //今のプレイヤーの色
	static ICOLOR Icolor;		//アイテムの色
	static bool PlayerDamage;   //プレイヤーがダメージを受けたか
	static char StarShot;       //必殺技を使ったか  0->使ってない 1->演出中 2->効果発揮中
	static bool ShotFlag;		//ショットを打ったか
	static float PlayerPoint[4];   //プレイヤーの当たり判定の座標{left,top,right,bottom}
	static PlayerPHASE PlayerPhase; //プレイヤーの状態
	//BG
	static float RunSpeed;			//スピード
	//Shot
	static Shot shot[PSHOT_NUM];	//ショットの配列
	//Item
	static unsigned char ItemCounter;//アイテムの生成用
};

