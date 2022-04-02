// CSecondDlg.cpp: 实现文件
//

#include "pch.h"
#include "Cryptography.h"
#include "CSecondDlg.h"
#include "afxdialogex.h"
#include "RSA.cpp"

// CSecondDlg 对话框

IMPLEMENT_DYNAMIC(CSecondDlg, CDialogEx)

CSecondDlg::CSecondDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CSecondDlg::~CSecondDlg()
{
}

void CSecondDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_CBString(pDX, IDC_COMBO1, algorithm_str);
    DDX_CBString(pDX, IDC_COMBO2, algorithm_str);
    DDX_Control(pDX, IDC_COMBO1, m_Combo1);
    DDX_Control(pDX, IDC_COMBO2, m_Combo2);
}


BEGIN_MESSAGE_MAP(CSecondDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSecondDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDEncryption, &CSecondDlg::OnBnClickedEncryption)
    ON_BN_CLICKED(IDDecryption, &CSecondDlg::OnBnClickedDecryption)
    ON_BN_CLICKED(IDC_BUTTON2, &CSecondDlg::OnBnClickedButton2)
END_MESSAGE_MAP()

// CSecondDlg 消息处理程序

void CSecondDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
    CFile File;
    CFileException e;
    if (!File.Open(_T("readmeDH.txt"), CFile::modeRead, &e))
    {
        CString strErr;
        strErr.Format(_T("文件无法打开\n"));
        MessageBox(strErr);
    }
    //创建指定大小的Buffer
    DWORD  dwFileLenth = (DWORD)File.GetLength();
    //初始化buffer， 增加一个\0空间
    char* str = (char*)malloc((dwFileLenth + 1) * sizeof(char));
    memset(str, 0, dwFileLenth + 1);

    if (str != NULL)
    {
        //读取文件内容
        File.Read(str, dwFileLenth);
        CString cstr;
        cstr = str;
        MessageBox(cstr);
        File.Close();
        //显示文件内容
        //删除buffer，避免内存泄漏
        delete[] str;
        str = NULL;
    }
}

void CSecondDlg::OnBnClickedEncryption()
{
    // TODO: 在此添加控件通知处理程序代码
    GetDlgItem(IDC_COMBO1)->GetWindowText(algorithm_str);
    //在这里写各种密码的main函数

    if (algorithm_str == "RSA")
    {
        int m = 1000;
        ll* ptr = initprime(m);
        srand((unsigned)time(NULL));
        //生成随机数
        p = ptr[rand() % m];
        //素数p的最大原根a
        a = pri_root(p);
        Xa = rand() % p;
        Ya = q_pow(a, Xa, p);
        char str1[100] = {};
        itoa(Xa, str1, 10);
        CString Ya_str = (_T(""));
        Ya_str += str1;
        GetDlgItem(IDC_EDIT4)->SetWindowText(Ya_str);
        return;
    }
}

void CSecondDlg::OnBnClickedDecryption()
{
    // TODO: 在此添加控件通知处理程序代码
    GetDlgItem(IDC_COMBO2)->GetWindowText(algorithm_str);
    //在这里写各种密码的main函数

    if (algorithm_str == "RSA")
    {
        int m = 1000;
        ll* ptr = initprime(m);
        srand((unsigned)time(NULL));
        //生成随机数
        p = ptr[rand() % m];
        //素数p的最小原根a
        ll a = pri_root(p);
        Xb = rand() % p;
        Yb = q_pow(a, Xb, p);
        char str1[100] = {};
        itoa(Xb, str1, 10);
        CString Yb_str = (_T(""));
        Yb_str += str1;
        GetDlgItem(IDC_EDIT3)->SetWindowText(Yb_str);
        return;
    }
}


BOOL CSecondDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_Combo1.SetCurSel(0);
    m_Combo2.SetCurSel(0);
    // TODO:  在此添加额外的初始化

    return TRUE;  // return TRUE unless you set the focus to a control
                  // 异常: OCX 属性页应返回 FALSE
}


void CSecondDlg::OnBnClickedButton2()
{
    // TODO: 在此添加控件通知处理程序代码
    ll K = q_pow(Yb, Xa, p);
    char str1[100] = {};
    itoa(K, str1, 10);
    CString K_str = (_T("共同密钥为："));
    K_str += str1;
    MessageBox(K_str);
}
