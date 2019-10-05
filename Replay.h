#pragma once
#include"Food.h"
#include"Snake.h"
#include<time.h>
#include<vector>

using namespace std;


enum eKey_Dir
{
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_NULL,//记录无按键蛇自己走的情况
};



struct tagSnakeData
{
	int m_NodeCount;
	eSNAKE_DIR m_eDir;//4
	//eKey_Dir m_KeyInfo;//4
	vector<tagSnakeNode*> m_Body;//
	
};

struct tagFoodData
{
	int m_nRow;
	int m_nCol;
	int m_nShapeID;
	int m_nFoodColorID;
};//16

class CReplay
{
public:
	void OpenFile(char* argFileName);
	void ReadData(CFood* food, CSnake* snake, clock_t *time);//需要传出时间
	void ReadRunTime(clock_t *time);
	void CloseFile();
	FILE *m_pFile;
	char *m_readFileName;
	CReplay();
	~CReplay();


private:

};



