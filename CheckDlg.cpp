// CheckDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Check.h"
#include "CheckDlg.h"

#include <stdio.h>
#include <stdlib.h>

#include <MMSystem.h>
#include <DSound.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CCheckDlg *pDlg;

typedef unsigned char  uchar; /*  8 bits or more */
	
#define CRC_MASK    0xFFFFFFFFUL
#define UPDATE_CRC(crc, c)  \
    crc = crctable[(uchar)crc ^ (uchar)(c)] ^ (crc >> 8)
	DWORD  crctable[256]= {/*CRC 0xedb88320 */
		0x00000000l, 0x77073096l, 0xee0e612cl, 0x990951bal, 0x076dc419l, 0x706af48fl, 0xe963a535l, 0x9e6495a3l,
		0x0edb8832l, 0x79dcb8a4l, 0xe0d5e91el, 0x97d2d988l, 0x09b64c2bl, 0x7eb17cbdl, 0xe7b82d07l, 0x90bf1d91l,
		0x1db71064l, 0x6ab020f2l, 0xf3b97148l, 0x84be41del, 0x1adad47dl, 0x6ddde4ebl, 0xf4d4b551l, 0x83d385c7l,
		0x136c9856l, 0x646ba8c0l, 0xfd62f97al, 0x8a65c9ecl, 0x14015c4fl, 0x63066cd9l, 0xfa0f3d63l, 0x8d080df5l,
		0x3b6e20c8l, 0x4c69105el, 0xd56041e4l, 0xa2677172l, 0x3c03e4d1l, 0x4b04d447l, 0xd20d85fdl, 0xa50ab56bl,
		0x35b5a8fal, 0x42b2986cl, 0xdbbbc9d6l, 0xacbcf940l, 0x32d86ce3l, 0x45df5c75l, 0xdcd60dcfl, 0xabd13d59l,
		0x26d930acl, 0x51de003al, 0xc8d75180l, 0xbfd06116l, 0x21b4f4b5l, 0x56b3c423l, 0xcfba9599l, 0xb8bda50fl,
		0x2802b89el, 0x5f058808l, 0xc60cd9b2l, 0xb10be924l, 0x2f6f7c87l, 0x58684c11l, 0xc1611dabl, 0xb6662d3dl,
		0x76dc4190l, 0x01db7106l, 0x98d220bcl, 0xefd5102al, 0x71b18589l, 0x06b6b51fl, 0x9fbfe4a5l, 0xe8b8d433l,
		0x7807c9a2l, 0x0f00f934l, 0x9609a88el, 0xe10e9818l, 0x7f6a0dbbl, 0x086d3d2dl, 0x91646c97l, 0xe6635c01l,
		0x6b6b51f4l, 0x1c6c6162l, 0x856530d8l, 0xf262004el, 0x6c0695edl, 0x1b01a57bl, 0x8208f4c1l, 0xf50fc457l,
		0x65b0d9c6l, 0x12b7e950l, 0x8bbeb8eal, 0xfcb9887cl, 0x62dd1ddfl, 0x15da2d49l, 0x8cd37cf3l, 0xfbd44c65l,
		0x4db26158l, 0x3ab551cel, 0xa3bc0074l, 0xd4bb30e2l, 0x4adfa541l, 0x3dd895d7l, 0xa4d1c46dl, 0xd3d6f4fbl,
		0x4369e96al, 0x346ed9fcl, 0xad678846l, 0xda60b8d0l, 0x44042d73l, 0x33031de5l, 0xaa0a4c5fl, 0xdd0d7cc9l,
		0x5005713cl, 0x270241aal, 0xbe0b1010l, 0xc90c2086l, 0x5768b525l, 0x206f85b3l, 0xb966d409l, 0xce61e49fl,
		0x5edef90el, 0x29d9c998l, 0xb0d09822l, 0xc7d7a8b4l, 0x59b33d17l, 0x2eb40d81l, 0xb7bd5c3bl, 0xc0ba6cadl,
		0xedb88320l, 0x9abfb3b6l, 0x03b6e20cl, 0x74b1d29al, 0xead54739l, 0x9dd277afl, 0x04db2615l, 0x73dc1683l,
		0xe3630b12l, 0x94643b84l, 0x0d6d6a3el, 0x7a6a5aa8l, 0xe40ecf0bl, 0x9309ff9dl, 0x0a00ae27l, 0x7d079eb1l,
		0xf00f9344l, 0x8708a3d2l, 0x1e01f268l, 0x6906c2fel, 0xf762575dl, 0x806567cbl, 0x196c3671l, 0x6e6b06e7l,
		0xfed41b76l, 0x89d32be0l, 0x10da7a5al, 0x67dd4accl, 0xf9b9df6fl, 0x8ebeeff9l, 0x17b7be43l, 0x60b08ed5l,
		0xd6d6a3e8l, 0xa1d1937el, 0x38d8c2c4l, 0x4fdff252l, 0xd1bb67f1l, 0xa6bc5767l, 0x3fb506ddl, 0x48b2364bl,
		0xd80d2bdal, 0xaf0a1b4cl, 0x36034af6l, 0x41047a60l, 0xdf60efc3l, 0xa867df55l, 0x316e8eefl, 0x4669be79l,
		0xcb61b38cl, 0xbc66831al, 0x256fd2a0l, 0x5268e236l, 0xcc0c7795l, 0xbb0b4703l, 0x220216b9l, 0x5505262fl,
		0xc5ba3bbel, 0xb2bd0b28l, 0x2bb45a92l, 0x5cb36a04l, 0xc2d7ffa7l, 0xb5d0cf31l, 0x2cd99e8bl, 0x5bdeae1dl,
		0x9b64c2b0l, 0xec63f226l, 0x756aa39cl, 0x026d930al, 0x9c0906a9l, 0xeb0e363fl, 0x72076785l, 0x05005713l,
		0x95bf4a82l, 0xe2b87a14l, 0x7bb12bael, 0x0cb61b38l, 0x92d28e9bl, 0xe5d5be0dl, 0x7cdcefb7l, 0x0bdbdf21l,
		0x86d3d2d4l, 0xf1d4e242l, 0x68ddb3f8l, 0x1fda836el, 0x81be16cdl, 0xf6b9265bl, 0x6fb077e1l, 0x18b74777l,
		0x88085ae6l, 0xff0f6a70l, 0x66063bcal, 0x11010b5cl, 0x8f659effl, 0xf862ae69l, 0x616bffd3l, 0x166ccf45l,
		0xa00ae278l, 0xd70dd2eel, 0x4e048354l, 0x3903b3c2l, 0xa7672661l, 0xd06016f7l, 0x4969474dl, 0x3e6e77dbl,
		0xaed16a4al, 0xd9d65adcl, 0x40df0b66l, 0x37d83bf0l, 0xa9bcae53l, 0xdebb9ec5l, 0x47b2cf7fl, 0x30b5ffe9l,
		0xbdbdf21cl, 0xcabac28al, 0x53b39330l, 0x24b4a3a6l, 0xbad03605l, 0xcdd70693l, 0x54de5729l, 0x23d967bfl,
		0xb3667a2el, 0xc4614ab8l, 0x5d681b02l, 0x2a6f2b94l, 0xb40bbe37l, 0xc30c8ea1l, 0x5a05df1bl, 0x2d02ef8dl
	};	
