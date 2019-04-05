#pragma once


// CGuolvDlg 对话框

#include "DXQSniffer.h"

#include "afxdialogex.h"

class CGuolvDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGuolvDlg)

public:
	CGuolvDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGuolvDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CButton d_tcp;
	CButton d_udp;

	CButton d_icmp;
	CButton d_igmp;
	CButton d_arp;
	CButton d_rarp;
	afx_msg void OnBnClickedOk();
	CString GetGuoLvName();//确定过滤表达式
	CButton d_all;
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck4();
};
