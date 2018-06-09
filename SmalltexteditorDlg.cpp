// 小型文本编辑器Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Smalltexteditor.h"
#include "SmalltexteditorDlg.h"
#include "string"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// CMyDlg dialog

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)
	m_str1 = _T("");
	m_str2 = _T("");
	m_str4 = _T("");
	m_str5 = _T("");
	m_str6 = _T("");
	m_str3 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	Text_rear = 1;
    Text_head = NULL;
	Debug = false;
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
	DDX_Text(pDX, IDC_EDIT1, m_str1);
	DDX_Text(pDX, IDC_EDIT2, m_str2);
	DDX_Text(pDX, IDC_EDIT4, m_str4);
	DDX_Text(pDX, IDC_EDIT5, m_str5);
	DDX_Text(pDX, IDC_EDIT6, m_str6);
	DDX_Text(pDX, IDC_EDIT3, m_str3);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_INSERT, OnInsert)
	ON_BN_CLICKED(IDC_NEW, OnNew)
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_KEEP, OnKeep)
	ON_BN_CLICKED(IDC_TOTAL, OnTotal)
	ON_BN_CLICKED(IDC_SEARCH, OnSearch)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_QUIT, OnQuit)
	ON_BN_CLICKED(IDC_STEAD, OnStead)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

BOOL CMyDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyDlg::OnPaint() 
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
HCURSOR CMyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CMyDlg::PreTranslateMessage(MSG *pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		return true;
	}
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		return true;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CMyDlg::Read(CString FilePath)    //以链表形式读取文件
{

	ifstream fp(FilePath);
	Debug = true;

	CString C_str;
	string str;
	int i;
	m_str1 = "";

	while(getline(fp, str))
	{
		C_str = str.c_str();
		m_str1 += C_str;
		m_str1 += "\r\n";

		i = 0;
		DulNode *s = new DulNode;
		s->Node_str = new char[255];

		
		while(i < str.size())
		{
			s->Node_str[i] = str[i];
			i++;
			
		}
		
		
			
		s->Node_str[i] = '\0';
		
		
		if (Text_rear == 1)
		{
			Text_rear++;
			s->next = NULL;
			Text_head = s;
		}
		else
		{
			Text_rear++;
			DulNode *p = Text_head;
			
			while(p->next != NULL)
			{
				p = p->next;
			}
			
			s->next = p->next;
			p->next = s;
		}
		
	}

	fp.close();

	UpdateData(false);
}

void CMyDlg::Destory()             //清空链表
{
	if(Text_head != NULL)
	{
		DulNode *p = Text_head;
		
		while(p != NULL)
		{
			Text_head = Text_head ->next;
			
			delete[] p;
			
			p = Text_head;
		}
	}
}



void CMyDlg::OnNew()           //新建文件
{
	// TODO: Add your control notification handler code here

	UpdateData(true);

	Text_rear = 1;

	Destory();

	m_str1 = "";

	MessageBox("新建成功,请插入");

	Debug = true;

	UpdateData(false);
	
}

void CMyDlg::OnOpen()          //打开文件
{
	// TODO: Add your control notification handler code here

	UpdateData(true);

	Text_rear = 1;

	TCHAR szFilter[] =  _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");     //设置过滤器，只显示.txt与文件

	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);     //构造打开文件对话框
	
	CString  FilePath;

	if(IDOK == fileDlg.DoModal())
	{

		FilePath = fileDlg.GetPathName();
		CFile(FilePath, CFile::modeReadWrite);
		
		strFilePath = FilePath;
		
		Destory();

		Read(strFilePath);
	}
	
	UpdateData(false);
	
}

