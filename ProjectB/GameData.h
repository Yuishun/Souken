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
// �ڒn����Y���W
#define TOPpoint_b 350.f
#define CENTERpoint_b 670.f
#define BOTTOMpoint_b 1030.f 

struct Shot {
	bool flag;		//�e���ł���Ă��邩
	float right;		//�e�̉E�̍��W
	float top;		//�e�̏�̍��W
	COLOR Shotcolor;	//�e�̐F
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
	//UI�֘A
	static unsigned int Score;			//�X�R�A
	static char Purplegauge;		//���̃Q�[�W�p
	static bool PurpleTime;			//���̌��ʂ��������Ă��邩
	static char Stargauge;      //�K�E�Z�Q�[�W�p
	//Player
	static int PlayerHP;     //�v���C���[�̗̑� //UI�ɂ��g��
	static COLOR NowPlayerColor; //���̃v���C���[�̐F
	static ICOLOR Icolor;		//�A�C�e���̐F
	static bool PlayerDamage;   //�v���C���[���_���[�W���󂯂���
	static char StarShot;       //�K�E�Z���g������  0->�g���ĂȂ� 1->���o�� 2->���ʔ�����
	static bool ShotFlag;		//�V���b�g��ł�����
	static float PlayerPoint[4];   //�v���C���[�̓����蔻��̍��W{left,top,right,bottom}
	static PlayerPHASE PlayerPhase; //�v���C���[�̏��
	//BG
	static float RunSpeed;			//�X�s�[�h
	//Shot
	static Shot shot[PSHOT_NUM];	//�V���b�g�̔z��
	//Item
	static unsigned char ItemCounter;//�A�C�e���̐����p
};

