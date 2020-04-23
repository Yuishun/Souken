#include "stdafx.h"
#include "Ranking.h"
#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include "GameData.h"

#define FILENAME "res\\Ranking.txt"

CRanking::CRanking()
{
	ranknum = -1;
}


CRanking::~CRanking()
{
}

void CRanking::DoRanking() {
	FILE *fp = NULL;
	Rank5 Top[TOP_NUM];
	char *p;
	struct stat st;
	if (0 != stat(FILENAME, &st)) {	//�@��Ԋm�F
		if (0 == fopen_s(&fp, FILENAME, "w")) {//�@�t�@�C�����Ȃ���΍쐬
			fprintf(fp, "%d\n", GameData::Score);
			fclose(fp);
		}
	}
	else {
		UINT nowscore = GameData::Score;
		if (0 == fopen_s(&fp, FILENAME, "r+")) {//�ǂݍ���
			for (int i = 0; i < TOP_NUM; ++i) {
				if (fgets(Top[i].str, NUM, fp) == NULL)
					break;
				p = strchr(Top[i].str, '\n');
				if (p != NULL)
					*p = '\0';
				rank[i] = atoi(Top[i].str);
			}
			
			for (int i = TOP_NUM-1; i >= 0; --i) {//���ʌ���
				if (nowscore < rank[i])
					break;
				else if (nowscore >= rank[i]) {
					ranknum = i;
					rank[TOP_NUM - 1] = nowscore;
				}
			}
			if (ranknum > -1) {
				for (int i = TOP_NUM-1; i > ranknum; --i) {//����ւ�
					UINT n = rank[i];
					rank[i] = rank[i - 1];
					rank[i - 1] = n;
				}
				rewind(fp);	//�t�@�C���|�C���^��擪��
				for (int i = 0; i < TOP_NUM; ++i) {//��������
					fprintf(fp, "%u\n", rank[i]);
				}
			}
		}
		fclose(fp);
	}
}