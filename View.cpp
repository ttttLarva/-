#include "stdafx.h"
#include"view.h"
#include<Windows.h>


void MoveCursorTo(int nRow, int nCol)
{
	COORD loc;
	loc.X = 2 * nCol;
	loc.Y = nRow;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);

}
void SetColor(int b)         //��ɫ����
{
	HANDLE hConsole = GetStdHandle((STD_OUTPUT_HANDLE));
	SetConsoleTextAttribute(hConsole, b);
}



