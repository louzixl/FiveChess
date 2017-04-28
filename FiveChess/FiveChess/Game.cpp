#include "stdafx.h"
#include "FiveChess.h"
#include "Game.h"
#include "Table.h"
#include "Message.h"
#include "Resource.h"

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

	m_pTable->GetParent()->GetDlgItem(IDC_BTN_BACK)->EnableWindow(FALSE); //悔棋按钮冻结
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
					temp1[n] = m;                   //第m组获胜组合
					m_Player[i][j][m] = false;
					temp2[n] = m_Win[0][m];         //第m组获胜组合已下子数
					m_Win[0][m] = -1;
					n++;
				}
			}
			ptempTable[i][j] = 0;
			
			pi = i;
			pj = j;
			while (SearchBlank(i, j, ptempTable))    //该部分表示玩家若下某个地方会得多少分，分数越小，对计算机越有利
			{
				ptempTable[i][j] = 2; //标记已被查找
				step.color = m_pTable->GetColor();
				step.x = i;
				step.y = j;
				ptemp = GiveScore(step);
				if (pscore > ptemp)
				{
					pscore = ptemp;
				}
			}
			for (m = 0; m < n; m++)       //恢复玩家信息
			{
				m_Player[pi][pj][temp1[m]] = true;
				m_Win[0][temp1[m]] = temp2[m];
			}
			if (ctemp + pscore > cscore)  //根据得分情况确定最佳落子位置
			{
				cscore = ctemp + pscore;
				bestX = pi;
				bestY = pj;
			}
		}
	}
	m_step.color = 1 - m_pTable->GetColor();
	m_step.x = bestX;
	m_step.y = bestY;
	for (i = 0; i < 572; i++)
	{
		if (m_Computer[bestX][bestY][i] && m_Win[1][i] != -1)
		{
			m_Win[1][i]++;
		}
		if (m_Player[bestX][bestY][i])
		{
			m_Player[bestX][bestY][i] = false;
			m_Win[0][i] = -1;
		}
	}
	m_pTable->GetParent()->GetDlgItem(IDC_BTN_BACK)->EnableWindow(); //悔棋按钮激活
	m_pTable->Receive();
}

/**
* 仅能悔一步棋
**/
void COneGame::Back()
{
	int i;
	STEP step;

	//悔掉计算机最后一步棋
	step = *(m_StepList.begin());
	m_StepList.pop_front();
	m_pTable->m_data[step.x][step.y] = -1;
	for (i = 0; i < 572; i++)
	{
		m_Win[0][i] = m_nOldWin[0][i];
		m_Win[1][i] = m_nOldWin[1][i];
		m_Player[step.x][step.y][i] = m_bOldPlayer[i];
	}

	//悔掉玩家最后一步棋
	step = *(m_StepList.begin());
	m_StepList.pop_front();
	m_pTable->m_data[step.x][step.y] = -1;
	for (i = 0; i < 572; i++)
	{
		m_Computer[step.x][step.y][i] = m_bOldComputer[i];
	}
	m_pTable->Invalidate();
	AfxGetMainWnd()->GetDlgItem(IDC_BTN_BACK)->EnableWindow(FALSE);
}

int COneGame::GiveScore(const STEP &stepPut)
{
	int i, nScore = 0;
	for (i = 0; i < 572; i++)
	{
		if (m_pTable->GetColor() == stepPut.color)
		{
			if (m_Player[stepPut.x][stepPut.y][i])
			{
				switch (m_Win[0][i])
				{
				case 1:
					nScore -= 5;
					break;
				case 2:
					nScore -= 50;
					break;
				case 3:
					nScore -= 500;
					break;
				case 4:
					nScore -= 5000;
					break;
				default:
					break;
				}
			}
		}
		else
		{
			if (m_Computer[stepPut.x][stepPut.y][i])
			{
				switch (m_Win[1][i])
				{
				case 1:
					nScore += 5;
					break;
				case 2:
					nScore += 50;
					break;
				case 3:
					nScore += 100;
					break;
				case 4:
					nScore += 10000;
					break;
				default:
					break;
				}
			}
		}
	}
	return nScore;
}

void COneGame::GetTable(int tempTable[][15], int nowTable[][15])
{
	int i, j;
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
		{
			tempTable[i][j] = nowTable[i][j];
		}
	}
}

bool COneGame::SearchBlank(int &i, int &j, int nowTable[][15])
{
	int x, y;
	for (x = 0; x < 15; x++)
	{
		for (y = 0; y < 15; y++)
		{
			if (nowTable[x][y] == -1 && nowTable[x][y] != 2)
			{
				i = x;
				j = y;
				return true;
			}
		}
	}
	return false;
}

void COneGame::ReceiveMsg(MSGSTRUCT *pMsg)
{}