#pragma once
#include"Food.h"
#include"Snake.h"
#include"Background.h"
#include"Replay.h"
#include"Logger.h"

class CGame
{
public:
	CSnake* m_pSnake;
	CBackground* m_pBackground;
	CFood* m_pFood;
	CLogger* m_pLogger;//定义一个记录仪器——在play的时候打开
	CReplay* m_pRepalyer;//定义一个读取器——在replay的时候打开
	static char* pszFileName;
	static int m_nCurScore;
	clock_t m_clkPlay;
	CGame();
	~CGame();

	void MainMenu();
	void MenuInfo();
	void ShowScore();
	void MainLoop();
	void ReplayLoop();
	bool IsCollision();
	void Save();
	void Load();
};

