// CGuolvDlg.cpp: 实现文件
//

#include "stdafx.h"

#include "CGuolvDlg.h"

// CGuolvDlg 对话框

IMPLEMENT_DYNAMIC(CGuolvDlg, CDialogEx)

CGuolvDlg::CGuolvDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CGuolvDlg::~CGuolvDlg()
{
}

void CGuolvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	DDX_Control(pDX, IDC_CHECK1, d_tcp);
	DDX_Control(pDX, IDC_CHECK2, d_udp);
	DDX_Control(pDX, IDC_CHECK4, d_icmp);
	DDX_Control(pDX, IDC_CHECK5, d_igmp);
	DDX_Control(pDX, IDC_CHECK6, d_arp);
	DDX_Control(pDX, IDC_CHECK3, d_rarp);
	DDX_Control(pDX, IDC_CHECK7, d_all);
}


BEGIN_MESSAGE_MAP(CGuolvDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGuolvDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK5, &CGuolvDlg::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK4, &CGuolvDlg::OnBnClickedCheck4)
END_MESSAGE_MAP()


// CGuolvDlg 消息处理程序


BOOL CGuolvDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	d_all.SetCheck(0);
	d_tcp.SetCheck(0);
	d_udp.SetCheck(0);
	d_rarp.SetCheck(0);
	d_icmp.SetCheck(0);
	d_igmp.SetCheck(0);
	d_arp.SetCheck(0);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

CString guolvname;//过滤表达式
//得到过滤表达式
void CGuolvDlg::OnBnClickedOk()//选择过滤规则
{
	if (1 == d_all.GetCheck())
	{
		d_tcp.SetCheck(1);
		d_udp.SetCheck(1);
		d_rarp.SetCheck(1);
		d_icmp.SetCheck(1);
		d_igmp.SetCheck(1);
		d_arp.SetCheck(1);
	}
	// TODO: 在此添加控件通知处理程序代码
	if (1 == d_tcp.GetCheck())
	{
		guolvname += _T("(tcp and ip) or ");
	}
	if (1 == d_udp.GetCheck())
	{
		guolvname += _T("(udp and ip) or ");
	}
	if (1 == d_arp.GetCheck())   
     {   
		guolvname += _T("arp or ");
    }    
     if (1 == d_rarp.GetCheck())   
     {   
		 guolvname += _T("rarp or ");
     }   
     if (1 == d_icmp.GetCheck())   
     {   
		 guolvname += _T("(icmp and ip) or ");
     } 
     if (1 == d_igmp.GetCheck())   
     {   
		 guolvname += _T("(igmp and ip) or ");
     }  
     
	 guolvname = guolvname.Left(guolvname.GetLength()-4);  //注意去掉最后多余的" or ",否则过滤规则不成立
 

	CDialogEx::OnOK();
}
//确定过滤规则
CString CGuolvDlg::GetGuoLvName()
{
	return guolvname;
}


void CGuolvDlg::OnBnClickedCheck5()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CGuolvDlg::OnBnClickedCheck4()
{
	// TODO: 在此添加控件通知处理程序代码
}
