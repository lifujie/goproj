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

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSpecialFTSApp:
// �йش����ʵ�֣������ SpecialFTS.cpp
//

class CSpecialFTSApp : public CWinApp
{
public:
	CSpecialFTSApp();

// ��д
public:
	virtual BOOL InitInstance();
	//������������
	void LoadLaguage();
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSpecialFTSApp theApp;