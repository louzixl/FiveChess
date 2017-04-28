
// FiveChessDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FiveChess.h"
#include "FiveChessDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFiveChessDlg �Ի���

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


// CFiveChessDlg ��Ϣ�������

BOOL CFiveChessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_pDlg = NULL;
	CRect rect(0, 0, 200, 200);
	m_Table.CreateEx(WS_EX_CLIENTEDGE, _T("ChessTable"), NULL, WS_VISIBLE | WS_BORDER | WS_CHILD, 
		CRect(0, 0, 480, 509), this, IDC_TABLE);
	SetDlgItemText(IDC_ST_ME, m_Table.m_strMe);
	SetDlgItemText(IDC_ST_ENEMY, _T("�����"));
	CMenu *pMenu = GetMenu();
	pMenu->EnableMenuItem(ID_MENU_PLAYAGAIN, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND);
	pMenu->EnableMenuItem(ID_MENU_LEAVE, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND);
	m_Table.Clear(TRUE);
	GetDlgItem(IDC_BTN_BACK)->EnableWindow(FALSE);
	GetDlgItem(IDC_TABLE)->SetFocus();

	return FALSE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFiveChessDlg::OnPaint()
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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