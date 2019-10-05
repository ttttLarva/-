#include "stdafx.h"
#include "Food.h"
#include"Background.h"
#include"View.h"
#include<stdlib.h>

char* CFood::FoodPool[SHAPE_NUMS] = { "¡ï", "¨‹", "¡ï", "¡ø", "¡ö" };
int CFood::ColorPool[COLOR_NUMS] = { 0x02, 0x03, 0x04, 0x05, 0x06 };

CFood::CFood()
{
	Refresh();
	
}


CFood::~CFood()
{
}


void CFood::Refresh()
{
	m_nRow = (rand() % (GAME_ROW - 2)) + 1;
	m_nCol = (rand() % (GAME_COL - 2)) + 1;
	m_nShapeID = rand() % (SHAPE_NUMS);
	m_nFoodColorID = rand() % 4;
}
void CFood::Show()
{
	SetColor(ColorPool[m_nFoodColorID]);
	MoveCursorTo(m_nRow, m_nCol);

	printf(FoodPool[m_nShapeID]);
}
void CFood::Cover()
{
	MoveCursorTo(m_nRow, m_nCol);
	printf("  ");
}