#define BUFFERSIZE  1024
#define CRCPOLY     0xEDB88320UL /* 1110 1101 1001 1000 1000 0011 0010 0000 */

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckDlg dialog

CCheckDlg::CCheckDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCheckDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCheckDlg)
	m_RichEditMessage = _T("");
	m_CheckBoxCreateLog = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	pDlg=this;
}

void CCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCheckDlg)
	DDX_Control(pDX, IDC_CHECK_CREATE_LOG, m_CheckBoxCreateLogCtrl);
	DDX_Control(pDX, IDC_RICHEDIT_INFORMATION_BOX, m_RichEditControl);
	DDX_Text(pDX, IDC_RICHEDIT_INFORMATION_BOX, m_RichEditMessage);
	DDX_Check(pDX, IDC_CHECK_CREATE_LOG, m_CheckBoxCreateLog);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCheckDlg, CDialog)
	//{{AFX_MSG_MAP(CCheckDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_START_CHOOSESOURCEFOLDER, OnStartChooseSourceFolder)
	ON_BN_CLICKED(IDC_BUTTON_WRITE_REPORT, OnButtonWriteReport)
	ON_COMMAND(ID_START_CHOOSEDESTINATIONFOLDER, OnStartChooseDestinationFolder)
	ON_BN_CLICKED(IDC_BUTTON_CHECK_ARCHIVE, OnButtonCheckArchive)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckDlg message handlers

