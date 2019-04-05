
// DXQSnifferDlg.cpp: 实现文件
//

#include "stdafx.h"

#include "DXQSnifferDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDXQSnifferDlg 对话框



CDXQSnifferDlg::CDXQSnifferDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DXQSNIFFER_DIALOG, pParent)
	, d_pDevice(NULL)
	, d_pFlag(false)
	, d_tcpnum(_T(""))
	, d_arpnum(_T(""))
	, d_rarpnum(_T(""))
	, d_allnum(_T(""))
	, d_udpnum(_T(""))
	, d_ftpnum(_T(""))
	, d_icmpnum(_T(""))
	, d_igmpnum(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDXQSnifferDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, d_edit1);
	
	DDX_Control(pDX, IDC_LIST1, d_list1);
	DDX_Control(pDX, IDC_TREE1, d_tree1);
	DDX_Control(pDX, IDC_BUTTON2, d_button2);
	DDX_Control(pDX, IDC_BUTTON3, d_button3);
	DDX_Control(pDX, IDC_BUTTON1, d_button1);

	DDX_Text(pDX, IDC_EDIT4, d_tcpnum);
	DDX_Text(pDX, IDC_EDIT10, d_arpnum);
	DDX_Text(pDX, IDC_EDIT11, d_rarpnum);
	DDX_Text(pDX, IDC_EDIT5, d_allnum);
	DDX_Text(pDX, IDC_EDIT6, d_udpnum);
	DDX_Text(pDX, IDC_EDIT7, d_ftpnum);
	DDX_Text(pDX, IDC_EDIT8, d_icmpnum);
	DDX_Text(pDX, IDC_EDIT9, d_igmpnum);
}

BEGIN_MESSAGE_MAP(CDXQSnifferDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CDXQSnifferDlg::OnEnChangeEdit1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CDXQSnifferDlg::OnLvnItemchangedList1)
	ON_COMMAND(1, &CDXQSnifferDlg::On1)
	ON_COMMAND(2, &CDXQSnifferDlg::On2)
	ON_BN_CLICKED(IDC_BUTTON1, &CDXQSnifferDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDXQSnifferDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDXQSnifferDlg::OnBnClickedButton3)
	ON_COMMAND(ID_32774, &CDXQSnifferDlg::On32774)
END_MESSAGE_MAP()


// CDXQSnifferDlg 消息处理程序

BOOL CDXQSnifferDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
			//pSysMenu->EnableMenuItem(SC_CLOSE, MF_ENABLED);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	d_pDevice = NULL;
	d_pFlag = false;
	//list control控件初始化
	d_list1.SetExtendedStyle(d_list1.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	d_list1.InsertColumn(0, _T("序号"), LVCFMT_CENTER, 70);
	d_list1.InsertColumn(1, _T("时间"), LVCFMT_CENTER, 200);
	d_list1.InsertColumn(2, _T("源MAC地址"), LVCFMT_CENTER, 220);
	d_list1.InsertColumn(3, _T("目的MAC地址"), LVCFMT_CENTER, 220);
	d_list1.InsertColumn(4, _T("长度"), LVCFMT_CENTER, 70);
	d_list1.InsertColumn(5, _T("协议"), LVCFMT_CENTER, 70);
	d_list1.InsertColumn(6, _T("源IP地址"), LVCFMT_CENTER, 200);
	d_list1.InsertColumn(7, _T("目的IP地址"), LVCFMT_CENTER, 200);
	//数据包数目初始化
	d_tcpcount = 0;
	d_udpcount = 0;
	d_arpcount = 0;
	d_rarpcount = 0;
	d_ftpcount = 0;
	d_icmpcount = 0;
	d_igmpcount = 0;
	d_allcount = 0;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDXQSnifferDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
	
	if (nID == SC_CLOSE)//使得关闭按钮起作用
		CDialog::OnCancel();
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDXQSnifferDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

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
HCURSOR CDXQSnifferDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDXQSnifferDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDXQSnifferDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	POSITION pos = d_list1.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return;
	long index = d_list1.GetNextSelectedItem(pos);
	if (index < 0)
		return;
	ShowPacketTree(d_pktHeaders.GetAt(index), d_pktDatas.GetAt(index), index);
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDXQSnifferDlg::On1()//显示适配器对话框
{
	// TODO: 在此添加命令处理程序代码
	
	
	CShipeiDlg shipeidlg;
	if (shipeidlg.DoModal() == IDOK)//将选择的网卡返回到主界面的类实现中
	{
		d_pDevice = shipeidlg.Returnd();
		
	}
}

void CDXQSnifferDlg::On2()//显示过滤器对话框
{
	// TODO: 在此添加命令处理程序代码

	CGuolvDlg guolvdlg;
	if (guolvdlg.DoModal() == IDOK)//将过滤规则的字符串返回到主界面的类实现中
	{
		int len = WideCharToMultiByte(CP_ACP, 0, guolvdlg.GetGuoLvName(), -1, NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, guolvdlg.GetGuoLvName(), -1, d_guolvname, len, NULL, NULL);
	    //宽字符转化为多字符的函数
	}  
}

void CDXQSnifferDlg::OnBnClickedButton1()//退出程序
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);//直接退出程序
}

