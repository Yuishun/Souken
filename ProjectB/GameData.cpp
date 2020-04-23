#include "stdafx.h"
#include "GameData.h"

// 初期化
DifficultyPhase GameData::StagePhase = NOON;
unsigned int GameData::Score = 0;
char GameData::Purplegauge = 0;
bool GameData::PurpleTime = false;
char GameData::Stargauge = 0;

int GameData::PlayerHP = PHP_NUM;
COLOR GameData::NowPlayerColor = Red_;
ICOLOR GameData::Icolor = White;
bool GameData::PlayerDamage = false;
char GameData::StarShot = 0;
bool GameData::ShotFlag = false;
float GameData::PlayerPoint[4] = { 50,910,350,1030 };
PlayerPHASE GameData::PlayerPhase = DEFOULT;

float GameData::RunSpeed = 3.0f;

Shot GameData::shot[PSHOT_NUM];

unsigned char GameData::ItemCounter = 0;

// 静的変数を初期値にリセット
void GameData::Reset() {
	for (int i = 0; i < PSHOT_NUM; ++i) {
		shot[i].flag = false;
	}
	StagePhase = NOON;
	Score = 0;
	Purplegauge = 0;
	PurpleTime = 0;
	Stargauge = 0;

	PlayerHP = PHP_NUM;
	NowPlayerColor = Red_;
	Icolor = White;
	PlayerDamage = false;
	StarShot = 0;
	ShotFlag = false;
	PlayerPoint[0] = 300;
	PlayerPoint[1] = 910;
	PlayerPoint[2] = 600;
	PlayerPoint[3] = 1030;
	PlayerPhase = DEFOULT;

	RunSpeed = 3.f;

	ItemCounter = 0;
}