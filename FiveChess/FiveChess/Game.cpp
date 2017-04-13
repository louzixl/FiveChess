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
	//���ö�������
	m_pTable->GetParent()->SetDlgItemText(IDC_ST_ENEMY, _T("�����"));

	//��ʼ����ʤ�������
	int i, j, k, nCount = 0;
	for (i = 0; i < 15; i++)                              //��ʼ����ʤ���Ϊfalse
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
	for (i = 0; i < 2; i++)                               //��ʼ����ʤ����������������Ϊ0
	{
		for (j = 0; j < 572; j++)
		{
			m_Win[i][j] = 0;
		}
	}
	for (i = 0; i < 15; i++)                              //��ȡ����Ļ�ʤ�����
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
	for (i = 0; i < 15; i++)                              //��ȡ����Ļ�ʤ�����
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
	for (i = 0; i < 15; i++)                              //��ȡб��Ļ�ʤ�����
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
	for (i = 0; i < 15; i++)                              //��ȡ��б��Ļ�ʤ�����
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
	if (1 == m_pTable->GetColor())                        //���������
	{
		//�ü����ռ����Ԫ
		m_pTable->SetData(7, 7, 0);
		PlaySound(MAKEINTRESOURCE(IDR_WAVE_PUT), NULL, SND_RESOURCE | SND_SYNC);
		m_bStart = false;
		for (i = 0; i < 572; i++)
		{
			//�޸ļ�������Ӻ����̵ı仯״��
			if (m_Computer[7][7][i] && (m_Win[1][i] != -1))  //�������Ԫλ�������ӵĻ�ʤ���������+1
			{
				m_Win[1][i]++;
			}
			if (m_Player[7][7][i])                           //�����Ԫλ�������ӵĻ�ʤ�����������Ϊ-1
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
	//������ǰ���ݣ�������֮��
	for (i = 0; i < 572; i++)
	{
		m_nOldWin[0][i] = m_Win[0][i];
		m_nOldWin[1][i] = m_Win[1][i];
		m_bOldPlayer[i] = m_Player[stepPut.x][stepPut.y][i];
		m_bOldComputer[i] = m_Computer[stepPut.x][stepPut.y][i];
	}
	//�޸�������Ӻ�����״̬�ı仯
	for (i = 0; i < 572; i++)
	{
		//�޸�״̬�仯
		if (m_Player[stepPut.x][stepPut.y][i] && (m_Win[0][i] != -1))  //������Ӵ��ɻ�ʤ�����������+1
			m_Win[0][i]++;
		if (m_Computer[stepPut.x][stepPut.y][i])                       //������Ӵ�������ɻ�ʤ�������������Ϊ-1
		{
			m_Computer[stepPut.x][stepPut.y][i] = false;
			m_Win[1][i] = -1;
		}
	}
	if (m_bStart)
	{
		//�ֶ�ȷ���������һ������Ԫ��(8, 8)
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
		//Ѱ�����λ��
		GetTable(ctempTable, m_pTable->m_data);
		while (SearchBlank(i, j, ctempTable))
		{
			n = 0;
			pscore = 10;
			GetTable(ptempTable, m_pTable->m_data);
			ctempTable[i][j] = 2;                      //����ѱ�����
			step.color = 1 - m_pTable->GetColor();
			step.x = i;
			step.y = j;
			ctemp = GiveScore(step);                   //�������λ���
			for (m = 0; m < 572; m++)
			{
				//��ʱ���������Ϣ
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