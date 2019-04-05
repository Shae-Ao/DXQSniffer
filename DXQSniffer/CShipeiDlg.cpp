//CShipeiDlg.cpp: 实现文件
//
/*
#include "stdafx.h"
#include "pcap.h"
#include "CShipeiDlg.h"
#include "DXQSniffer.h"
#include "afxdialogex.h"
#include "DXQSnifferDlg.h"
*/
#include "stdafx.h"
#include "CShipeiDlg.h"

// CShipeiDlg 对话框

IMPLEMENT_DYNAMIC(CShipeiDlg, CDialogEx)

CShipeiDlg::CShipeiDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CShipeiDlg::~CShipeiDlg()
{
}

void CShipeiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, d_check1);
	DDX_Control(pDX, IDC_EDIT1, d_edit1);
	DDX_Control(pDX, IDC_LIST1, d_list1);

	//  DDX_Control(pDX, IDOK, d_ok);
}


BEGIN_MESSAGE_MAP(CShipeiDlg, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CShipeiDlg::OnNMClickList1)
	ON_BN_CLICKED(IDOK, &CShipeiDlg::OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CShipeiDlg::OnLvnItemchangedList1)
//	ON_EN_CHANGE(IDC_EDIT1, &CShipeiDlg::OnEnChangeEdit1)
ON_BN_CLICKED(IDC_CHECK1, &CShipeiDlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CShipeiDlg 消息处理程序

//pcap_if_t * alldevs = new pcap_if_t();//设备索引指针
//pcap_if_t * d = new pcap_if_t();//设备移动指针
CString shipeiname;//已选择设备名称
BOOL CShipeiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	d_list1.SetExtendedStyle(d_list1.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	d_list1.InsertColumn(0, _T("设备名"), LVCFMT_CENTER, 500);
	d_list1.InsertColumn(1, _T("设备描述"), LVCFMT_CENTER, 400);
	

	d_check1.SetCheck(1);//将设置混杂模式的单选框初始为选中状态

	//获取设备列表
	char errbuf[PCAP_ERRBUF_SIZE];
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1)
		return FALSE;
	for (d = alldevs; d; d = d->next)
	{
		
		d_list1.InsertItem(0, (CString)d->name);
		d_list1.SetItemText(0, 1, (CString)d->description);
	}
	d = NULL;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CShipeiDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;
	if (-1 != pNMListView->iItem)
	{
		shipeiname = d_list1.GetItemText(pNMListView->iItem, 0);//获取选择适配器名称
		SetDlgItemText(IDC_EDIT1, shipeiname);//将选择的适配器名称显示在编辑框中
	}
}
//返回选择设备
pcap_if_t* CShipeiDlg::GetDevice()
{
	if (shipeiname)
	{
		for (d = alldevs; d; d = d->next)
			if (d->name == shipeiname)
				return d;
	}
	return NULL;
}

void CShipeiDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	d = GetDevice();
	if (d)
	{
		MessageBox(_T("网卡绑定成功！"));
		CDialogEx::OnOK();
	}
	else
		MessageBox(_T("网卡没有绑定，请选择网卡！"));
}
pcap_if_t* CShipeiDlg::Returnd()
{
	return d;
}


void CShipeiDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}




void CShipeiDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (d_check1.GetCheck() == 0)//不设置混杂模式
	{
		AfxMessageBox(_T("请选择“混杂模式”选项"));
		d_check1.SetCheck(1);
	}
	
}
