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
#include "stdafx.h"
#include "SpecialFTS.h"
#include "SpecialFTSDlg.h"
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


// CSpecialFTSDlg �Ի���




CSpecialFTSDlg::CSpecialFTSDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSpecialFTSDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ftsoutput = 0;
}

void CSpecialFTSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_F_TS_INPUTURL, m_ftsinputurl);
	DDX_Control(pDX, IDC_F_TS_PACKETLIST, m_ftspacketlist);
	DDX_Control(pDX, IDC_F_TS_PACKETLIST_MAXNUM, m_ftspacketlistmaxnum);
	DDX_Control(pDX, IDC_F_TS_BASICINFO, m_ftsbasicinfo);
	DDX_Control(pDX, IDC_F_TS_DUMP_MODE, m_ftsdumpmode);
	DDX_Radio(pDX, IDC_F_TS_OUTPUT, m_ftsoutput);
	DDX_Control(pDX, IDC_F_TS_LANG, m_ftslang);
}

BEGIN_MESSAGE_MAP(CSpecialFTSDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_F_TS_INPUTURL_OPEN, &CSpecialFTSDlg::OnBnClickedFTsInputurlOpen)
	ON_NOTIFY ( NM_CUSTOMDRAW,IDC_F_TS_PACKETLIST, OnCustomdrawMyList )
	ON_BN_CLICKED(IDC_F_TS_ABOUT, &CSpecialFTSDlg::OnBnClickedFTsAbout)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_F_TS_OUTPUT, &CSpecialFTSDlg::OnBnClickedFTsOutput)
	ON_BN_CLICKED(IDC_F_TS_OUTPUT2, &CSpecialFTSDlg::OnBnClickedFTsOutput2)
	ON_CBN_SELCHANGE(IDC_F_TS_LANG, &CSpecialFTSDlg::OnSelchangeFTsLang)
END_MESSAGE_MAP()


// CSpecialFTSDlg ��Ϣ�������

BOOL CSpecialFTSDlg::OnInitDialog()
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
	//����ѡ���б���ߣ���ͷ����������
	DWORD dwExStyle=LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP|LVS_EX_ONECLICKACTIVATE;
	//�����񣻵���ѡ�񣻸�����ʾѡ����
	//��Ƶ
	m_ftspacketlist.ModifyStyle(0,LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS);
	m_ftspacketlist.SetExtendedStyle(dwExStyle);

	text.LoadString(IDS_TSPKT_NUM);
	m_ftspacketlist.InsertColumn(0,text,LVCFMT_CENTER,50,0);
	text.LoadString(IDS_TSPKT_PID);
	m_ftspacketlist.InsertColumn(1,text,LVCFMT_CENTER,122,0);
	text.LoadString(IDS_TSPKT_TYPE);
	m_ftspacketlist.InsertColumn(2,text,LVCFMT_CENTER,122,0);
	text.LoadString(IDS_TSPKT_PSITYPE);
	m_ftspacketlist.InsertColumn(3,text,LVCFMT_CENTER,122,0);

	//Propertylist��ʼ��------------------------
	m_ftsbasicinfo.EnableHeaderCtrl(FALSE);
	m_ftsbasicinfo.EnableDescriptionArea();
	m_ftsbasicinfo.SetVSDotNetLook();
	m_ftsbasicinfo.MarkModifiedProperties();
	//�ѵ�һ�е�����һЩ-----------------------
	HDITEM item; 
	item.cxy=120; 
	item.mask=HDI_WIDTH; 
	m_ftsbasicinfo.GetHeaderCtrl().SetItem(0, &item); 
	//----
	text.LoadString(IDS_TS_PAT);
	PATgroup=new CMFCPropertyGridProperty(text);
	text.LoadString(IDS_TS_PMT);
	PMTgroup=new CMFCPropertyGridProperty(text);
	//--------------------
	tsl_index=0;
	m_ftspacketlistmaxnum.SetCheck(1);
	m_ftsoutput=1;
	UpdateData(FALSE);
	m_ftsinputurl.EnableFileBrowseButton(
		NULL,
		_T("MPEG2 Transport Stream Files (*.ts,*.m2ts,*.mts)|*.ts;*.m2ts;*.mts|All Files (*.*)|*.*||")
		);
	//------------
	m_ftsdumpmode.InsertString(0,_T("M2TS timecodes"));
	m_ftsdumpmode.InsertString(1,_T("PTS/DTS"));
	m_ftsdumpmode.InsertString(2,_T("readable PTS/DTS"));
	m_ftsdumpmode.SetCurSel(0);
	m_ftsdumpmode.EnableWindow(FALSE);

	m_ftslang.InsertString(0,_T("Chinese"));
	m_ftslang.InsertString(1,_T("English"));
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSpecialFTSDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSpecialFTSDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
	//���Ի���Ӧ����ӵ�OnInitDialog�У�����û��Ч��
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSpecialFTSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSpecialFTSDlg::OnBnClickedFTsInputurlOpen()
{
	SystemClear();
	CString strFilePath;
	m_ftsinputurl.GetWindowText(strFilePath);
	if(strFilePath.IsEmpty()==TRUE){
		text.LoadString(IDS_INPUTURL_ERROR);
		AfxMessageBox(text);
		return;
	}

	
#ifdef _UNICODE
	USES_CONVERSION;
	strcpy(fileurl,W2A(strFilePath));
#else
	strcpy(fileurl,strFilePath);
#endif
	
	int argc=5;
	char **argv=(char **)malloc(MAX_URL_LENGTH);
	argv[0]=(char *)malloc(MAX_URL_LENGTH);
	argv[1]=(char *)malloc(MAX_URL_LENGTH);
	argv[2]=(char *)malloc(MAX_URL_LENGTH);
	argv[3]=(char *)malloc(MAX_URL_LENGTH);
	argv[4]=(char *)malloc(MAX_URL_LENGTH);
	strcpy(argv[0],"dummy");
	strcpy(argv[1],fileurl);
	UpdateData(TRUE);

	if(m_ftsoutput==1){
		strcpy(argv[2],"");
	}else{
		strcpy(argv[2],"-p");
	}

	if(m_ftsoutput==0){
		strcpy(argv[3],"-e");
		switch(m_ftsdumpmode.GetCurSel()){
		case 0:strcpy(argv[4],"1");break;
		case 1:strcpy(argv[4],"2");break;
		case 2:strcpy(argv[4],"3");break;
		default:strcpy(argv[4],"1");break;
		}
		
	}else{
		strcpy(argv[3],"");
		strcpy(argv[4],"");
	}
	tsdemux(this,argc,argv);
	free(argv[0]);
	free(argv[1]);
	free(argv[2]);
	free(argv[3]);
	free(argv[4]);
	free(argv);
	ShowBInfo();
}

