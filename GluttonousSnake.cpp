// GluttonousSnake.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<Windows.h>
#include<time.h>
#include"View.h"
#include"Snake.h"
#include"Food.h"
#include"Game.h"
#include"Replay.h"

int _tmain(int argc, _TCHAR* argv[])
{
	srand((unsigned)time(NULL));

	
	CGame MyGame;
	MyGame.MainMenu();

	

	return 0;
}