BOOL CCheckDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
    CHARFORMAT cf;
    this->m_RichEditControl.GetDefaultCharFormat(cf);
  
	cf.bCharSet=ANSI_CHARSET;
    
	strcpy(cf.szFaceName, "Courier New"); ;
	
	this->m_RichEditControl.SetDefaultCharFormat(cf);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCheckDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCheckDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCheckDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
///++++++++++    НАЧАЛО КОДА, НАПИСАННОГО ВРУЧНУЮ     ++++++
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
///++++++++++        Глобальные переменные      ++++++++++++
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

CString sPathDestination, sPathSource;
CString cLogFileMessage, cLogFileResult;
CFile hLogFile;		// файл отчета, пригодный для печти

int FlagInit = 0;		// для управления отркрытием и закрытием файлов
CFile hReportFile;	// основной бинарный файл отчета

int NumberOfFiles=0; 
DWORD dwTotalCheckSum = 0;

///++++++++++++++++++ Основные функции  ++++++++++++++++++++

//++++++++++Пункты меню Начало+++++++++++++++++++++++
void CCheckDlg::OnStartChooseSourceFolder()  // выбор каталога для подсчета КС файлов
{
	// Эта функция для обработки выбора пункта меню выбор каталога-источника
 	sPathSource = ChooseFolder("Выберите каталог-источник");
	m_RichEditMessage ="Каталог-источник          : ";
	if (sPathSource == "")	
		m_RichEditMessage+="не указан";
	else 
		m_RichEditMessage+=sPathSource;
	
	m_RichEditMessage+="\nКаталог для отчёта        : ";	
	if (sPathDestination == "")	
		m_RichEditMessage+="не указан";
	else 
		m_RichEditMessage+=sPathDestination;

	UpdateData(FALSE);
}

void CCheckDlg::OnStartChooseDestinationFolder()  // выбор каталога для размещения результата работы
{
	// Эта функция для обработки выбора пункта меню выбор каталога назначения
	sPathDestination = ChooseFolder("Выберите каталог для отчёта");
	m_RichEditMessage ="Каталог-источник          : ";
	if (sPathSource == "")	
		m_RichEditMessage+="не указан";
	else 
		m_RichEditMessage+=sPathSource;
	
	m_RichEditMessage+="\nКаталог для отчёта        : ";	
	if (sPathDestination == "")	
		m_RichEditMessage+="не указан";
	else 
		m_RichEditMessage+=sPathDestination;

	UpdateData(FALSE);
}

//++++++++++++Пункты меню Конец+++++++++++++++++++++++++
CString CCheckDlg::ChooseFolder(CString lpszTitle)   // функция, обеспечивающая выбор каталога
{
	// В этой функции вызываем диалог для выбора папки, функция возвращает путь
	TCHAR path[MAX_PATH*4];// переменная для хранения полученного пути к каталогу
    BROWSEINFO lpbi;
    ITEMIDLIST *Id;
	
    lpbi.hwndOwner = 0;		//задаются параметры структуры BROWSEINFO
    lpbi.pidlRoot = NULL;
    lpbi.pszDisplayName = path;
    lpbi.lpszTitle  = lpszTitle;//_T("Выберите Каталог");
    lpbi.ulFlags = NULL; // BIF_BROWSEINCLUDEFILES; //флаги управляющие внешним видом
    lpbi.lpfn = NULL;
    lpbi.lParam = NULL;
    lpbi.iImage = NULL;
	
    Id = SHBrowseForFolder(&lpbi);
	//SHGetPathFromIDList(Id, tmp_path);
    if(Id)	{
        SHGetPathFromIDList(Id, path);
    }	else sprintf(path,"%s","");//не очень удобно, по кнопке отмены - путь обнуляется 
	return path;
}