void CSpecialFTSDlg::SystemClear(){
	PMTgroup->RemoveAllOptions();
	PATgroup->RemoveAllOptions();
	text.LoadString(IDS_TS_PAT);
	PATgroup=new CMFCPropertyGridProperty(text);
	text.LoadString(IDS_TS_PMT);
	PMTgroup=new CMFCPropertyGridProperty(text);
	m_ftsbasicinfo.RemoveAll();
	m_ftspacketlist.DeleteAllItems();
	tsl_index=0;
}

int CSpecialFTSDlg::AppendTSLInfo(int pid,int type,int psi_type){
	//���ѡ���ˡ�������5000�������ж��Ƿ񳬹�5000��
	if(m_ftspacketlistmaxnum.GetCheck()==1&&tsl_index>5000){
		return 0;
	}
	CString temp_index,temp_pid,temp_type,temp_psi_type;
	int nIndex=0;
	switch(type){
	case 0:
		text.LoadString(IDS_TS_PES);
		temp_type.Format(_T("%s"),text);break;
	case 1:
		text.LoadString(IDS_TS_PSI);
		temp_type.Format(_T("%s"),text);break;
	default:
		text.LoadString(IDS_UNKNOWN);
		temp_type.Format(_T("%s"),text);break;
	}
	temp_index.Format(_T("%d"),tsl_index);
	temp_pid.Format(_T("%d"),pid);
	switch(psi_type){
	case 0:
		temp_psi_type.Format(_T(""));break;
	case 1:
		text.LoadString(IDS_TS_PAT);
		temp_psi_type.Format(_T("%s"),text);break;
	case 2:
		text.LoadString(IDS_TS_PMT);
		temp_psi_type.Format(_T("%s"),text);break;
	default:
		text.LoadString(IDS_UNKNOWN);
		temp_psi_type.Format(_T("%s"),text);break;
	}
	//��ȡ��ǰ��¼����
	nIndex=m_ftspacketlist.GetItemCount();
	//���С����ݽṹ
	LV_ITEM lvitem;
	lvitem.mask=LVIF_TEXT;
	lvitem.iItem=nIndex;
	lvitem.iSubItem=0;
	//ע��vframe_index������ֱ�Ӹ�ֵ��
	//���ʹ��f_indexִ��Format!�ٸ�ֵ��
	lvitem.pszText=temp_index.GetBuffer();
	//------------------------
	m_ftspacketlist.InsertItem(&lvitem);
	m_ftspacketlist.SetItemText(nIndex,1,temp_pid);
	m_ftspacketlist.SetItemText(nIndex,2,temp_type);
	m_ftspacketlist.SetItemText(nIndex,3,temp_psi_type);
	tsl_index++;
	return TRUE;
	return 0;
}

