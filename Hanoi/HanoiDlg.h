
// HanoiDlg.h : ͷ�ļ�
//

#pragma once

#include "Stakes.h"
#include "Plate.h"

// CHanoiDlg �Ի���
class CHanoiDlg : public CDialogEx
{
// ����
public:
	CHanoiDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HANOI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	static CHanoiDlg*self;
	static Stakes * stakes;//��������
	static Plate * plate;//��ǰ�˶�������
	bool ready;//�Ƿ������ȫ��׼����
	static CPoint*pos;//��¼�ƶ����ӵĿ�ʼ�ͽ���λ��
	//˫����
	CDC memDC;
	CBitmap memBitmap;

	//�߳�
	static UINT hanoi (LPVOID pParam) ;
	static void _hanoi(int n,int a,int b,int c);
	static int paraNum;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
