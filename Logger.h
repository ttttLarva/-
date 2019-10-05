#pragma once
#include"Food.h"
#include"Snake.h"
#include<time.h>

class CLogger
{
public:
	CLogger();
	~CLogger();
	void OpenFile();
	void SaveData(CFood* food, CSnake* snake, clock_t time);
	void SaveRunTime(clock_t time);
	void CloseFile();
	FILE *m_pFile;
	static char* pszFileName;

};