//+++++++++++++++++Кнопки Начало+++++++++++++++++++++++++++++++++
void CCheckDlg::OnButtonWriteReport()   // Нbажатие кнопки подготовить отчет
{		
	// Обработка нажатия кнопки Подготовка отчета
	cLogFileResult="";

	if (sPathSource == "") {
			OnStartChooseSourceFolder();
			if 	(sPathSource == "") 
					return;
	}
	
	if (sPathDestination == "") {	// диалог при не выбранном каталоге для отчета			
				OnStartChooseDestinationFolder();
				if 	(sPathDestination == "") 
					return;
	}

	char buf1[20],buf2[20];
	CTime theTime = CTime::GetCurrentTime();  // для вывода текущего времени
	CString cTime;
	cTime = theTime.Format("%d.%m.%y   %X");

	BrowseAndCalculateCheckSum(sPathSource);
	
	sprintf(buf1,"%d", NumberOfFiles);
	sprintf(buf2,"%08X", dwTotalCheckSum);	
	//-------------------------	
	// Проверка для обрезки пути до относительного.	
	CString sPathSourceShort;
	int i;
	i = sPathSource.ReverseFind('\\');  
	
	if((sPathSource.Find('\\')!=sPathSource.ReverseFind('\\'))&&(i!=-1))
	{
       i = sPathSource.ReverseFind('\\');  
	   i++;
	}else
	{
       i = sPathSource.ReverseFind('\\');  
	   i--;
	}			
	if (i!=-1)	{
		sPathSourceShort.Format("%s",sPathSource.GetBuffer(0)+i);
	}
	else	{
		sPathSourceShort = sPathSource;
	}
	//-----------------------		
	cLogFileMessage = "Отчёт создан                    : " + cTime +"\nИсточник                          : "+sPathSourceShort+"\n"+"Файлов обработано       : "+buf1+"\nКонтрольная сумма       : "+buf2;
	CreateLogFile(cLogFileMessage);
    
	if (cLogFileResult=="") {
		if (sPathDestination!="")
			cLogFileResult="\nФайлы отчета Report_CRC32.lcr и LogFile_CRC32.txt созданы : " + cTime;
		else
			cLogFileResult="\nКонтрольная сумма вычислена : " + cTime;
	}
		
	m_RichEditMessage ="Каталог-источник          : " + sPathSource+ "\nКаталог для отчёта        : "+ sPathDestination +"\nФайлов                    : "+buf1+"\nКонтрольная сумма         : "+buf2+cLogFileResult;

	UpdateData(FALSE);		
}
	
void CCheckDlg::OnButtonCheckArchive() // Кнопка проверить архив
{
	// Обработка нажатия кнопки Проверить Архив	
	CString cResult;
	cLogFileResult=="";
		
	if (sPathSource == "") {
			OnStartChooseSourceFolder();
			if 	(sPathSource == "") 
					return;
	}
	
	if (sPathDestination == "") {	// диалог при не выбранном каталоге для отчета			
				OnStartChooseDestinationFolder();
				if 	(sPathDestination == "") 
					return;
	}
	
	char buf1[20],buf2[20];
	CTime theTime = CTime::GetCurrentTime();  // для вывода текущего времени
	CString cTime;
	cTime = theTime.Format("%d.%m.%y   %X");
	// возвращаемое значение 9 - не удалось открыть файл отчета
	// возвращаемое значение 1 - не найдены(не удалось получить доступ) файлы 
	// возвращаемое значение 2 - изменилась контрольная сумма файла 
	// возвращаемое значение 3 - изменилась и контрольная сумма файла и есть ошибки чтения файлов
	switch (BrowseAndCompareCheckSum(sPathSource))	
	{
		case 0:
			cResult = "\nРезультат                 : Проверка прошла успешно.";
			break;
		case 1:
			cResult = "\nРезультат                 : Внимание! Ошибка открытия файлов";
			break;
		case 2:
			cResult = "\nРезультат                 : Контрольная сумма изменилась. Обнаружены искаженные файлы";
			break;
		case 3:
			cResult = "\nРезультат                 : Контрольная сумма изменилась. Обнаружены искаженные файлы. Ошибка открытия файлов";
			break;		
		case 9:
			cResult = "\nРезультат                 : Внимание! Ошибка открытия служебного файла со списком контрольных сумм";
			break;
		default:
			cResult = "\nРезультат                 : ";
			break;
	}

	sprintf(buf1,"%d", NumberOfFiles);	
	sprintf(buf2,"%08X", dwTotalCheckSum);
	//-------------------------	
	// Проверка для обрезки пути до относительного.	
	CString sPathSourceShort;
	int i;
	i = sPathSource.ReverseFind('\\');  
	
	if((sPathSource.Find('\\')!=sPathSource.ReverseFind('\\'))&&(i!=-1))
	{
       i = sPathSource.ReverseFind('\\');  
	   i++;
	}else
	{
       i = sPathSource.ReverseFind('\\');  
	   i--;
	}			
	if (i!=-1)	{
		sPathSourceShort.Format("%s",sPathSource.GetBuffer(0)+i);
	}
	else	{
		sPathSourceShort = sPathSource;
	}
	//-----------------------
	
	cLogFileMessage = "Отчёт создан                    : " + cTime+"\nИсточник                          : "+sPathSourceShort+"\n"+"Файлов обработано       : "+buf1+"\nКонтрольная сумма       : "+buf2+cResult;
	
	if (cLogFileResult != "")
		cLogFileMessage+=cLogFileResult;
	
	m_RichEditMessage ="Каталог-источник          : " + sPathSource+ "\nКаталог для отчёта        : "+ sPathDestination +"\nФайлов                    : "+buf1+"\nКонтрольная сумма         : "+buf2;
	
	if (CreateLogFile(cLogFileMessage) != 9)	{
		
		if (sPathDestination!="")
			m_RichEditMessage +="\nФайл отчёта создан        : " + cTime+cResult;
		else
			m_RichEditMessage +="\nПроверка произведена      : " + cTime+cResult;
	}
	else	{
			m_RichEditMessage +="\nНе удалось создать файл отчёта"+cResult;
	}
	
	UpdateData(FALSE);	
}
//++++++++++++++++Кнопки Конец++++++++++++++++++++++++++++++++++++
// Запись файла отчета
// Возвращает 9 если не удалось создать файл отчёта
int CCheckDlg::CreateLogFile(CString LogMessage)
{
	CStdioFile hLogFile;
	
	if (hLogFile.Open(sPathDestination+"\\LogFile_CRC32.txt", CFile::modeCreate | CFile::modeWrite )==NULL)	{		
		MessageBox("Не удалось создать файл отчёта по указанному пути:\n"+sPathDestination,"Внимание!", MB_ICONHAND);
		cLogFileResult = "\nНе удалось создать файл отчёта";
		
		return 9;
	}
	else	{	
		hLogFile.WriteString(LogMessage.GetBuffer(0));
		hLogFile.Close();
	}
	return 0;
}