void CMyDlg::OnKeep()          //保存文件
{
	// TODO: Add your control notification handler code here

	UpdateData(true);

	if(Debug == false)
	{
		MessageBox("没有文本!");
		return;
	}


	TCHAR szFilter[] =  _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");    //设置过滤器，只显示.txt与文件

	CFileDialog fileDlg(FALSE, _T("txt"), NULL, 0, szFilter, this);     //构造保存文件对话框
	
	CString  FilePath;

	if(IDOK == fileDlg.DoModal())
	{

		FilePath = fileDlg.GetPathName();
		DulNode *p = Text_head;

		strFilePath = FilePath;


		CString strText;
		GetDlgItemText(IDC_EDIT1, strText);


		CStdioFile file;
		file.Open(strFilePath, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		file.WriteString(strText);


		file.Close();
		MessageBox("保存成功!");
	}
	else
	{
		MessageBox("保存失败!");
	}

	
	
	m_str1 = "";
	UpdateData(false);
	
}

void CMyDlg::OnInsert()             //插入
{
	// TODO: Add your control notification handler code here

	UpdateData(true);


	INT_PTR nRes;


	DulNode *p;

	int num = _ttoi(m_str3);;

	int m_str2_length = strlen(m_str2);

	

	if(Debug == false)
	{
		nRes = MessageBox("请新建!", MB_OK);
		if(IDOK == nRes)
		{
			return;
		}
	}

	if(m_str2_length == 0)
	{
		nRes = MessageBox("请输入字符!", MB_OK);
		if(IDOK == nRes)
		{
			return;
		}
	}

	if(num == 0)
	{
		nRes = MessageBox("请输入行数!", MB_OK);
		if(IDOK == nRes)
		{
			return;
		}
	}

	int i;
    
    if (num == 1)
    {
        DulNode *p;
		p = new DulNode;
		p ->Node_str = new char[255];

        Text_rear++;
	
        
        for(i = 0; i < m_str2_length; i++)
        {

            p ->Node_str[i] = m_str2[i];
        }

		p ->Node_str[i] = '\0';
		
        
        p ->next = Text_head;
		Text_head = p;

		nRes = MessageBox("插入成功!", MB_OK);
    }
	else
    {
		i = 1;
        p = Text_head;
        
		if (num > Text_rear)
		{
			nRes = MessageBox("插入错误!", MB_OK);
			if(IDOK == nRes)
			{
				return;
			}
		}
		else
		{
			Text_rear ++;
        
			while (i < num-1)
			{
				p = p ->next;
				i++;
			}
			
			DulNode *s = new DulNode;
			s ->Node_str = new char[255];
			
			for(i = 0; i < m_str2_length; i++)
			{
				s ->Node_str[i] = m_str2[i];
			}
			
		    s ->Node_str[i] = '\0';
			
			
			s ->next = p ->next;
			p->next = s;
			nRes = MessageBox("插入成功!", MB_OK);
		}
    }

	m_str1 = "";
	m_str2 = "";
	m_str3 = "";

	CString str;

	p = Text_head;

	while(p != NULL)
	{
		str.Format("%s", p->Node_str);
		m_str1 += str;
	    m_str1 += "\r\n";

		p = p->next;
	}

	UpdateData(false);

	
}

void CMyDlg::OnTotal()         //统计
{
	// TODO: Add your control notification handler code here

	UpdateData(true);
	INT_PTR nRes;

	int i;
	int i_num = 0;
	int c_num = 0;
	int else_num = 0;
	int Chinese_num = 0;
	int all_num = 0;
	int row_num = 0;

	

	DulNode *p = Text_head;

	if(p == NULL)
	{
		nRes = MessageBox("没有文本!", MB_OK);

		if(IDOK == nRes)
		{
			return;
		}
	}
	else
	{
		int k = 0;
		while(p!= NULL)
		{
			i = 0;
			int len = strlen(p->Node_str);

			
			
			while(i < len)
			{
				if(p->Node_str[i] >= '0' && p->Node_str[i] <= '9')
				{
					i_num++;
				}
				else if(p->Node_str[i] >= 'A' && p->Node_str[i] <= 'Z')
				{
					c_num++;
				}
				else if(p->Node_str[i] >='a' && p->Node_str[i] <= 'z')
				{
					c_num++;
				}
				else if(p->Node_str[i] < 0)
				{
					Chinese_num ++;
				}
				else
				{
					else_num ++;
				}
				k++;
				i++;
			}

			row_num++;
			p = p->next;
		}
		all_num = i_num + c_num + else_num + Chinese_num/2;

		CString str;

		str.Format("文本共有: \n数字个数:  %d \n字母个数: %d \n汉字个数: %d \n其他字符: %d \n总字数: %d \n行数: %d", i_num, c_num, Chinese_num/2, else_num, all_num, row_num);

		nRes = MessageBox(str, MB_OK);

		if(IDOK == nRes)
		{
			return;
		}
	}
	
}

void Get_next(char *str, int *next, int length)
{
    
    next[0] = -1;
    
    int k = -1;
    
    int q = 0;
    
    while (q < length-1)
    {
        if (k == -1 || str[q] == str[k])
        {
            if (str[++q] == str[++k])
            {
                next[q] = next[k];
            }
            else
            {
                next[q] = k;
            }
        }
        else
        {
            k = next[k];
        }
    }
   
}

void CMyDlg::OnSearch()            //查询
{ 
	// TODO: Add your control notification handler code here

	UpdateData();

	int i;
	int tem = 0;
	int line[255];
	int row[255];
	int lin = 0;
	int ro = 0;
	int num = 1;
	m_str6 = "";

	int m_str2_length = strlen(m_str4);

	char *ch = new char[m_str2_length];

	for(i = 0; i < m_str2_length; i++)
	{
		ch[i] = m_str4[i];
	}

	
	DulNode *p = Text_head;

	INT_PTR nRes;

	if(p == NULL)
	{
		nRes = MessageBox("没有文本!", MB_OK); 

		if(IDOK == nRes)
		{
			return;
		}
	}
	else if(m_str2_length == 0)
	{
		nRes = MessageBox("请输入!!", MB_OK); 

		if(IDOK == nRes)
		{
			return;
		}
	}
	else
	{
		while(p != NULL)
		{
			
            int len = strlen(p->Node_str);
			int plen = m_str2_length;
			int *next = new int[plen];

			Get_next(ch, next, plen);
			
		    i = 0;
			int j = 0;
			
			while (i < len && j < plen)
			{
				if (j == -1 || p->Node_str[i] == ch[j])
				{
					i++;
					j++;
				}
				else
				{
					j = next[j];
				}
				if(j == plen)
				{
					i = i-j+1;
					j = 0;
					if(p->Node_str[i] < 0)
					{
						line[lin++] = (i+1)/2;
					}
					else
					{
						line[lin++] = i;
					}
					
					row[ro++] = num;
					tem = 1;
				}
			}
			
			p = p->next;
			num++;
		}

	}

	if(tem == 0)
	{
		MessageBox("没有找到!");
	}

	m_str4 = "";
	int d, f;
	CString hj;

	for(d = 0, f = 0; d < lin; d++,f++)
	{
		hj.Format("行数%d  列数%d\r\n", row[d], line[f]);
		m_str6 +=hj;
	}

	UpdateData(false);

	
}

void CMyDlg::OnDelete()         //删除
{
	// TODO: Add your control notification handler code here

	UpdateData(true);

	int i, k;
	int tem = 0;
	int tem1;


	int m_str5_length = strlen(m_str5);

	char *ch = new char[m_str5_length];

	for(i = 0; i < m_str5_length; i++)
	{
		ch[i] = m_str5[i];
	}

	
	DulNode *p = Text_head;
	DulNode *q = p;

	INT_PTR nRes;

	if(p == NULL)
	{
		nRes = MessageBox("没有文本!", MB_OK); 

		if(IDOK == nRes)
		{
			return;
		}
	}
	else if(m_str5_length == 0)
	{
		nRes = MessageBox("请输入!!", MB_OK); 

		if(IDOK == nRes)
		{
			return;
		}
	}
	else
	{
		while(p != NULL)
		{
			tem1 = 0;
            int len = strlen(p->Node_str);
			int plen = m_str5_length;
			int *next = new int[plen];

			Get_next(ch, next, plen);
			
		    i = 0;
			int j = 0;
			
			while (i < len && j < plen)
			{
				
				if (j == -1 || p->Node_str[i] == ch[j])
				{
					i++;
					j++;
				}
				else
				{
					j = next[j];
				}
				if(j == plen)
				{
					i = i-j;
					tem = 1;
					
					k = i + plen;
					
					
					tem1 = 1;
					if(plen == len)
					{
						
						if(p == Text_head)
						{
							if (p->next == NULL)
							{
								p = Text_head = NULL;
								i = len;
							}
							else
							{
								p = p->next;
								q = Text_head = p;
								p = p->next;
								i = len;
							}
						}
						else
						{
							q->next = p->next;
							p = p->next;
							tem1 = 1;
							i = len;
							
						}
						
					}
					else
					{
						while(p->Node_str[k])
						{
							p->Node_str[i++] = p->Node_str[k++];
						}
						p->Node_str[i] = '\0';

						j = 0;
						i = 0;
						len = len - plen;
					}

				}
			}
			
			if(tem1 == 0)
			{
			       q = p;
			       p = p->next;
			}

		}
	

	}

	if(tem == 0)
	{
		MessageBox("没有找到!");
	}

	CString sd;
	m_str1 = "";
	m_str5 = "";

	p = Text_head;

	while(p != NULL)
	{
		sd.Format("%s", p->Node_str);
		m_str1 += sd;
	    m_str1 += "\r\n";

		p = p->next;
	}

	UpdateData(false);
	
}

void CMyDlg::OnStead() 
{
	// TODO: Add your control notification handler code here

	UpdateData();

	int i;
	int tem = 0;

	int m_str3_length = strlen(m_str3);
	int m_str5_length = strlen(m_str5);

	char *ch1 = new char[m_str3_length];
	char *ch2 = new char[m_str5_length];

	for(i = 0; i < m_str3_length; i++)
	{
		ch1[i] = m_str3[i];
	}

	for(i = 0; i < m_str5_length; i++)
	{
		ch2[i] = m_str5[i];
	}

	
	DulNode *p = Text_head;

	INT_PTR nRes;

	if(p == NULL)
	{
		nRes = MessageBox("没有文本!", MB_OK); 

		if(IDOK == nRes)
		{
			return;
		}
	}
	else if(m_str3_length == 0 && m_str5_length == 0)
	{
		nRes = MessageBox("请输入!!", MB_OK); 

		if(IDOK == nRes)
		{
			return;
		}
	}
	else
	{
		while(p != NULL)
		{
			
            int len = strlen(p->Node_str);
			int plen = m_str3_length;
			int *next = new int[plen];

			Get_next(ch1, next, plen);
			
		    i = 0;
			int j = 0;
			int y;
			
			while (i < len && j < plen)
			{
				if (j == -1 || p->Node_str[i] == ch1[j])
				{
					i++;
					j++;
				}
				else
				{
					j = next[j];
				}
				if(j == plen)
				{
					i = i-j;
					j = 0;

					

					int num = m_str3_length - m_str5_length;
					
					int a = 0;

					if(num > 0)
					{

						for(y = 0; y < m_str5_length; y++)
						{
							p->Node_str[i+y] = ch2[y];
						}

						while(p->Node_str[i+y+num+a] != '\0')
						{
							p->Node_str[i+y+a] = p->Node_str[i+y+num+a];
							a++;
						}
						p->Node_str[i+y+a] = '\0';
						
					}

					if(num == 0)
					{
						for(y = 0; y < m_str5_length; y++)
						{
							p->Node_str[i+y] = ch2[y];
						}

					}

					if(num < 0)
					{
						int h = strlen(p->Node_str);

						p->Node_str[h-num] = '\0';
						//h = h-1;

						while(h > i+m_str3_length)
						{
							p->Node_str[h-num-1] = p->Node_str[h-1];
							h--;
						}

						for(y = 0; y < m_str5_length; y++)
						{
							p->Node_str[i+y] = ch2[y];
						}

					}


					tem = 1;
				}
				len = strlen(p->Node_str);	
			}
			
			p = p->next;
		}

	}

	if(tem == 0)
	{
		MessageBox("没有找到!");
	}

	m_str1 = "";
	p = Text_head;
	CString sd;

	while(p != NULL)
	{
		sd.Format("%s", p->Node_str);
		m_str1 += sd;
	    m_str1 += "\r\n";

		p = p->next;
	}

	m_str3 = "";
	m_str5 = "";


	UpdateData(false);


	
}

void CMyDlg::OnQuit()       //退出
{
	// TODO: Add your control notification handler code here

	CDialog::OnOK();
	
}


