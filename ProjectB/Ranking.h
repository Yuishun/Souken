#pragma once

#include "IGameScene.h"
#include "Selector.h"

#define NUM 200
#define TOP_NUM 5

struct Rank5 {
	char str[NUM];
};

class CRanking
{
public:
	CRanking();
	virtual ~CRanking();
	void DoRanking();
	UINT rank[TOP_NUM];
	int ranknum;	//+1����΂ǂ̏��ʂ��������킩��
};

