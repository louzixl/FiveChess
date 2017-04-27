#pragma once
#include "Game.h"

class CTable : public CWnd
{
	CImageList m_iml;
	int m_color;
	BOOL m_bWait;
	void Draw(int x, int y, int color);
	CGame *m_pGame;
public:
	void SetMenuState(BOOL bEnable);
	void RestoreWait();
	BOOL m_bOldWait;
	CString m_strMe;
	CString m_strAgainst;
	int m_data[15][15];
	CTable();
	~CTable();
	void Clear(BOOL bWait);
	void SetColor(int color);
	int GetColor() const;
	BOOL SetWait(BOOL bWait);
	void SetData(int x, int y, int color);
	BOOL Win(int color) const;
	void SetGameMode(int nGameMode);
	void Back();
	void StepOver();
	void Accept(int nGameMode);
	void Receive();
protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlag, CPoint point);
	DECLARE_MESSAGE_MAP()
};