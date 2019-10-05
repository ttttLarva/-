#include "stdafx.h"
#include "Snake.h"
#include<stdlib.h>
#include"Game.h"


CSnake::CSnake()
{
	//初始化头结点
	tagSnakeNode* pHead = new tagSnakeNode(10, 10);
	m_Body.push_back(pHead);
	m_eDir = (eSNAKE_DIR)(rand()%4);
	AddNode();
	AddNode();
}


CSnake::~CSnake()
{
	for (size_t i = 0; i < m_Body.size(); i++)
	{
		if (m_Body[i] != nullptr)
		{
			delete m_Body[i];
			m_Body[i] = nullptr;
		}
		m_Body.clear();
	}
}


void CSnake::Show()
{
	SetColor(0x07);
	for (size_t i = 0; i < m_Body.size(); i++)
	{
		if (i==0)
		{
			m_Body[i]->Show("●");
		}
		else
		{
			m_Body[i]->Show("○");
		}
	}
}
void CSnake::Cover()
{
	for (size_t i = 0; i < m_Body.size(); i++)
	{
		m_Body[i]->Show("  ");
	}
}

void CSnake::AddNode()
{
	//无论如何先初始化一个结点，再对这个结点进行设置
	tagSnakeNode* pNewNode = new tagSnakeNode(0, 0);

	//如果只有一个结点，那么增长方向只和结点有关
	if (m_Body.size()==1)
	{
		int nHeadRow = m_Body[0]->m_nRow;
		int nHeadCol = m_Body[0]->m_nCol;
		switch (m_eDir)
		{
		case UP:
			pNewNode->SetXY(nHeadRow + 1, nHeadCol);
			break;
		case DOWN:
			pNewNode->SetXY(nHeadRow - 1, nHeadCol);
			break;
		case LEFT:
			pNewNode->SetXY(nHeadRow, nHeadCol + 1);
			break;
		case RIGHT:
			pNewNode->SetXY(nHeadRow, nHeadCol - 1);
			break;
		default:
			break;
		}
		m_Body.push_back(pNewNode);
		return;
	}

	//如果有多个结点，那么它与倒数第一个和倒数第二个的相对位置有关
	tagSnakeNode* pLastOne = m_Body[m_Body.size() - 1];
	tagSnakeNode* pLastTwo = m_Body[m_Body.size() - 2];

	if (pLastOne->m_nRow==pLastTwo->m_nRow
		&&pLastOne->m_nCol<pLastTwo->m_nCol)
	{
		//new 1 2
		pNewNode->SetXY(pLastOne->m_nRow, pLastOne->m_nCol - 1);
	}
	else if (pLastOne->m_nRow == pLastTwo->m_nRow
		&&pLastOne->m_nCol>pLastTwo->m_nCol)
	{
		//2 1 new
		pNewNode->SetXY(pLastOne->m_nRow, pLastOne->m_nCol + 1);
	}
	else if (pLastOne->m_nRow < pLastTwo->m_nRow
		&&pLastOne->m_nCol==pLastTwo->m_nCol)
	{
		/*
		new
		1
		2
		*/
		pNewNode->SetXY(pLastOne->m_nRow-1, pLastOne->m_nCol);
	}
	else if (pLastOne->m_nRow > pLastTwo->m_nRow
		&&pLastOne->m_nCol==pLastTwo->m_nCol)
	{
		/*
		2
		1
		new
		*/
		pNewNode->SetXY(pLastOne->m_nRow+1, pLastOne->m_nCol);
	}
	m_Body.push_back(pNewNode);
}


void CSnake::MoveOneStep()
{
	//移动策略：后一个结点的坐标，变成它的前一个结点的坐标，头部结点除外
	int nLastIndex = m_Body.size() - 1;

	while (nLastIndex!=0)
	{
		tagSnakeNode* pLast = m_Body[nLastIndex];
		tagSnakeNode* pPrev = m_Body[nLastIndex - 1];
		pLast->SetXY(pPrev->m_nRow, pPrev->m_nCol);
		//m_Body[nLastIndex]->SetXY(m_Body[nLastIndex - 1]->m_nRow, m_Body[nLastIndex - 1]->m_nCol);以上三句等于这一句，但是一点也不优雅
		nLastIndex--;
	}

	switch (m_eDir)
	{
	case UP:
		m_Body[0]->m_nRow--;
		break;
	case DOWN:
		m_Body[0]->m_nRow++;
		break;
	case LEFT:
		m_Body[0]->m_nCol--;
		break;
	case RIGHT:
		m_Body[0]->m_nCol++;
		break;
	default:
		break;
	}
}


void CSnake::ChangeDir(eSNAKE_DIR argDir)
{
	switch (m_eDir)
	{
	case UP:
		if (argDir==DOWN)
		{
			return;
		}
		break;
	case DOWN:
		if (argDir == UP)
		{
			return;
		}
		break;
	case LEFT:
		if (argDir == RIGHT)
		{
			return;
		}
		break;
	case RIGHT:
		if (argDir == LEFT)
		{
			return;
		}
		break;
	default:
		break;
	}
	m_eDir = argDir;
}


void CSnake::EatFood()
{
	if (m_pCurGame->IsCollision())
	{
		system("pause");
		return;
	}
	//如果吃到豆子就增加蛇的长度，并且为豆子更新
	CFood* pFood = m_pCurGame->m_pFood;
	tagSnakeNode* pHead = m_Body[0];
	if (pHead->m_nRow == pFood->m_nRow
		&&pHead->m_nCol == pFood->m_nCol)
	{
		Cover();
		AddNode();
		pFood->Refresh();
		Show();
		pFood->Show();
		m_pCurGame->m_nCurScore = m_pCurGame->m_nCurScore + 10;
	}


}
