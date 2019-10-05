#include "stdafx.h"
#include "Game.h"
#include<time.h>
#include<conio.h>
#include<Windows.h>
#include"Replay.h"

int CGame::m_nCurScore = 0;

CGame::CGame()
{
	m_pBackground = new CBackground();
	m_pFood = new CFood();
	m_pSnake = new CSnake();
	m_pLogger = new CLogger();
	m_pRepalyer = new CReplay();
	//����֪��������Ϸ����Ϣ������ȥ��ʳ��
	m_pSnake->m_pCurGame = this;
	m_clkPlay = 0;

	
}


CGame::~CGame()
{
	
	delete m_pLogger;
	delete m_pSnake;
	delete m_pFood;
	delete m_pBackground;
}

void CGame::ShowScore()
{
	MoveCursorTo(3, GAME_COL + 7);
	printf("%d", m_nCurScore);
	
}

void CGame::MainLoop()
{
	m_pBackground->Show();
	m_pFood->Show();
	m_pSnake->Show();
	MoveCursorTo(0, GAME_COL / 2-3);
	SetColor(0x0E);
	printf("��Ϸ��");
	SetColor(0x07);

	m_pBackground->InfoBoard();
	//���ļ���ʼ��¼
	m_pLogger->OpenFile();
	

	char chInput = 0;
	clock_t clkStart = clock();
	clock_t clkFinish = clock();
	int timeGap = 200;
	while (!IsCollision())
	{
		if (_kbhit() != 0)
		{
			chInput = _getch();
		}
		//chInput = getchar();
		clkFinish = clock();
		if (clkFinish - clkStart>timeGap)
		{
			//��¼����
			m_pLogger->SaveData(m_pFood, m_pSnake, clock());
			ShowScore();
			m_pSnake->Cover();
			m_pSnake->MoveOneStep();
			m_pSnake->Show();
			clkStart = clock();
		}
		switch (chInput)
		{
		case 'A':
		case 'a':
			m_pSnake->ChangeDir(LEFT);
			break;
		case 'D':
		case 'd':
			m_pSnake->ChangeDir(RIGHT);
			break;
		case 'S':
		case 's':
			m_pSnake->ChangeDir(DOWN);
			break;
		case 'W':
		case 'w':
			m_pSnake->ChangeDir(UP);
			break;
		case 'O':
		case 'o'://����
			timeGap = timeGap - 5;
			break;
		case 'P':
		case 'p'://�ָ��ٶ�
			timeGap = 200;
			break;
		case ' '://��ͣ
			system("pause");
			break;
		case '1':
			Save();
			break;
		case '2':
			Load();
			break;
		case 'Q':
		case 'q':
			m_clkPlay = clock();
			m_pLogger->SaveRunTime(clock());
			m_pLogger->CloseFile();
			MoveCursorTo(5, 10);
			printf("��Ϸ����");
			fflush(stdin);
			getchar();
			return;
		default:
			break;
		}
		//m_pLogger->SaveData(m_pFood, m_pSnake, clock());

		chInput = '\0';
		m_pSnake->EatFood();
		
		
		MoveCursorTo(29, 30);

	}

}


void CGame::ReplayLoop()
{
	
	m_pFood->Show();
	m_pBackground->Show();
	m_pSnake->Show();   
	MoveCursorTo(0, GAME_COL / 2-4);
	SetColor(0x0E);
	printf("��Ϸ�ط���");
	SetColor(0x07);

	clock_t clkCur = 0;
	clock_t clkRecord = 0;
	clock_t clkFinish = 0;
	//��ȡ��¼��
	m_pRepalyer->OpenFile(m_pLogger->pszFileName);

	m_pRepalyer->ReadRunTime(&clkFinish);

	//��ȡ�����ݸ��Ѿ���ʼ�����ߺ�ʳ�������Ҫ������ߺ�ʳ��




	//���߽�������
	while (true)
	{
		
		//����ԭ������Ϸ11
		m_pFood->Cover();
		m_pSnake->Cover();
		
		//�����
		for (size_t i = 0; i < m_pSnake->m_Body.size(); i++)
		{
			if (m_pSnake->m_Body[i] != nullptr)
			{
				delete m_pSnake->m_Body[i];
				m_pSnake->m_Body[i] = nullptr;
			}
			m_pSnake->m_Body.clear();
		}

		clkCur = clock();
		//��ȡ
		m_pRepalyer->ReadData(m_pFood, m_pSnake, &clkRecord);

		if (m_pSnake->m_Body.empty())
		{
			
			
			return;
		}
		m_pSnake->Show();
		m_pFood->Show();

		while (clkCur<clkRecord+m_clkPlay)
		{
			clkCur = clock();
		}

		m_pSnake->Cover();
		m_pFood->Cover();
		m_pSnake->MoveOneStep();
		m_pSnake->ChangeDir(m_pSnake->m_eDir);
		m_pSnake->Show();
		m_pFood->Show();


		
	}

}

bool CGame::IsCollision()
{
	//�õ���һ����㣬�ж��Ƿ�ײǽ
	tagSnakeNode* pHead = m_pSnake->m_Body[0];

	//�Ƿ�ײ��ǽ
	if (pHead->m_nRow == 0
		|| pHead->m_nCol == 0
		|| pHead->m_nRow == GAME_ROW - 1
		|| pHead->m_nCol == GAME_COL - 1)
	{
		m_pLogger->SaveRunTime(clock());
		m_pLogger->CloseFile();
		m_clkPlay = clock();
		return true;
	}

	//�ж��Ƿ�ײ���Լ�
	for (size_t i = 1; i < m_pSnake->m_Body.size(); i++)
	{
		if (pHead->m_nRow == m_pSnake->m_Body[i]->m_nRow
			&&pHead->m_nCol == m_pSnake->m_Body[i]->m_nCol)
		{
			m_pLogger->SaveRunTime(clock());
			m_pLogger->CloseFile();
			m_clkPlay = clock();
			return true;
		}
	}
	return false;
}
//�浵

