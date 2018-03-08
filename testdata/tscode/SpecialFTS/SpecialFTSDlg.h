/* 
 * MPEG2-TS��ʽ������
 * MPEG2-TS Format Analysis
 *
 * ������ Lei Xiaohua
 * leixiaohua1020@126.com
 * �й���ý��ѧ/���ֵ��Ӽ���
 * Communication University of China / Digital TV Technology
 * http://blog.csdn.net/leixiaohua1020
 *
 */

#pragma once

#include "resource.h"
#include "stdafx.h"
#include "tsdemux.h"
#include "afxwin.h"
 // CSpecialFTSDlg �Ի���
class CSpecialFTSDlg : public CDialogEx
{
// ����
public:
	CSpecialFTSDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SPECIAL_F_TS };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


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
	afx_msg void OnBnClickedFTsInputurlOpen();
	void SystemClear();
	char fileurl[MAX_URL_LENGTH];
	CMFCEditBrowseCtrl m_ftsinputurl;
	CListCtrl m_ftspacketlist;
	//���һ��TS����¼(PID,���ͣ���Ƶ����Ƶ or PSI����PSI����)
	//ListCtrl����
	int tsl_index;
	int AppendTSLInfo(int pid,int type,int psi_type);
	CButton m_ftspacketlistmaxnum;
	void OnCustomdrawMyList ( NMHDR* pNMHDR, LRESULT* pResult );
	//PropertyList------------------
	CMFCPropertyGridProperty *PATgroup;
	CMFCPropertyGridProperty *PMTgroup;
	CMFCPropertyGridCtrl m_ftsbasicinfo;
	int AppendBInfo(char *dst_group,char *property_name,char *value,char *remark);
	int ShowBInfo();


	afx_msg void OnBnClickedFTsAbout();

	
	afx_msg void OnDropFiles(HDROP hDropInfo);
	
	//ר�����ڼ����ַ���
	CString text;
	CComboBox m_ftsdumpmode;

	afx_msg void OnBnClickedFTsOutput();
//	int m_ftsoutput;
	int m_ftsoutput;
	afx_msg void OnBnClickedFTsOutput2();
	CComboBox m_ftslang;
	afx_msg void OnSelchangeFTsLang();
};
