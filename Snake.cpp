#include "stdafx.h"
#include "Snake.h"
#include<stdlib.h>
#include"Game.h"


CSnake::CSnake()
{
	//��ʼ��ͷ���
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
			m_Body[i]->Show("��");
		}
		else
		{
			m_Body[i]->Show("��");
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
	//��������ȳ�ʼ��һ����㣬�ٶ��������������
	tagSnakeNode* pNewNode = new tagSnakeNode(0, 0);

	//���ֻ��һ����㣬��ô��������ֻ�ͽ���й�
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

	//����ж����㣬��ô���뵹����һ���͵����ڶ��������λ���й�
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
	//�ƶ����ԣ���һ���������꣬�������ǰһ���������꣬ͷ��������
	int nLastIndex = m_Body.size() - 1;

	while (nLastIndex!=0)
	{
		tagSnakeNode* pLast = m_Body[nLastIndex];
		tagSnakeNode* pPrev = m_Body[nLastIndex - 1];
		pLast->SetXY(pPrev->m_nRow, pPrev->m_nCol);
		//m_Body[nLastIndex]->SetXY(m_Body[nLastIndex - 1]->m_nRow, m_Body[nLastIndex - 1]->m_nCol);�������������һ�䣬����һ��Ҳ������
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
	//����Ե����Ӿ������ߵĳ��ȣ�����Ϊ���Ӹ���
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