void CDXQSnifferDlg::OnBnClickedButton3()//停止捕获函数
{
	// TODO: 在此添加控件通知处理程序代码
	d_pFlag = false;
	CloseHandle(thread);//关闭多线程
}

DWORD WINAPI CapturePacket(LPVOID IpParam)//创建新线程，抓包函数
{
	CDXQSnifferDlg *pDlg = (CDXQSnifferDlg *)IpParam;
	pcap_t * pCap;
	char strErrorBuf[PCAP_ERRBUF_SIZE];
	int res;
	struct pcap_pkthdr *pkt_header;
	const u_char *pkt_data;
	u_int netmask;
	struct bpf_program fcode;

	if ((pCap = pcap_open_live(pDlg->d_pDevice->name, 65536, PCAP_OPENFLAG_PROMISCUOUS, 1000, strErrorBuf)) == NULL)
	{
		return -1;
	}
	if (pDlg->d_pDevice->addresses != NULL)
		// 获得接口第一个地址的掩码 
		netmask = ((struct sockaddr_in *)(pDlg->d_pDevice->addresses->netmask))->sin_addr.S_un.S_addr;
	else
		// 如果接口没有地址，那么我们假设一个C类的掩码 
		netmask = 0xffffff;
	//编译过滤器
	if (pcap_compile(pCap, &fcode, pDlg->d_guolvname, 1, netmask) < 0)
	{
		AfxMessageBox(_T("请在“过滤器”选项处设置过滤规则"));
		return -1;
	}
	//设置过滤器
	if (pcap_setfilter(pCap, &fcode) < 0)
		return -1;

	while ((res = pcap_next_ex(pCap, &pkt_header, &pkt_data)) >= 0)
	{

		if (res == 0)
			continue;
		if (!pDlg->d_pFlag)
			break;
		CDXQSnifferDlg *pDlg = (CDXQSnifferDlg *)AfxGetApp()->GetMainWnd();
		pDlg->ShowPacketList(pkt_header, pkt_data);
		pDlg = NULL;
	}

	pcap_close(pCap);
	pDlg = NULL;
	return 1;
}

void CDXQSnifferDlg::OnBnClickedButton2()//开始捕获函数
{
	// TODO: 在此添加控件通知处理程序代码
	if (d_pDevice == NULL)
	{
		AfxMessageBox(_T("未选择网卡！请在“适配器”选项处选择网卡！"));
		return;
	}
	d_pFlag = true;
	
	thread = CreateThread(NULL, NULL, CapturePacket, (LPVOID)this, true, NULL);
	thread;

}

