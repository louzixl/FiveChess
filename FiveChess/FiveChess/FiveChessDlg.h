
// FiveChessDlg.h : 头文件
//

#pragma once
#include "Table.h"

// CFiveChessDlg 对话框
class CFiveChessDlg : public CDialogEx
{
// 构造
public:
	CDialog *m_pDlg;
	CTable m_Table;
	CFiveChessDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FIVECHESS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnMenuAbout();
	afx_msg void OnMenuPlayerfirst();
	afx_msg void OnMenuPcfirst();
	afx_msg void OnBnClickedBtnBack();
};
