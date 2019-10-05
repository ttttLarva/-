#pragma once


#include"View.h"
#include<vector>

using namespace std;

enum eSNAKE_DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};


struct tagSnakeNode
{
	int m_nRow;
	int m_nCol;
	tagSnakeNode(int nRow, int nCol) :m_nRow(nRow), m_nCol(nCol)
	{};
	void SetXY(int nRow, int nCol)
	{
		m_nRow = nRow;
		m_nCol = nCol;
	}
	void Show(char* argShape)
	{
		MoveCursorTo(m_nRow, m_nCol);
		printf(argShape);
	}
};

class CGame;

class CSnake
{
public:
	
	vector<tagSnakeNode*> m_Body;
	eSNAKE_DIR m_eDir;
	CGame* m_pCurGame;

	CSnake();
	~CSnake();
	void Show();
	void Cover();
	void AddNode();
	void MoveOneStep();
	void ChangeDir(eSNAKE_DIR argDir);
	void EatFood();
};

