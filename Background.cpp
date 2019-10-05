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
				printf("��");
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
	printf("������������ָ�ϡ�������");
	MoveCursorTo(X+1,nGaps);
	printf(" A��a������ת�����  ��");
	MoveCursorTo(X+2, nGaps);
	printf(" D��d������ת���ұ�  ��");
	MoveCursorTo(X+3, nGaps);
	printf(" W��w������ת���ϱ�  ��");
	MoveCursorTo(X+4, nGaps);
	printf(" S��s������ת���±�  ��");

	MoveCursorTo(X+6,nGaps);
	SetColor(0x0F);
	printf("O��o���������˶�    P��p����Ĭ���ٶ�");

	MoveCursorTo(X+7, nGaps);
	printf("�ո��������ͣ      Q��q�����˳�");


	SetColor(0x07);
	MoveCursorTo(X+10, nGaps);
	printf("����������ȡָ��ָ�ϡ�������");
	MoveCursorTo(X+11,nGaps);
	printf("1�����浵");
	MoveCursorTo(X+12,  nGaps);
	printf("2��������");
}

void CBackground::InfoBoard()
{
	int nGaps = 3;
	
	MoveCursorTo(0, GAME_COL + nGaps);
	printf("��������������INFO����������������");
	MoveCursorTo(2, GAME_COL + nGaps);
	SetColor(0x0E);
	printf("��ǰ�����ǣ�");
	OperInfo(6,nGaps + GAME_COL);



	
}