void CDXQSnifferDlg::ShowPacketList(const pcap_pkthdr *pkt_header, const u_char *pkt_data)
{
	//用于存诸网络中的数据，并保存到CArray中,以备将来使用
	struct pcap_pkthdr *pHeader = new pcap_pkthdr;
	u_char *pData;
	unsigned char *pPosition = (unsigned char *)pkt_data;

	long nIndex = 0;//标识当前的数据包位置
	long nCount = 0;//标识后来

	pHeader->caplen = pkt_header->caplen;
	pHeader->len = pkt_header->len;

	pData = new unsigned char[pHeader->len];
	memcpy((void *)pData, pkt_data, pHeader->len);

	d_pktHeaders.Add(pHeader);
	d_pktDatas.Add(pData);

	nIndex = d_pktHeaders.GetSize() - 1;
	CString str;
	str.Format(_T("%d"), nIndex);
	nCount = d_list1.InsertItem(nIndex, str, 0);
	d_allcount++;//总数据包加1

	/*显示时间*/
	struct tm *ltime;
	time_t local_tv_sec;
	local_tv_sec = pkt_header->ts.tv_sec;
	ltime = localtime(&local_tv_sec);
	str.Format(_T("%d:%d:%d.%.6d"), ltime->tm_hour, ltime->tm_min, ltime->tm_sec, pkt_header->ts.tv_usec);
	d_list1.SetItemText(nCount, 1, str);
	/*处理链路层*/
	ethernet_header *eh;
	eh = (ethernet_header *)pkt_data;
	str.Format(_T("%x:%x:%x:%x:%x:%x"), eh->saddr.byte1, eh->saddr.byte2, eh->saddr.byte3, eh->saddr.byte4, eh->saddr.byte5, eh->saddr.byte6);
	d_list1.SetItemText(nCount, 2, str);
	str.Format(_T("%x:%x:%x:%x:%x:%x"), eh->daddr.byte1, eh->daddr.byte2, eh->daddr.byte3, eh->daddr.byte4, eh->daddr.byte5, eh->daddr.byte6);
	d_list1.SetItemText(nCount, 3, str);
	str.Format(_T("%ld"), pHeader->len);
	d_list1.SetItemText(nCount, 4, str);
	/*处理网络层*/
	switch (ntohs(eh->type))
	{
	case IP:
	{
		ip_header *ih;
		const u_char *ip_data;
		ip_data = pkt_data + 14;
		ih = (ip_header *)ip_data;
		u_int ip_len;//IP首部长度
		ip_len = (ih->ver_ihl & 0xf) * 4;
		str.Format(_T("%d.%d.%d.%d"), ih->saddr.byte1, ih->saddr.byte2, ih->saddr.byte3, ih->saddr.byte4);
		d_list1.SetItemText(nCount, 6, str);
		str.Format(_T("%d.%d.%d.%d"), ih->saddr.byte1, ih->saddr.byte2, ih->saddr.byte3, ih->saddr.byte4);
		d_list1.SetItemText(nCount, 7, str);
		/*处理传输层*/
		switch (ih->type)
		{
		case TCP:
		{
			d_tcpcount++;
			tcp_header *th;
			const u_char *tcp_data;
			tcp_data = ip_data + ip_len;
			th = (tcp_header *)tcp_data;
			if (ntohs(th->sport) == HTTP)
			{
				d_list1.SetItemText(nCount, 5, _T("源HTTP"));
				d_ftpcount++;
			}
			else if (ntohs(th->dport) == HTTP)
			{
				d_list1.SetItemText(nCount, 5, _T("目的HTTP"));
				d_ftpcount++;
			}
			else if (ntohs(th->dport) == DNS || ntohs(th->sport) == DNS)
			{
				d_list1.SetItemText(nCount, 5, _T("DNS"));
				d_rarpcount++;
			}
			else
				d_list1.SetItemText(nCount, 5, _T("TCP"));
			
			break;
		}
		case UDP:
		{
			d_udpcount++;
			udp_header *uh;
			const u_char *udp_data;
			udp_data = ip_data + ip_len;
			uh = (udp_header *)udp_data;
			if (ntohs(uh->dport) == DNS || ntohs(uh->sport) == DNS)
			{
				d_list1.SetItemText(nCount, 5, _T("DNS"));
				d_rarpcount++;
			}
			else
				d_list1.SetItemText(nCount, 5, _T("UDP"));
			
			break;
		}
		case ICMP:d_icmpcount++; d_list1.SetItemText(nCount, 5, _T("ICMP")); break;
		case IGMP:d_igmpcount++; d_list1.SetItemText(nCount, 5, _T("IGMP")); break;
		case EGP:d_list1.SetItemText(nCount, 5, _T("EGP")); break;
		case IPv6:d_list1.SetItemText(nCount, 5, _T("IPv6")); break;
		case OSPF:d_list1.SetItemText(nCount, 5, _T("OSPF")); break;
		default:d_list1.SetItemText(nCount, 5, _T("未知"));
		}
		break;
	}
	case ARP:
	{
		d_arpcount++;
		arp_header *ah;
		const u_char *arp_data;
		arp_data = pkt_data + 14;
		ah = (arp_header *)arp_data;
		str.Format(_T("%d.%d.%d.%d"), ah->arp_sip.byte1, ah->arp_sip.byte2, ah->arp_sip.byte3, ah->arp_sip.byte4);
		d_list1.SetItemText(nCount, 6, str);
		str.Format(_T("%d.%d.%d.%d"), ah->arp_dip.byte1, ah->arp_dip.byte2, ah->arp_dip.byte3, ah->arp_dip.byte4);
		d_list1.SetItemText(nCount, 7, str);
		d_list1.SetItemText(nCount, 5, _T("ARP"));
		break;
	}
	case RARP:
		d_list1.SetItemText(nCount, 5, _T("RARP"));
		break;
	default:
		d_list1.SetItemText(nCount, 5, _T("未知协议"));
	}
	
	ShowPckNum();
}

