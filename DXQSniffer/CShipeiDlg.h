#pragma once


// CShipeiDlg 对话框
//为了避免头文件相互包含问题，把本身头文件和包含的另一个头文件分别放于.cpp和.h文件中

#include "pcap.h"
#include "DXQSniffer.h"
#include "afxdialogex.h"
#include "DXQSnifferDlg.h"

class CShipeiDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShipeiDlg)

public:
	CShipeiDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CShipeiDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton d_check1;
	CEdit d_edit1;
	CListCtrl d_list1;
//	CButton d_cancel;
//	CButton d_ok;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
    pcap_if_t *GetDevice(void);
	pcap_if_t *Returnd();
	
private:
	
	//pcap_if_t * alldevs = new pcap_if_t();//设备指针
	//pcap_if_t * d = new pcap_if_t();
	//CString shipeiname;//已选择设备名称
/*
public:
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnEnChangeEdit1();*/
public:
	pcap_if_t * alldevs = new pcap_if_t();//设备索引指针
	pcap_if_t * d = new pcap_if_t();//设备移动指针
	afx_msg void OnBnClickedCheck1();
	
};
