
// DXQSnifferDlg.h: 头文件
//
#pragma warning(disable:4996)
#pragma once
#include "pcap.h"
#include "windows.h"
using namespace std;

#include "DXQSniffer.h"
#include "afxdialogex.h"

#include "CGuolvDlg.h"
#include "CShipeiDlg.h"
#include "CGuanyuDlg.h"
#include "xieyi.h"

// CDXQSnifferDlg 对话框
class CDXQSnifferDlg : public CDialogEx
{
// 构造
public:
	CDXQSnifferDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DXQSNIFFER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit d_edit1;

	CListCtrl d_list1;
	CTreeCtrl d_tree1;
	CButton d_button2;
	CButton d_button3;
	afx_msg void On1();
	afx_msg void On2();
	afx_msg void OnBnClickedButton1();
	CButton d_button1;

	HANDLE thread;

	CString d_tcpnum;
	CString d_arpnum;
	CString d_rarpnum;
	CString d_allnum;
	CString d_udpnum;
	CString d_ftpnum;
	CString d_icmpnum;
	CString d_igmpnum;
	pcap_if_t * d_pDevice;//选择的设备
	bool d_pFlag;//点击开始捕获时变量为true，点击停止捕获时变量为false
	char d_guolvname[1024];//过滤表达式字串
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	/*将数据包概要信息展示到list control控件中*/
	void ShowPacketList(const pcap_pkthdr * pkt_header, const u_char*pkt_data);
	/*将数据包详细信息展示到tree control控件中*/
	void ShowPacketTree(const pcap_pkthdr*pkt_header, const u_char*pkt_data, long index);
	void ShowPckNum();//展示数据包数量
private:
	CArray<const struct pcap_pkthdr*, const struct pcap_pkthdr*>d_pktHeaders;//协议头部
	CArray<const u_char*, const u_char*>d_pktDatas;//协议数据
	long d_tcpcount;
	long d_udpcount;
	long d_arpcount;
	long d_rarpcount;
	long d_icmpcount;
	long d_igmpcount;
	long d_allcount;
	long d_ftpcount;
public:
	afx_msg void On32774();

	
	
};