void CDXQSnifferDlg::ShowPacketTree(const pcap_pkthdr *pkt_header, const u_char *pkt_data, long index)
{
	d_tree1.DeleteAllItems();
	CString str;
	str.Format(_T("数据包:%ld"), index);
	HTREEITEM hRoot;
	HTREEITEM hSubItem;
	HTREEITEM hItem;
	HTREEITEM hItem2;

	hRoot = d_tree1.InsertItem(str);
	hSubItem = d_tree1.InsertItem(_T("数据链路层"), hRoot);
	ethernet_header *eh;
	eh = (ethernet_header *)pkt_data;
	str.Format(_T("源MAC:%x:%x:%x:%x:%x:%x"), eh->saddr.byte1, eh->saddr.byte2, eh->saddr.byte3, eh->saddr.byte4, eh->saddr.byte5, eh->saddr.byte6);
	hItem = d_tree1.InsertItem(str, hSubItem);
	str.Format(_T("目的MAC:%x:%x:%x:%x:%x:%x"), eh->daddr.byte1, eh->daddr.byte2, eh->daddr.byte3, eh->daddr.byte4, eh->daddr.byte5, eh->daddr.byte6);
	hItem = d_tree1.InsertItem(str, hSubItem);
	switch (ntohs(eh->type))
	{
	case IP:
	{
		hItem = d_tree1.InsertItem(_T("上层协议:IP"), hSubItem);
		hSubItem = d_tree1.InsertItem(_T("网络层"), hRoot);
		ip_header *ih;
		const u_char *ip_data;
		ip_data = pkt_data + 14;
		ih = (ip_header *)ip_data;
		str.Format(_T("版本：%d"), (ih->ver_ihl & 0xf0) / 0x10);
		hItem = d_tree1.InsertItem(str, hSubItem);
		u_int ip_len;//IP首部长度
		ip_len = (ih->ver_ihl & 0xf) * 4;
		str.Format(_T("首部长度：%d"), ip_len);
		hItem = d_tree1.InsertItem(str, hSubItem);
		str.Format(_T("服务类型：0x%x"), ih->tos);
		hItem = d_tree1.InsertItem(str, hSubItem);
		str.Format(_T("总长度：%d"), ntohs(ih->tlen));
		hItem = d_tree1.InsertItem(str, hSubItem);
		str.Format(_T("标识：0x%x"), ntohs(ih->identification));
		hItem = d_tree1.InsertItem(str, hSubItem);
		str.Format(_T("标志：0x%x"), ntohs(ih->flags_fo) & 0xe000 / 0x2000);
		hItem = d_tree1.InsertItem(str, hSubItem);
		str.Format(_T("片偏移：%d"), ntohs(ih->flags_fo) & 0x1fff);
		hItem = d_tree1.InsertItem(str, hSubItem);
		str.Format(_T("生存时间：%d"), ih->ttl);
		hItem = d_tree1.InsertItem(str, hSubItem);
		str.Format(_T("首部校验和：0x%x"), ntohs(ih->crc));
		hItem = d_tree1.InsertItem(str, hSubItem);
		str.Format(_T("源IP地址：%d.%d.%d.%d"), ih->saddr.byte1, ih->saddr.byte2, ih->saddr.byte3, ih->saddr.byte4);
		hItem = d_tree1.InsertItem(str, hSubItem);
		str.Format(_T("目的IP地址：%d.%d.%d.%d"), ih->saddr.byte1, ih->saddr.byte2, ih->saddr.byte3, ih->saddr.byte4);
		hItem = d_tree1.InsertItem(str, hSubItem);
		switch (ih->type)
		{
		case TCP:
		{
			hItem = d_tree1.InsertItem(_T("上层协议:TCP"), hSubItem);
			hSubItem = d_tree1.InsertItem(_T("传输层"), hRoot);
			tcp_header *th;
			const u_char *tcp_data;
			tcp_data = ip_data + ip_len;
			th = (tcp_header *)tcp_data;
			str.Format(_T("源端口号：%d"), ntohs(th->sport));
			hItem = d_tree1.InsertItem(str, hSubItem);
			str.Format(_T("目的口号：%d"), ntohs(th->dport));
			hItem = d_tree1.InsertItem(str, hSubItem);
			str.Format(_T("顺序号：%d"), ntohs(th->seq));
			hItem = d_tree1.InsertItem(str, hSubItem);
			str.Format(_T("确认号：%d"), ntohs(th->ack));
			hItem = d_tree1.InsertItem(str, hSubItem);
			str.Format(_T("TCP头长：%d"), (th->len & 0xf0) / 0x10 * 4);
			hItem = d_tree1.InsertItem(str, hSubItem);
			hItem = d_tree1.InsertItem(_T("控制位"), hSubItem);
			str.Format(_T("紧急URG:%d"), (th->flags & 0x20) / 0x20);
			hItem2 = d_tree1.InsertItem(str, hItem);
			str.Format(_T("确认ACK:%d"), (th->flags & 0x10) / 0x10);
			hItem2 = d_tree1.InsertItem(str, hItem);
			str.Format(_T("推送PSH:%d"), (th->flags & 0x08) / 0x08);
			hItem2 = d_tree1.InsertItem(str, hItem);
			str.Format(_T("复位RSTG:%d"), (th->flags & 0x04) / 0x04);
			hItem2 = d_tree1.InsertItem(str, hItem);
			str.Format(_T("同步SYN:%d"), (th->flags & 0x02) / 0x02);
			hItem2 = d_tree1.InsertItem(str, hItem);
			str.Format(_T("结束FIN:%d"), (th->flags & 0x01) / 0x01);
			hItem2 = d_tree1.InsertItem(str, hItem);
			str.Format(_T("窗口：%d"), ntohs(th->win));
			hItem = d_tree1.InsertItem(str, hSubItem);
			str.Format(_T("校验和：0x%x"), ntohs(th->crc));
			hItem = d_tree1.InsertItem(str, hSubItem);
			str.Format(_T("紧急指针：0x%x"), ntohs(th->urp));
			hItem = d_tree1.InsertItem(str, hSubItem);
			break;
		}
		case UDP:
		{
			hItem = d_tree1.InsertItem(_T("上层协议:UDP"), hSubItem);
			hSubItem = d_tree1.InsertItem(_T("传输层"), hRoot);
			udp_header *uh;
			const u_char *udp_data;
			udp_data = ip_data + ip_len;
			uh = (udp_header *)udp_data;
			str.Format(_T("源端口号：%d"), ntohs(uh->sport));
			hItem = d_tree1.InsertItem(str, hSubItem);
			str.Format(_T("目的口号：%d"), ntohs(uh->dport));
			hItem = d_tree1.InsertItem(str, hSubItem);
			str.Format(_T("长度：%d"), ntohs(uh->len));
			hItem = d_tree1.InsertItem(str, hSubItem);
			str.Format(_T("校验和：0x%x"), ntohs(uh->crc));
			hItem = d_tree1.InsertItem(str, hSubItem);
			if (ntohs(uh->dport) == DNS || ntohs(uh->sport) == DNS)
			{
				hSubItem = d_tree1.InsertItem(_T("应用层"), hRoot);
				dns_header *dh;
				const u_char *dns_data;
				dns_data = udp_data + 8;
				dh = (dns_header *)dns_data;
				str.Format(_T("标识：0x%x"), ntohs(dh->identification));
				hItem = d_tree1.InsertItem(str, hSubItem);
				str.Format(_T("标志：0x%x"), ntohs(dh->flags));
				hItem = d_tree1.InsertItem(str, hSubItem);
				str.Format(_T("问题数：%d"), ntohs(dh->questions_num));
				hItem = d_tree1.InsertItem(str, hSubItem);
				str.Format(_T("资源记录数：%d"), ntohs(dh->answers_num));
				hItem = d_tree1.InsertItem(str, hSubItem);
				str.Format(_T("授权资源记录数：%d"), ntohs(dh->authority_num));
				hItem = d_tree1.InsertItem(str, hSubItem);
				str.Format(_T("额外资源记录数：%d"), ntohs(dh->addition_num));
				hItem = d_tree1.InsertItem(str, hSubItem);
			}
			break;
		}
		case ICMP:
		{
			hItem = d_tree1.InsertItem(_T("上层协议:ICMP"), hSubItem);
			hSubItem = d_tree1.InsertItem(_T("传输层"), hRoot);
			icmp_header *icmph;
			const u_char *icmp_data;
			icmp_data = ip_data + ip_len;
			icmph = (icmp_header *)icmp_data;
			str.Format(_T("类型：%d"), icmph->type);
			hItem = d_tree1.InsertItem(str, hSubItem);
			str.Format(_T("代码：%d"), icmph->code);
			hItem = d_tree1.InsertItem(str, hSubItem);
			str.Format(_T("校验和：0x%x"), ntohs(icmph->checksum));
			hItem = d_tree1.InsertItem(str, hSubItem);
			break;
		}
		case IGMP:hItem = d_tree1.InsertItem(_T("上层协议:IGMP"), hSubItem); break;
		case EGP:hItem = d_tree1.InsertItem(_T("上层协议:EGP"), hSubItem); break;
		case IPv6:hItem = d_tree1.InsertItem(_T("上层协议:IPv6"), hSubItem); break;
		case OSPF:hItem = d_tree1.InsertItem(_T("上层协议:OSPF"), hSubItem); break;
		default:hItem = d_tree1.InsertItem(_T("上层协议:未知"), hSubItem);
		}
		break;
	}
	case ARP:
	{
		hItem = d_tree1.InsertItem(_T("上层协议:ARP"), hSubItem);
		hSubItem = d_tree1.InsertItem(_T("网络层"), hRoot);
		arp_header *ah;
		const u_char *arp_data;
		arp_data = pkt_data + 14;
		ah = (arp_header *)arp_data;
		str.Format(_T("硬件类型：%d"), ntohs(ah->arp_hdr));
		hItem = d_tree1.InsertItem(str, hSubItem);
		str.Format(_T("协议类型：0x%x"), ntohs(ah->arp_pro));
		hItem = d_tree1.InsertItem(str, hSubItem);
		str.Format(_T("硬件长度：%d"), ah->arp_hln);
		hItem = d_tree1.InsertItem(str, hSubItem);
		str.Format(_T("协议长度：%d"), ah->apr_pln);
		hItem = d_tree1.InsertItem(str, hSubItem);
		str.Format(_T("操作类型：%d"), ntohs(ah->arp_opt));
		hItem = d_tree1.InsertItem(str, hSubItem);
		str.Format(_T("发送端MAC地址：%x:%x:%x:%x:%x:%x"), ah->arp_smac.byte1, ah->arp_smac.byte2, ah->arp_smac.byte3, ah->arp_smac.byte4, ah->arp_smac.byte5, ah->arp_smac.byte6);
		hItem = d_tree1.InsertItem(str, hSubItem);
		str.Format(_T("发送端协议地址：%d.%d.%d.%d"), ah->arp_sip.byte1, ah->arp_sip.byte2, ah->arp_sip.byte3, ah->arp_sip.byte4);
		hItem = d_tree1.InsertItem(str, hSubItem);
		str.Format(_T("接收端MAC地址：%x:%x:%x:%x:%x:%x"), ah->arp_dmac.byte1, ah->arp_dmac.byte2, ah->arp_dmac.byte3, ah->arp_dmac.byte4, ah->arp_dmac.byte5, ah->arp_dmac.byte6);
		hItem = d_tree1.InsertItem(str, hSubItem);
		str.Format(_T("接收端协议地址：%d.%d.%d.%d"), ah->arp_dip.byte1, ah->arp_dip.byte2, ah->arp_dip.byte3, ah->arp_dip.byte4);
		hItem = d_tree1.InsertItem(str, hSubItem);
		break;
	}
	case RARP:
	{
		hItem = d_tree1.InsertItem(_T("上层协议:RARP"), hSubItem);
		break;
	}
	default:
		hItem = d_tree1.InsertItem(_T("上层协议:未知"), hSubItem);
	}

	d_tree1.Expand(hRoot, TVE_EXPAND);		//默认展开目录
	d_tree1.Expand(hSubItem, TVE_EXPAND);

	CString strHex;
	int nCount = 0;
	CString strText;
	for (unsigned short i = 0; i < pkt_header->caplen; i++)
	{
		CString hex;
		if ((i % 16) == 0)
		{
			hex.Format(_T("\x0d\x0a 0X%04x   "), nCount);
			nCount++;
			if (i != 0)
			{
				strHex += _T("  ") + strText;
				strText = _T("");
			}
			strHex += hex;
		}
		hex.Format(_T("%2.2x "), pkt_data[i - 1]);
		strHex += hex;
		if (pkt_data[i - 1] <= 127 && pkt_data[i - 1] >= 0)
			hex.Format(_T("%c"), pkt_data[i - 1]);
		else
			hex = _T(".");
		strText += hex;
	}
	if (strText != _T(""))
		strHex += strText;
	d_edit1.SetWindowText(strHex);
}

