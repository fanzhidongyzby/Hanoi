
// HanoiDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Hanoi.h"
#include "HanoiDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHanoiDlg 对话框




Stakes * CHanoiDlg::stakes=NULL;
Plate * CHanoiDlg::plate=NULL;
CPoint * CHanoiDlg::pos=NULL;
int CHanoiDlg::paraNum=0;
CHanoiDlg::CHanoiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHanoiDlg::IDD, pParent)
	, plateNum(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	CHanoiDlg::self=this;
	this->plateNum=3;
	this->ready=false;
	stakes=new Stakes();
	pos=new CPoint[2];
}

void CHanoiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NUM, plateNum);
	DDV_MinMaxUInt(pDX, plateNum, 1, 10);
}

BEGIN_MESSAGE_MAP(CHanoiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PLAY, &CHanoiDlg::OnBnClickedPlay)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CHanoiDlg 消息处理程序

BOOL CHanoiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHanoiDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHanoiDlg::OnPaint()
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
		static int created=0;
		static int left=25,top=50,width=550,height=350;
		CPaintDC dc(this); // 用于绘制的设备上下文
		if(created==0)
		{
			memDC.CreateCompatibleDC(&dc);
			memBitmap.CreateCompatibleBitmap(&dc,width,height);
			memDC.SelectObject(&memBitmap);
			created++;
		}		
		//memDC.FillSolidRect(0,0,width,height,RGB(0,0,0));
		CBrush *brush=new CBrush(RGB(110,100,200));
		CRect rect;
		rect.SetRect(0,0,width,height);
		memDC.Rectangle(0,0,width,height);
		memDC.FillRect(rect,brush);
		delete brush;
		left=top=0;
		//底座
		brush=new CBrush(RGB(0,0,0));
		rect.SetRect(left+10,height-5-50,left+width-10,height+5-50);
		memDC.FillRect(rect,brush);

		
		//三个柱子
		rect.SetRect(left+100-2,height-307,left+100+2,height-50);
		memDC.FillRect(rect,brush);
		rect.SetRect(left+275-2,height-307,left+275+2,height-50);
		memDC.FillRect(rect,brush);
		rect.SetRect(left+450-2,height-307,left+450+2,height-50);
		memDC.FillRect(rect,brush);

		::SetBkMode(memDC,TRANSPARENT);
		::SetTextColor(memDC,RGB(0,0,0));
		rect.SetRect(80,310,120,340);
		memDC.DrawText("A",rect,DT_CENTER);
		rect.SetRect(255,310,295,340);
		memDC.DrawText("B",rect,DT_CENTER);
		rect.SetRect(430,310,470,340);
		memDC.DrawText("C",rect,DT_CENTER);
		delete brush;

		brush=new CBrush(RGB(200,110,200));
		CBrush*oldBrush=memDC.SelectObject(brush);
		CPen*pen=new CPen(PS_SOLID,1,RGB(200,110,200));
		CPen*oldPen=memDC.SelectObject(pen);
		
		::SetBkMode(memDC,TRANSPARENT);
		::SetTextColor(memDC,RGB(230,230,65));
		
		stakes->paint(memDC);
		if(plate!=NULL)
		{
			plate->paint(memDC);//运动的盘子
			CPen*oldPen;
			pen=new CPen(PS_SOLID,1,RGB(0,0,0));
			oldPen=memDC.SelectObject(pen);
			memDC.MoveTo(pos[0]);
			memDC.LineTo(pos[1]);
			memDC.Ellipse(pos[1].x-5,pos[1].y-5,pos[1].x+5,pos[1].y+5);
			memDC.SelectObject(oldPen);
		}
		memDC.SelectObject(oldPen);
		memDC.SelectObject(oldBrush);
		delete brush;
		delete pen;
		dc.BitBlt(20,20,width,height,&memDC,0,0,SRCCOPY);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHanoiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHanoiDlg::OnBnClickedPlay()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!UpdateData(TRUE))
		return;
	stakes->clear();
	SetTimer(10,50,NULL);
	this->GetDlgItem(IDC_PLAY)->EnableWindow(FALSE);
}

void CHanoiDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent==10)
	{
		if(!ready)//正在准备盘子
		{
			static int id=plateNum;
			if(id==-1)//重进入
			{
				id=plateNum;
			}
			if(id>0)
			{
				stakes->genOnePlate(id,plateNum);
				id--;
			}
			if(stakes->dropDown()==0)
			{
				id=-1;
				ready=true;
				CHanoiDlg::paraNum=plateNum;
				CWinThread*thread=AfxBeginThread(hanoi,NULL,0,0,0);
				SetTimer(10,30,NULL);
				thread->ResumeThread();
			}
		}
		else//修正运动盘子的位置
		{
			if(plate!=NULL)
			{
				if(plate->x==pos[0].x)//开始
				{
					if(plate->y==43)//一次转折
					{
						if(pos[0].x<pos[1].x)
							plate->x+=25;
						else
							plate->x-=25;
					}
					plate->y-=20;
				}
				else if(plate->x==pos[1].x)//二次转折
				{
					if(plate->y==pos[1].y)//结束
					{
						stakes->endMove(plate);
						plate=NULL;
						pos[0].x=0;
						pos[0].y=0;
						pos[1].x=0;
						pos[1].y=0;
					}
					else//最后段
						plate->y+=20;
				}
				else//中间段
				{
					if(pos[0].x<pos[1].x)
						plate->x+=25;
					else
						plate->x-=25;
				}
			}
		}
		//Invalidate();
		CRect r;
		r.SetRect(20,20,550,350);
		InvalidateRect(r);
	}
	
	CDialogEx::OnTimer(nIDEvent);
}

void CHanoiDlg::_hanoi(int n,int a,int b,int c)//次数=2^n-1
{
	if(n<=0)
		return;
	_hanoi(n-1,a,c,b);
	plate=stakes->beginMove(a,b,pos);
	while(true)
	{
		if(plate==NULL)
			break;
		Sleep(100);
	}//等待盘子移动完毕，继续hanoi算法
	_hanoi(n-1,c,b,a);
}
UINT CHanoiDlg::hanoi(LPVOID param)
{
	_hanoi(CHanoiDlg::paraNum,0,1,2);
	self->GetDlgItem(IDC_PLAY)->EnableWindow(TRUE);
	self->KillTimer(10);
	self->ready=false;
	return 0;
}
CHanoiDlg * CHanoiDlg::self=NULL;
BOOL CHanoiDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return true;// CDialogEx::OnEraseBkgnd(&memDC);
}


void CHanoiDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	memBitmap.DeleteObject();
	memDC.DeleteDC();
	if(plate!=NULL)//正常结束后一定是NULL
		delete plate;
	delete stakes;
	delete[]pos;
}
