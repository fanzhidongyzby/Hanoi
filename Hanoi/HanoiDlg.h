
// HanoiDlg.h : 头文件
//

#pragma once

#include "Stakes.h"
#include "Plate.h"

// CHanoiDlg 对话框
class CHanoiDlg : public CDialogEx
{
// 构造
public:
	CHanoiDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HANOI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	static CHanoiDlg*self;
	static Stakes * stakes;//所有柱子
	static Plate * plate;//当前运动的盘子
	bool ready;//是否把盘子全部准备好
	static CPoint*pos;//记录移动盘子的开始和结束位置
	//双缓冲
	CDC memDC;
	CBitmap memBitmap;

	//线程
	static UINT hanoi (LPVOID pParam) ;
	static void _hanoi(int n,int a,int b,int c);
	static int paraNum;
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
	UINT plateNum;
	
	afx_msg void OnBnClickedPlay();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
};