//ListCtrl����ɫ
void CSpecialFTSDlg::OnCustomdrawMyList ( NMHDR* pNMHDR, LRESULT* pResult )
{
	//This code based on Michael Dunn's excellent article on
	//list control custom draw at http://www.codeproject.com/listctrl/lvcustomdraw.asp

	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );

	// Take the default processing unless we set this to something else below.
	*pResult = CDRF_DODEFAULT;

	// First thing - check the draw stage. If it's the control's prepaint
	// stage, then tell Windows we want messages for every item.
	if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		// This is the notification message for an item.  We'll request
		// notifications before each subitem's prepaint stage.

		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
	{

		COLORREF clrNewTextColor, clrNewBkColor;

		int    nItem = static_cast<int>( pLVCD->nmcd.dwItemSpec );

		CString strTemp = m_ftspacketlist.GetItemText(nItem,2);
		CString text_pes,text_psi;
		text_pes.LoadString(IDS_TS_PES);
		text_psi.LoadString(IDS_TS_PSI);


		if(strTemp.Compare(text_pes)==0){
			clrNewTextColor = RGB(0,0,0);		//Set the text 
			clrNewBkColor = RGB(0,255,255);		//��ɫ
		}
		else if(strTemp.Compare(text_psi)==0){
			clrNewTextColor = RGB(0,0,0);		//text 
			clrNewBkColor = RGB(255,255,0);		//��ɫ
		}
		else{
			clrNewTextColor = RGB(0,0,0);		//text
			clrNewBkColor = RGB(255,255,255);			//��ɫ
		}

		pLVCD->clrText = clrNewTextColor;
		pLVCD->clrTextBk = clrNewBkColor;


		// Tell Windows to paint the control itself.
		*pResult = CDRF_DODEFAULT;


	}
}

int CSpecialFTSDlg::AppendBInfo(char *dst_group,char *property_name,char *value,char *remark){
	if(strcmp(dst_group,"PMT")==0){

#ifdef _UNICODE
		USES_CONVERSION;
		PMTgroup->AddSubItem(new CMFCPropertyGridProperty(A2W(property_name), A2W(value), A2W(remark)));
#else
		PMTgroup->AddSubItem(new CMFCPropertyGridProperty(property_name, (_variant_t)value, remark));
#endif

	}if(strcmp(dst_group,"PAT")==0){

#ifdef _UNICODE
		USES_CONVERSION;
		PATgroup->AddSubItem(new CMFCPropertyGridProperty(A2W(property_name), A2W(value), A2W(remark)));
#else
		PATgroup->AddSubItem(new CMFCPropertyGridProperty(property_name, (_variant_t)value, remark));
#endif

	}else{
	}
	return TRUE;
}

int CSpecialFTSDlg::ShowBInfo(){
	m_ftsbasicinfo.AddProperty(PMTgroup);
	m_ftsbasicinfo.AddProperty(PATgroup);
	return TRUE;
}


void CSpecialFTSDlg::OnBnClickedFTsAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}


void CSpecialFTSDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialogEx::OnDropFiles(hDropInfo);
	LPTSTR pFilePathName =(LPTSTR)malloc(MAX_URL_LENGTH);
	::DragQueryFile(hDropInfo, 0, pFilePathName,MAX_URL_LENGTH);  // ��ȡ�Ϸ��ļ��������ļ�������ؼ���
	m_ftsinputurl.SetWindowText(pFilePathName);
	::DragFinish(hDropInfo);   // ע����������٣��������ͷ�Windows Ϊ�����ļ��ϷŶ�������ڴ�
	free(pFilePathName);
}




void CSpecialFTSDlg::OnBnClickedFTsOutput()
{
	UpdateData(TRUE);
	if(m_ftsoutput==0){
		m_ftsdumpmode.EnableWindow(TRUE);
	}else{
		m_ftsdumpmode.EnableWindow(FALSE);
	}
}


void CSpecialFTSDlg::OnBnClickedFTsOutput2()
{
	UpdateData(TRUE);
	if(m_ftsoutput==0){
		m_ftsdumpmode.EnableWindow(TRUE);
	}else{
		m_ftsdumpmode.EnableWindow(FALSE);
	}
}


void CSpecialFTSDlg::OnSelchangeFTsLang()
{
	//�����ļ�·��
	char conf_path[300]={0};
	//���exe����·��
	GetModuleFileNameA(NULL,(LPSTR)conf_path,300);//
	//���exe�ļҼ�·��
	strrchr( conf_path, '\\')[0]= '\0';//
	//_getcwd(realpath,MYSQL_S_LENGTH);
	printf("%s",conf_path);
	strcat(conf_path,"\\configure.ini");
	//д�������ļ�
	switch(m_ftslang.GetCurSel()){
	case 0:WritePrivateProfileStringA("Settings","language","Chinese",conf_path);break;
	case 1:WritePrivateProfileStringA("Settings","language","English",conf_path);break;
	default:break;
	}
	//�������
	char exe_path[300]={0};
	//���exe����·��
	GetModuleFileNameA(NULL,(LPSTR)exe_path,300);
	ShellExecuteA( NULL,"open",exe_path,NULL,NULL,SW_SHOWNORMAL);
	OnCancel();
}

