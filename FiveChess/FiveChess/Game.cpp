#include "stdafx.h"
#include "Game.h"

CGame::~CGame()
{
}

void CGame::Win(const STEP &stepSend)
{
}

COneGame::~COneGame()
{
}

void COneGame::Init()
{
	//设置对手姓名
	m_pTable->GetParent()->SetDlgItemText(IDC_ST_ENEMY, _T("计算机"));

	//初始化获胜组合数组
	int i, j, k, nCount = 0;
	for (i = 0; i < 15; i++)                              //初始化获胜组合为false
	{
		for (j = 0; j < 15; j++)
		{
			for (k = 0; k < 572; k++)
			{
				m_Player[i][j][k] = false;
				m_Computer[i][j][k] = false;
			}
		}
	}
	for (i = 0; i < 2; i++)                               //初始化获胜组合中填入的棋子数为0
	{
		for (j = 0; j < 572; j++)
		{
			m_Win[i][j] = 0;
		}
	}
	for (i = 0; i < 15; i++)                              //获取纵向的获胜组合数
	{
		for (j = 0; j < 11; j++)
		{
			for (k = 0; k < 5; k++)
			{
				m_Player[j + k][i][nCount] = true;
				m_Computer[j + k][i][nCount] = true;
			}
			nCount++;
		}
	}
	for (i = 0; i < 15; i++)                              //获取横向的获胜组合数
	{
		for (j = 0; j < 11; j++)
		{
			for (k = 0; k < 5; k++)
			{
				m_Player[i][j + k][nCount] = true;
				m_Computer[i][j + k][nCount] = true;
			}
			nCount++;
		}
	}
	for (i = 0; i < 15; i++)                              //获取斜向的获胜组合数
	{
		for (j = 0; j < 11; j++)
		{
			for (k = 0; k < 5; k++)
			{
				m_Player[j + k][i + k][nCount] = true;
				m_Computer[j + k][i + k][nCount] = true;
			}
			nCount++;
		}
	}
	for (i = 0; i < 15; i++)                              //获取反斜向的获胜组合数
	{
		for (j = 0; j < 11; j++)
		{
			for (k = 0; k < 5; k++)
			{
				m_Player[j - k][i + k][nCount] = true;
				m_Computer[j - k][i + k][nCount] = true;
			}
			nCount++;
		}
	}
	if (1 == m_pTable->GetColor())                        //计算机先走
	{
		//让计算机占据天元
		m_pTable->SetData(7, 7, 0);
		PlaySound(MAKEINTRESOURCE(IDR_WAVE_PUT), NULL, SND_RESOURCE | SND_SYNC);
		m_bStart = false;
		for (i = 0; i < 572; i++)
		{
			//修改计算机下子后棋盘的变化状况
			if (m_Computer[7][7][i] && (m_Win[1][i] != -1))  //计算机天元位置需落子的获胜组合落子数+1
			{
				m_Win[1][i]++;
			}
			if (m_Player[7][7][i])                           //玩家天元位置需落子的获胜组合落子数置为-1
			{
				m_Player[7][7][i] = false;
				m_Win[0][i] = -1;
			}
		}
	}
	else
	{
		m_bStart = true;
	}
}

void COneGame::SendStep(const STEP &stepPut)
{
	int bestX, bestY, i, j, pi, pj, ptemp, ctemp, pscore = 10, cscore = -10000;
	int ctempTable[15][15], ptempTable[15][15];
	int m, n, temp1[20], temp2[20];

	pTable->GetParent()->GetDlgItem(IDC_BTN_BACK)->EnableWindow(FALSE);
	//保存先前数据，做悔棋之用
	for (i = 0; i < 572; i++)
	{
		m_nOldWin[0][i] = m_Win[0][i];
		m_nOldWin[1][i] = m_Win[1][i];
		m_bOldPlayer[i] = m_Player[stepPut.x][stepPut.y][i];
		m_bOldComputer[i] = m_Computer[stepPut.x][stepPut.y][i];
	}
	//修改玩家下子后棋盘状态的变化
	for (i = 0; i < 572; i++)
	{
		//修改状态变化
		if (m_Player[stepPut.x][stepPut.y][i] && (m_Win[0][i] != -1))  //玩家落子处可获胜的组合落子数+1
			m_Win[0][i]++;
		if (m_Computer[stepPut.x][stepPut.y][i])                       //玩家落子处计算机可获胜的组合落子数置为-1
		{
			m_Computer[stepPut.x][stepPut.y][i] = false;
			m_Win[1][i] = -1;
		}
	}
	if (m_bStart)
	{
		//手动确定计算机第一步：天元或(8, 8)
		if (-1 == m_pTable->m_data[7][7])
		{
			bestX = 7;
			bestY = 7;
		}
		else
		{
			bestX = 8;
			bestY = 8;
		}
		m_bStart = false;
	}
	else
	{
		STEP step;
		//寻找最佳位置
		GetTable(ctempTable, m_pTable->m_data);
		while (SearchBlank(i, j, ctempTable))
		{
			n = 0;
			pscore = 10;
			GetTable(ptempTable, m_pTable->m_data);
			ctempTable[i][j] = 2;                      //标记已被查找
			step.color = 1 - m_pTable->GetColor();
			step.x = i;
			step.y = j;
			ctemp = GiveScore(step);                   //给这个空位打分
			for (m = 0; m < 572; m++)
			{
				//暂时更改玩家信息
				if (m_Player[i][j][m])
				{
					temp1[n] = m;
					m_Player[i][j][m] = false;
					temp2[n] = m_Win[0][m];
					m_Win[0][m] = -1;
					n++;
				}
			}
			ptempTable[i][j] = 0;
			//TODO:
		}
	}
}