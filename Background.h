#pragma once
#define GAME_ROW 30
#define GAME_COL 30
#define INFO_ROW 30
#define INFO_COL 10

class CBackground
{
public:
	char m_chBackground[GAME_ROW][GAME_COL];
	CBackground();
	~CBackground();
	void Show();
	void InfoBoard();
	void OperInfo(int X,int nGaps);
};

