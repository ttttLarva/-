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
	CLogger* m_pLogger;//����һ����¼����������play��ʱ���
	CReplay* m_pRepalyer;//����һ����ȡ��������replay��ʱ���
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