void CDXQSnifferDlg::ShowPckNum()//统计数据包数目
{
	d_tcpnum.Format(_T("%ld"), d_tcpcount);
	this->SetDlgItemText(IDC_EDIT4, d_tcpnum);
	d_udpnum.Format(_T("%ld"), d_udpcount);
	this->SetDlgItemText(IDC_EDIT6, d_udpnum);
	d_arpnum.Format(_T("%ld"), d_arpcount);
	this->SetDlgItemText(IDC_EDIT10, d_arpnum);
	d_icmpnum.Format(_T("%ld"), d_icmpcount);
	this->SetDlgItemText(IDC_EDIT8, d_icmpnum);
	d_igmpnum.Format(_T("%ld"), d_igmpcount);
	this->SetDlgItemText(IDC_EDIT9, d_igmpnum);
	d_allnum.Format(_T("%ld"), d_allcount);
	this->SetDlgItemText(IDC_EDIT5, d_allnum);
	d_ftpnum.Format(_T("%ld"), d_ftpcount);
	this->SetDlgItemText(IDC_EDIT7, d_ftpnum);
	d_rarpnum.Format(_T("%ld"), d_rarpcount);
	this->SetDlgItemText(IDC_EDIT11, d_rarpnum);

}




//帮助-关于对话框
void CDXQSnifferDlg::On32774()
{
	// TODO: 在此添加命令处理程序代码
	CGuanyuDlg guanyu;
	guanyu.DoModal();
}