char* CGame::pszFileName = "snakegame.dat";

void CGame::Save()
{
	FILE* pFile=nullptr;
	pFile = fopen(pszFileName, "wb");
	if (pFile==nullptr)
	{
		perror("�ļ���ʧ�ܣ�");
		return;
	}
	//�����
	fwrite(&m_nCurScore, 1, sizeof(m_nCurScore), pFile);
	//��ʳ��
	fwrite(&m_pFood->m_nRow, 1, sizeof(m_pFood->m_nRow), pFile);
	fwrite(&m_pFood->m_nCol, 1, sizeof(m_pFood->m_nCol), pFile);
	fwrite(&m_pFood->m_nShapeID, 1, sizeof(m_pFood->m_nShapeID), pFile);
	fwrite(&m_pFood->m_nFoodColorID, 1, sizeof(m_pFood->m_nShapeID), pFile);

	//���ߵ���Ϣ
	//���м������
	int nCount = m_pSnake->m_Body.size();
	fwrite(&nCount, 1, sizeof(nCount), pFile);
	
	//�ߵķ���
	fwrite(&m_pSnake->m_eDir, 1, sizeof(m_pSnake->m_eDir), pFile);

	for (int i = 0; i < nCount; i++)
	{
		tagSnakeNode* pCurNode = m_pSnake->m_Body[i];

		fwrite(&pCurNode->m_nRow, 1,
			sizeof(pCurNode->m_nRow), pFile);
		fwrite(&pCurNode->m_nCol, 1,
			sizeof(pCurNode->m_nCol), pFile);
	}
	fclose(pFile);
}


void CGame::Load()
{
	FILE* pFile = nullptr;
	pFile = fopen(pszFileName, "rb");
	if (pFile == nullptr)
	{
		perror("�ļ���ʧ�ܣ�");
		return;
	}
	
	//����ԭ������Ϸ
	m_pFood->Cover();
	m_pSnake->Cover();

	//�����
	for (size_t i = 0; i < m_pSnake->m_Body.size(); i++)
	{
		if (m_pSnake->m_Body[i]!=nullptr)
		{
			delete m_pSnake->m_Body[i];
			m_pSnake->m_Body[i] = nullptr;
		}
		m_pSnake->m_Body.clear();
	}

	//��ȡ����
	fread(&m_nCurScore, 1, sizeof(m_nCurScore), pFile);
	//��ȡʳ��
	fread(&m_pFood->m_nRow, 1, sizeof(m_pFood->m_nRow), pFile);
	fread(&m_pFood->m_nCol, 1, sizeof(m_pFood->m_nCol), pFile);
	fread(&m_pFood->m_nShapeID, 1, sizeof(m_pFood->m_nShapeID), pFile);
	fread(&m_pFood->m_nFoodColorID, 1, sizeof(m_pFood->m_nShapeID), pFile);
	//��ȡ�ߵ���Ϣ
	//��ȡ�м������
	int nCount = 0;
	fread(&nCount, 1, sizeof(nCount), pFile);
	//�ߵķ���
	fread(&m_pSnake->m_eDir, 1, sizeof(m_pSnake->m_eDir), pFile);

	for (int i = 0; i < nCount; i++)
	{
		tagSnakeNode* pNewNode = new tagSnakeNode(0,0);

		fread(&pNewNode->m_nRow, 1,
			sizeof(pNewNode->m_nRow), pFile);
		fread(&pNewNode->m_nCol, 1,
			sizeof(pNewNode->m_nCol), pFile);
		m_pSnake->m_Body.push_back(pNewNode);
	}
	fclose(pFile);
	m_pFood->Show();
	m_pSnake->Show();
}

void CGame::MenuInfo()
{
	system("cls");
	MoveCursorTo(0, 5);
	printf("����������������������������������������������������������");
	
	MoveCursorTo(1, 5);
	SetColor(0x0E);
	printf("-------------------------���˵�---------------------------");
	MoveCursorTo(2, 10);
	SetColor(0x0f);
	printf("1.������Ϸ");
	MoveCursorTo(3, 10);
	printf("2.�ط���Ϸ");
	MoveCursorTo(4, 10);
	printf("3.����ָ��");
	MoveCursorTo(5, 10);
	printf("4.�˳�");
	SetColor(0x07);
}

void CGame::MainMenu()
{
	

	while (true)
	{
		MenuInfo();
		char chInput = 0;
		fflush(stdin);
		scanf("%c", &chInput);

		switch (chInput)
		{
		case '1':
			system("cls");

			MainLoop();
			MoveCursorTo(5, 10);
			printf("��Ϸ����\r\n");
			MoveCursorTo(6, 10);
			printf("��ȷ�ϼ��˳�\r\n");
			fflush(stdin);
			getchar();
			break;
		case '2':
			system("cls");
			ReplayLoop();
			
			MoveCursorTo(5, 10);
			printf("�طŽ���\r\n");
			MoveCursorTo(6, 10);
			printf("��ȷ�ϼ��˳�\r\n");
			fflush(stdin);
			getchar();
			
			return;
			break;
		case '3':
			system("cls");
			m_pBackground->OperInfo(0,10);
			printf("\r\n");
			system("pause");
			break;
		case '4':
			return;
			break;
		default:
			break;
		}
	}
	
}