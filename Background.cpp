#include "stdafx.h"
#include"View.h"
#include "Background.h"
#include<Windows.h>

CBackground::CBackground()
{
	for (int nRow = 0; nRow < GAME_ROW; nRow++)
	{
		for (int nCol = 0; nCol < GAME_COL; nCol++)
		{
			if (nRow == GAME_ROW - 1
				|| nRow == 0
				|| nCol == 0
				|| nCol == GAME_COL - 1)
			{
				m_chBackground[nRow][nCol] = 1;
			}
			else
			{
				m_chBackground[nRow][nCol] = 0;
			}
		}

	}
}


CBackground::~CBackground()
{
}


void CBackground::Show()
{
	for (int nRow = 0; nRow < GAME_ROW; nRow++)
	{
		for (int nCol = 0; nCol < GAME_COL; nCol++)
		{
			if (m_chBackground[nRow][nCol] == 1)
			{
				MoveCursorTo(nRow, nCol);
				printf("■");
			}
			else
			{

			}
		}

	}
	
}
void CBackground::OperInfo(int X,int nGaps)
{
	SetColor(0x07);
	MoveCursorTo(X, nGaps);
	printf("～～～～操作指南～～～～");
	MoveCursorTo(X+1,nGaps);
	printf(" A、a——蛇转向左边  ←");
	MoveCursorTo(X+2, nGaps);
	printf(" D、d——蛇转向右边  →");
	MoveCursorTo(X+3, nGaps);
	printf(" W、w——蛇转向上边  ↑");
	MoveCursorTo(X+4, nGaps);
	printf(" S、s——蛇转向下边  ↓");

	MoveCursorTo(X+6,nGaps);
	SetColor(0x0F);
	printf("O、o——加速运动    P、p——默认速度");

	MoveCursorTo(X+7, nGaps);
	printf("空格键——暂停      Q、q——退出");


	SetColor(0x07);
	MoveCursorTo(X+10, nGaps);
	printf("～～～～读取指南指南～～～～");
	MoveCursorTo(X+11,nGaps);
	printf("1——存档");
	MoveCursorTo(X+12,  nGaps);
	printf("2——读档");
}

void CBackground::InfoBoard()
{
	int nGaps = 3;
	
	MoveCursorTo(0, GAME_COL + nGaps);
	printf("■■■■■■■INFO■■■■■■■■");
	MoveCursorTo(2, GAME_COL + nGaps);
	SetColor(0x0E);
	printf("当前分数是：");
	OperInfo(6,nGaps + GAME_COL);



	
}