//++++++++++++++++Функции отвечающие за основную логику приложения:++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++
// Возвращаем CompareResult = 5 если произошла ошибка открытия файлов в катологе источнике;
// Возвращаем 9, если ошибка создания файла отчета.
int CCheckDlg::BrowseAndCalculateCheckSum(CString RootPath)   // функция перебора всех файлов и подкаталогов. она же пишет в файл отчета КС
{
	int CompareResult = 0;
	CString NextRoot = RootPath;
	CString ComprString;	
	DWORD dwCheckSum = 0;
	short int PathLength;
	
	if(FlagInit==0) 	// to maintain file.open procedure
	{
        FlagInit++; 
		dwTotalCheckSum = 0;
		NumberOfFiles = 0;
		
		if (hReportFile.Open(sPathDestination + "\\Report_CRC32.lcr", CFile::modeCreate | CFile::modeWrite )== NULL)	{
			MessageBox("Не удалось создать служебный файл со списком контрольных сумм по указанному пути:\n"+sPathDestination,"Внимание!", MB_ICONHAND);
			FlagInit=0;
			return 9;
		}		

		if ((NextRoot.GetLength() == 3)&&(NextRoot.Replace(":\\",":\\") == 1))   /// если выбрали корневую папку диска
			NextRoot.Replace("\\",NULL);
	}else
		FlagInit++;

	HANDLE hFindFile;			/// this block is getting files and folders from a folder
	WIN32_FIND_DATA fd;
	
	hFindFile=FindFirstFile(NextRoot + "\\*", &fd);    /// Looking for a first file  should check if it is a file or a folder

	/// Обработка первого файла!!
///-----------------------------------
	ComprString = fd.cFileName;

		if ((FILE_ATTRIBUTE_DIRECTORY & fd.dwFileAttributes)&&(("." != ComprString)&&(".." != ComprString)))// проверяем, если это папка, но не служебная 
					BrowseAndCalculateCheckSum(NextRoot+"\\"+ComprString);

		else 
			if (!(FILE_ATTRIBUTE_DIRECTORY & fd.dwFileAttributes))	 {   // если не папка
				char pBufFilePath[MAX_PATH];    
				CString cFullPath;
			
				cFullPath = NextRoot + "\\"; // чтобы добавить полный путь - склеиваем
				cFullPath += fd.cFileName;
				cFullPath.Replace(sPathSource, NULL); // запись только относительного пути			
				sprintf(pBufFilePath,"%s", cFullPath);  // добавляем полное имя

				PathLength = 0; // Пишем цикл, в котором пишем в файл определенной длины сегмент, длина которого - pBufFilePath[] до нуль-терминатора
				for(int i=0;i<MAX_PATH;i++)	{
					if (pBufFilePath[i] != 0)
						PathLength++;
					else	{
						PathLength++;
						break;
					}
				}			
				
					
				if ((ComprString != "Report_CRC32.lcr")&&(ComprString != "LogFile_CRC32.txt")) {	// не будем запысывать в отчет информацию о файлах Report_CRC32.lcr и LogFile_CRC32.txt										

					if (CalculateCheckSum(NextRoot + "\\" + ComprString, &dwCheckSum) == 9)	{		// call for this function to calculate check summ for the file
						m_RichEditMessage+="\n\n****** Внимание! Нет доступа к файлу: " +NextRoot + "\\" + ComprString +" данные о нем не добавлены в отчёт";						
						CompareResult = 5;
					}
					else	{											
						NumberOfFiles++;
						dwTotalCheckSum+=dwCheckSum;
						hReportFile.Write(pBufFilePath, PathLength);//пишем из буфера только путь длиной в размер пакета (with null-terminator)
						hReportFile.Write(&dwCheckSum, 4);
					}
				}
			}			
///-----------------------------------	
			
	while (FindNextFile(hFindFile, &fd))     //looking for the rest files
	{	
		ComprString = fd.cFileName;

		if ((FILE_ATTRIBUTE_DIRECTORY & fd.dwFileAttributes)&&(("." != ComprString)&&(".." != ComprString)))// проверяем, если это папка, но не служебная 
					BrowseAndCalculateCheckSum(NextRoot+"\\"+ComprString);
		else 
			if (!(FILE_ATTRIBUTE_DIRECTORY & fd.dwFileAttributes))	 {   // если не папка
				char pBufFilePath[MAX_PATH];    
				CString cFullPath;
			
				cFullPath = NextRoot + "\\"; // чтобы добавить полный путь - склеиваем
				cFullPath += fd.cFileName;
				cFullPath.Replace(sPathSource, NULL); // запись только относительного пути			
				sprintf(pBufFilePath,"%s", cFullPath);  // добавляем полное имя

				PathLength = 0; // Пишем цикл, в котором пишем в файл определенной длины сегмент, длина которого - pBufFilePath[] до нуль-терминатора
				for(int i=0;i<MAX_PATH;i++)	{
					if (pBufFilePath[i] != 0)
						PathLength++;
					else	{
						PathLength++;
						break;
					}
				}			
									
				if ((ComprString != "Report_CRC32.lcr")&&(ComprString != "LogFile_CRC32.txt")) {	// не будем запысывать в отчет информацию о файлах Report_CRC32.lcr и LogFile_CRC32.txt										

					if (CalculateCheckSum(NextRoot + "\\" + ComprString, &dwCheckSum) == 9)	{		// call for this function to calculate check summ for the file
						m_RichEditMessage+="\n\n****** Внимание! Нет доступа к файлу: " +NextRoot + "\\" + ComprString +" данные о нем не добавлены в отчёт";						
						CompareResult = 5;
					}
					else	{											
						NumberOfFiles++;
						dwTotalCheckSum+=dwCheckSum;
						hReportFile.Write(pBufFilePath, PathLength);//пишем из буфера только путь длиной в размер пакета (with null-terminator)
						hReportFile.Write(&dwCheckSum, 4);
					}
				}
			}		
	}		

	FlagInit--; 		// to close report file before exit 
	if(FlagInit==0)
	{        
		hReportFile.Close();

        BYTE newAttribute =0x01;    /// ставим атрибуты readonly
        CFileStatus status;
        hReportFile.GetStatus( sPathDestination + "\\Report_CRC32.lcr", status );
        status.m_attribute = newAttribute;
        hReportFile.SetStatus( sPathDestination + "\\Report_CRC32.lcr", status );

	}
	return CompareResult;
}

