// CDHDecryptionDialog.cpp: 实现文件
//

#include "pch.h"
#include "Client.h"
#include "CDHDecryptionDialog.h"
#include "afxdialogex.h"
#include "RSA.cpp"
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll

// CDHDecryptionDialog 对话框

IMPLEMENT_DYNAMIC(CDHDecryptionDialog, CDialogEx)

CDHDecryptionDialog::CDHDecryptionDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG42, pParent)
{

}

CDHDecryptionDialog::~CDHDecryptionDialog()
{
}

void CDHDecryptionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, key_str);
    DDX_CBString(pDX, IDC_COMBO1, algorithm_str);
    DDX_Control(pDX, IDC_COMBO1, m_Combo1);
}


BEGIN_MESSAGE_MAP(CDHDecryptionDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDHDecryptionDialog::OnBnClickedButton1)
    ON_BN_CLICKED(IDEncryption, &CDHDecryptionDialog::OnBnClickedEncryption)
END_MESSAGE_MAP()


// CDHDecryptionDialog 消息处理程序


void CDHDecryptionDialog::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
    CFile File;
    CFileException e;
    if (!File.Open(_T("../../Cryptography/Cryptography/readmeDH.txt"), CFile::modeRead, &e))
    {
        CString strErr;
        strErr.Format(_T("文件无法打开\n"), e.m_cause);
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


BOOL CDHDecryptionDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_Combo1.SetCurSel(0);
    // TODO:  在此添加额外的初始化

    return TRUE;  // return TRUE unless you set the focus to a control
                  // 异常: OCX 属性页应返回 FALSE
}


void CDHDecryptionDialog::OnBnClickedEncryption()
{
    // TODO: 在此添加控件通知处理程序代码
    CFile File;
    CFileException e;
    if (!File.Open(_T("../../Cryptography/Cryptography/DHkeyFromA.txt"), CFile::modeRead, &e))
    {
        CString strErr;
        strErr.Format(_T("文件无法打开\n"), e.m_cause);
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
        p = 0;
        for (int i = 0;i < strlen(str);i++)
        {
            p *= 10;
            p += str[i] - '0';
        }
        File.Close();
        //显示文件内容
        //删除buffer，避免内存泄漏
        delete[] str;
        str = NULL;
    }

    //初始化DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    //创建套接字
    SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    //素数p的最大原根a
    ll a = pri_root(p);
    srand((unsigned)time(NULL));
    ll Xb = rand() % p;
    ll Yb = q_pow(a, Xb, p);
    //向服务器发起请求
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(1234);
    connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    //接收服务器传回的数据
    char szBuffer[MAXBYTE] = {};
    recv(sock, szBuffer, MAXBYTE, 0);
    char ch[100] = {};
    itoa(Yb, ch, 10);
    char* str1 = ch;
    send(sock, str1, strlen(str1) + sizeof(char), 0);
    //输出接收到的数据
    int Ya = 0;
    for (int i = 0;szBuffer[i] != '\0';i++)
    {
        Ya *= 10;
        Ya += szBuffer[i] - '0';
    }
    CString szBuffer_str;
    szBuffer_str = szBuffer;
    GetDlgItem(IDC_EDIT1)->SetWindowText(szBuffer_str);
    ll Kb = q_pow(Ya, Xb, p);
    char Kb_char[100];
    itoa(Kb, Kb_char, 10);
    CString Kb_str = (_T("密钥为："));
    Kb_str += Kb_char;
    //关闭套接字
    closesocket(sock);

    //终止使用 DLL
    WSACleanup();

    MessageBox(Kb_str);
    return;
}
