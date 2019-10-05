#include"stdafx.h"
#include"Replay.h"
#include<string.h>


CReplay::CReplay()
{
	m_pFile = nullptr;
	
}

CReplay::~CReplay()
{
	
}

void CReplay::OpenFile(char* argFileName)
{
	m_readFileName = new char[strlen(argFileName) + 1];
	strcpy(m_readFileName, argFileName);

	m_pFile = fopen(m_readFileName, "rb");
	if (m_pFile==nullptr)
	{
		perror("打开文件失败: ");
	}
}

void  CReplay::ReadRunTime(clock_t *time)
{
	fseek(m_pFile, 0, SEEK_SET);
	fread(time, sizeof(clock_t), 1, m_pFile);
	fseek(m_pFile, 0x20, SEEK_SET);

}
void CReplay::ReadData(CFood* food, CSnake* snake, clock_t *time)
{

	//食物
	fread(&food->m_nRow, 1, sizeof(food->m_nRow), m_pFile);
	fread(&food->m_nCol, 1, sizeof(food->m_nCol), m_pFile);
	fread(&food->m_nShapeID, 1, sizeof(food->m_nShapeID), m_pFile);
	fread(&food->m_nFoodColorID, 1, sizeof(food->m_nShapeID), m_pFile);
	//蛇:长度、方向、结点
	int nCount = snake->m_Body.size();
	fread(&nCount, 1, sizeof(nCount), m_pFile);

	fread(&snake->m_eDir, 1, sizeof(snake->m_eDir), m_pFile);

	for (int i = 0; i < nCount; i++)
	{
		tagSnakeNode* pNewNode = new tagSnakeNode(0, 0);

		fread(&pNewNode->m_nRow, 1,
			sizeof(pNewNode->m_nRow), m_pFile);
		fread(&pNewNode->m_nCol, 1,
			sizeof(pNewNode->m_nCol), m_pFile);
		snake->m_Body.push_back(pNewNode);
	}
	//时间
	fread(time, 1, sizeof(clock_t), m_pFile);
}
void CReplay::CloseFile()
{
	if (m_pFile!=nullptr)
	{
		fclose(m_pFile);
	}
}