//----------------------------------------------
//Проверяем архив так: ищем файл отчета, считываем оттуда пути и считаем контрольную сумму для каждого файла,
//затем сравниваем с суммой в отчете. Если не совпало - выводим предупреждение и делаем пометку в файле отчета. 
// возвращаемое значение 9 - не удалось открыть файл отчета
// возвращаемое значение 1 - не найдены(не удалось получить доступ) файлы 
// возвращаемое значение 2 - изменилась контрольная сумма файла 
// возвращаемое значение 3 - изменилась и контрольная сумма файла и есть ошибки чтения файлов
//
int CCheckDlg::BrowseAndCompareCheckSum(CString RootPath)   // Используем эту функцию для проверки архива 
{
	int CompareResult = 0;
	CString NextRoot = RootPath;
	DWORD dwCheckSum = 0, dwCheckSumFromReport;		// для хранения контрольных сумм
	DWORD CurrentPosition;
	CString cFileNameFromReport;
	int PathLength;		//для считывания определенной длины пути из файла отчета

	dwTotalCheckSum = 0;
	NumberOfFiles = 0;
	CurrentPosition=0;
	cLogFileResult="";
	if (!hReportFile.Open(RootPath + "\\Report_CRC32.lcr", CFile::modeRead))		{		// если не удалось открыть файл отчета
		MessageBox("Ошибка открытия файла отчета","Внимание!", MB_OK | MB_ICONERROR);
		m_RichEditMessage+="\n\nНе удалось открыть служебный файл со списком контрольных сумм в каталоге " +RootPath+" : проверьте наличие и целостность";
		
		cLogFileResult = "\n\nНе удалось открыть служебный файл со списком контрольных сумм в каталоге " +RootPath+" : проверьте наличие и целостность";                   /// Нужно написать надпись для предупреждения
		return 9;
	}

	while (CurrentPosition < hReportFile.GetLength())	{		//цикл чтения файла отчета
		//++++++++++++++++++   Часть относится к чтению из файла
		char pbuf[(MAX_PATH)*2];  // the maximum file name 
		char buf[4]; //для CheckSum
		
		hReportFile.Read(pbuf, (MAX_PATH)); // часть, относящаяся к адресу
		
		PathLength = 0;					// Пишем цикл, в котором ищем pbuf[] до нуль-терминатора
		for(int i=0;i<MAX_PATH;i++)	{
			if (pbuf[i] != 0)	{
				PathLength++;
				//cFileNameFromReport+=pbuf[i]; //для хранения имени текущего файля из отчета
				//m_RichEditMessage+=pbuf[i];   // for debugging needs
			}
			else {
				PathLength++;
				break;
			}
		}
		
		cFileNameFromReport = pbuf;//для хранения имени текущего файля из отчета
		
		CurrentPosition += PathLength;		
		hReportFile.Seek(CurrentPosition,CFile::begin);	// передвигаем указатель на начало контрольной суммы mooving file pointer to the position we need
		hReportFile.Read(buf, 4);  //часть, относящаяся к контрольной сумме
		CurrentPosition += 4; // запомнили конечное положение указателя позиции в файле
		
		DWORD *IntNum;		/// считывание чексуммы
		IntNum=(DWORD*)buf;  // для приведения типов
		
		dwCheckSumFromReport = *IntNum;
		
		// ++++++++++++++++++++++++
		char useItForOutput[20];		
		 /*
		//-----------------------------------------------------------//debugging stuff
		sprintf(useItForOutput,"%X",dwCheckSumFromReport);
		m_RichEditMessage+="\n  "+NextRoot + cFileNameFromReport +": ";	  //сумма из файла отчёта
		m_RichEditMessage+=useItForOutput;	//сумма из отчета
		//-----------------------------------------------------------//debugging stuff
		 */
		if (CalculateCheckSum(NextRoot + cFileNameFromReport, &dwCheckSum) == 9)	{			// call for this function to calculate check summ for the file
			m_RichEditMessage+="\n\n****** Внимание! Ошибка открытия файла: " + sPathSource + cFileNameFromReport;
			
			cLogFileResult +="\n" + cFileNameFromReport + " \tОшибка открытия файла";
			if (CompareResult ==0) 
				CompareResult = 1;
				else if (CompareResult == 2)
					CompareResult = 3;/// Но выхода-то нет, поэтому этот результат никуда не передается, кроме записи в текст. строку		
		}
		else	{			
			NumberOfFiles++;
			dwTotalCheckSum+=dwCheckSum;

			if (dwCheckSum != dwCheckSumFromReport)	{          //Сравниваем посчитанную и сумму из файла
				
				m_RichEditMessage+="\n\n! ****** Внимание! Контрольная сумма файла: "+cFileNameFromReport+" изменилась: ****** !\n";
				sprintf(useItForOutput,"%08X",dwCheckSumFromReport);
				m_RichEditMessage+="  "+cFileNameFromReport +": Была: <";	
				m_RichEditMessage+=useItForOutput;
				
				sprintf(useItForOutput,"%08X",dwCheckSum);
				m_RichEditMessage+=">\tСтала: <";
				m_RichEditMessage+=useItForOutput;
				m_RichEditMessage+=">\n! **************** !\n";

				cLogFileResult +="\n" + cFileNameFromReport +" \tИскажена контрольная сумма";
				if (CompareResult ==0)
					CompareResult = 2;
				else if (CompareResult == 1)
					CompareResult = 3;/// Но выхода-то нет, поэтому этот результат никуда не передается, кроме записи в текст. строку
			}
		}				
	}				
	hReportFile.Close();			
	return CompareResult;
}

