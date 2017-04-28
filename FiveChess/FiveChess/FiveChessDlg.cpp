
// FiveChessDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FiveChess.h"
#include "FiveChessDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFiveChessDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	enum {IDD = IDD_ABOUTBOX};

protected:
	virtual void DoDataExchange(CDataExchange *pDX);

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() :CDialogEx(CAboutDlg::IDD)
{}

void CAboutDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()



CFiveChessDlg::CFiveChessDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFiveChessDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFiveChessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFiveChessDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENU_ABOUT, &CFiveChessDlg::OnMenuAbout)
	ON_COMMAND(ID_MENU_PlayerFirst, &CFiveChessDlg::OnMenuPlayerfirst)
	ON_COMMAND(ID_MENU_PCFirst, &CFiveChessDlg::OnMenuPcfirst)
	ON_BN_CLICKED(IDC_BTN_BACK, &CFiveChessDlg::OnBnClickedBtnBack)
END_MESSAGE_MAP()


// CFiveChessDlg 消息处理程序

BOOL CFiveChessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_pDlg = NULL;
	CRect rect(0, 0, 200, 200);
	m_Table.CreateEx(WS_EX_CLIENTEDGE, _T("ChessTable"), NULL, WS_VISIBLE | WS_BORDER | WS_CHILD, 
		CRect(0, 0, 480, 509), this, IDC_TABLE);
	SetDlgItemText(IDC_ST_ME, m_Table.m_strMe);
	SetDlgItemText(IDC_ST_ENEMY, _T("计算机"));
	CMenu *pMenu = GetMenu();
	pMenu->EnableMenuItem(ID_MENU_PLAYAGAIN, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND);
	pMenu->EnableMenuItem(ID_MENU_LEAVE, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND);
	m_Table.Clear(TRUE);
	GetDlgItem(IDC_BTN_BACK)->EnableWindow(FALSE);
	GetDlgItem(IDC_TABLE)->SetFocus();

	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFiveChessDlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFiveChessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFiveChessDlg::OnMenuAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}

void CFiveChessDlg::OnMenuPlayerfirst()
{
	GetDlgItem(IDC_BTN_BACK)->EnableWindow(FALSE);
	m_Table.Accept(1);
}

void CFiveChessDlg::OnMenuPcfirst()
{
	GetDlgItem(IDC_BTN_BACK)->EnableWindow(FALSE);
	m_Table.SetColor(1);
	m_Table.Clear(FALSE);
	m_Table.SetGameMode(1);
}

void CFiveChessDlg::OnBnClickedBtnBack()
{
	m_Table.Back();
}