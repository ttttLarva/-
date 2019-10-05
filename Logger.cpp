#include "stdafx.h"
#include "Logger.h"


CLogger::CLogger()
{
}


CLogger::~CLogger()
{
}
char* CLogger::pszFileName = "gamedata.dat";


void CLogger::OpenFile()
{
	m_pFile = fopen(pszFileName, "wb");
	if (m_pFile == nullptr)
	{
		perror("���ļ�ʧ��: ");
	}
	fseek(m_pFile, 0x20, SEEK_SET);//�ƶ���0x20
}

void CLogger::SaveRunTime(clock_t time)
{
	fseek(m_pFile, 0, SEEK_SET);
	fwrite(&time, sizeof(time), 1, m_pFile);
	fseek(m_pFile, 0x20, SEEK_SET);
}
void CLogger::SaveData(CFood* food, CSnake* snake, clock_t time)
{
	if (m_pFile==nullptr)
	{
		return;
	}
	//ʳ��
	fwrite(&food->m_nRow, 1, sizeof(food->m_nRow), m_pFile);
	fwrite(&food->m_nCol, 1, sizeof(food->m_nCol), m_pFile);
	fwrite(&food->m_nShapeID, 1, sizeof(food->m_nShapeID), m_pFile);
	fwrite(&food->m_nFoodColorID, 1, sizeof(food->m_nShapeID), m_pFile);
	//��:���ȡ����򡢽��
	int nCount = snake->m_Body.size();
	fwrite(&nCount, 1, sizeof(nCount), m_pFile);

	fwrite(&snake->m_eDir, 1, sizeof(snake->m_eDir), m_pFile);

	for (int i = 0; i < nCount; i++)
	{
		tagSnakeNode* pCurNode = snake->m_Body[i];

		fwrite(&pCurNode->m_nRow, 1,
			sizeof(pCurNode->m_nRow), m_pFile);
		fwrite(&pCurNode->m_nCol, 1,
			sizeof(pCurNode->m_nCol), m_pFile);
	}
	//ʱ��
	fwrite(&time, 1, sizeof(time), m_pFile);
}
void CLogger::CloseFile()
{
	if (m_pFile != nullptr)
	{
		fclose(m_pFile);
	}
}