//---------------------------------------------
// Возвращает return 9, если не смогла открыть файл.
// Возврат 8, если служебный файл
int CCheckDlg::CalculateCheckSum(CString path,DWORD *pCS)     // функция по подсчету CRC здесь же рекомендуется запоминать длину файла, чтобы избежать атак-инъекций на коллизию CRC
{
	DWORD CRC_Sum=0;
	
	if ((0 == path.Replace("\\Report_CRC32.lcr",NULL))&&(0 == path.Replace("\\LogFile_CRC32.txt",NULL)) ) {   /// проверяем, что это не служебные файлы
		if (CRC(path,&CRC_Sum)==9) {		
			return 9;
		}
	}

	else 
		return 8;

	*pCS=CRC_Sum;  //возвращаем контрольную сумму
	
	return 0;
}

// подсчет Контрольной суммы файла расположенного по указанному пути
// Возвращает return 9, если не смогла открыть файл.
int CCheckDlg::CRC(CString path,DWORD *pCS)    // через указатель передаем вычесленное значение контрольной суммы 
{	
	DWORD   crc;
	FILE   *fp;
		
	size_t len;
	char *buffer, *sav;
			
	if ( ( fp = fopen(path, "rb" ) ) == NULL )	{		
		return 9; 
	}
    crc = CRC_MASK;
    buffer = (char *) calloc( BUFFERSIZE,1 );
	sav = buffer;
	while ( ( len = fread(buffer,1,BUFFERSIZE,fp) ) > 0 ) {
		while ( len-- ) UPDATE_CRC( crc, *buffer++ );
		buffer = sav;
	}
	free(buffer);
	len = (unsigned int)(crc>>16);  // длина в байтах
	//printf( "File = %13s CRC32 = %04x %04x\n", path, (int)~len, (int)~crc );
	
	fclose( fp );
	flushall();

    *pCS=~crc;

	return 0;
}


