
// HanoiDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Hanoi.h"
#include "HanoiDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
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


// CHanoiDlg �Ի���




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


// CHanoiDlg ��Ϣ�������

BOOL CHanoiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHanoiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

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
		static int created=0;
		static int left=25,top=50,width=550,height=350;
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������
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
		//����
		brush=new CBrush(RGB(0,0,0));
		rect.SetRect(left+10,height-5-50,left+width-10,height+5-50);
		memDC.FillRect(rect,brush);

		
		//��������
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
			plate->paint(memDC);//�˶�������
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHanoiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHanoiDlg::OnBnClickedPlay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!UpdateData(TRUE))
		return;
	stakes->clear();
	SetTimer(10,50,NULL);
	this->GetDlgItem(IDC_PLAY)->EnableWindow(FALSE);
}

void CHanoiDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nIDEvent==10)
	{
		if(!ready)//����׼������
		{
			static int id=plateNum;
			if(id==-1)//�ؽ���
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
		else//�����˶����ӵ�λ��
		{
			if(plate!=NULL)
			{
				if(plate->x==pos[0].x)//��ʼ
				{
					if(plate->y==43)//һ��ת��
					{
						if(pos[0].x<pos[1].x)
							plate->x+=25;
						else
							plate->x-=25;
					}
					plate->y-=20;
				}
				else if(plate->x==pos[1].x)//����ת��
				{
					if(plate->y==pos[1].y)//����
					{
						stakes->endMove(plate);
						plate=NULL;
						pos[0].x=0;
						pos[0].y=0;
						pos[1].x=0;
						pos[1].y=0;
					}
					else//����
						plate->y+=20;
				}
				else//�м��
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

void CHanoiDlg::_hanoi(int n,int a,int b,int c)//����=2^n-1
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
	}//�ȴ������ƶ���ϣ�����hanoi�㷨
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return true;// CDialogEx::OnEraseBkgnd(&memDC);
}


void CHanoiDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	memBitmap.DeleteObject();
	memDC.DeleteDC();
	if(plate!=NULL)//����������һ����NULL
		delete plate;
	delete stakes;
	delete[]pos;
}
