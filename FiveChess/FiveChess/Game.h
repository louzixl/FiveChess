#pragma once
#include "afx.h"
#include <list>
#include "Message.h"

class CTable;

class CGame : public CObject
{
protected:
	CTable *m_pTable;
public:
	std::list<STEP> m_StepList;
public:
	CGame(CTable *pTable) :m_pTable(pTable) {}
	virtual ~CGame();
	virtual void Init() = 0;
	virtual void Win(const STEP &stepSend);
	virtual void SendStep(const STEP &stepSend) = 0;
	virtual void ReceiveMsg(MSGSTRUCT *pMsg) = 0;
	virtual void Back() = 0;
};

class COneGame :public CGame
{
	bool m_Computer[15][15][572];  //�������ʤ���
	bool m_Player[15][15][572];    //��һ�ʤ���
	int m_Win[2][572];             //������ʤ����������������
	bool m_bStart;                 //��Ϸ�Ƿ�ոտ�ʼ
	STEP m_step;                   //�������ӽ��
	bool m_bOldPlayer[572];        //��������
	bool m_bOldComputer[572];
	int m_nOldWin[2][572];

public:
	COneGame(CTable *pTable) :CGame(pTable) {}
	virtual ~COneGame();
	virtual void Init();
	virtual void SendStep(const STEP &stepSend);
	virtual void ReceiveMsg(MSGSTRUCT *pMsg);
	virtual void Back();

private:
	int GiveScore(const STEP &stepPut);
	void GetTable(int tempTable[][15], int nowTable[][15]);
	bool SearchBlank(int &i, int &j, int nowTable[][15]);
};