int Thread()
{

	CString cTime;
	char buf1[20],buf2[20];

	pDlg->BrowseAndCalculateCheckSum(sPathSource);


	sprintf(buf1,"%d", NumberOfFiles);
	sprintf(buf2,"%08X", dwTotalCheckSum);	
	//-------------------------	
	// Проверка для обрезки пути до относительного.	
	CString sPathSourceShort;
	int i;
	i = sPathSource.ReverseFind('\\');  
	
	if((sPathSource.Find('\\')!=sPathSource.ReverseFind('\\'))&&(i!=-1))
	{
       i = sPathSource.ReverseFind('\\');  
	   i++;
	}else
	{
       i = sPathSource.ReverseFind('\\');  
	   i--;
	}			
	if (i!=-1)	{
		sPathSourceShort.Format("%s",sPathSource.GetBuffer(0)+i);
	}
	else	{
		sPathSourceShort = sPathSource;
	}
	//-----------------------		
	cLogFileMessage = "Отчёт создан                    : " + cTime +"\nИсточник                          : "+sPathSourceShort+"\n"+"Файлов обработано       : "+buf1+"\nКонтрольная сумма       : "+buf2;
	pDlg->CreateLogFile(cLogFileMessage);
    
	if (cLogFileResult=="") {
		if (sPathDestination!="")
			cLogFileResult="\nФайлы отчета Report_CRC32.lcr и LogFile_CRC32.txt созданы : " + cTime;
		else
			cLogFileResult="\nКонтрольная сумма вычислена : " + cTime;
	}
		
	pDlg->m_RichEditMessage ="Каталог-источник          : " + sPathSource+ "\nКаталог для отчёта        : "+ sPathDestination +"\nФайлов                    : "+buf1+"\nКонтрольная сумма         : "+buf2+cLogFileResult;

	pDlg->UpdateData(FALSE);
	return 0;
}


//*****************************************************************************
//*************      Конец кода,написанного вручную      **********************
//*****************************************************************************
