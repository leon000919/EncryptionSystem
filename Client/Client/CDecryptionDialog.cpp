// CDecryptionDialog.cpp: 实现文件
//

#include "pch.h"
#include "Client.h"
#include "CDecryptionDialog.h"
#include "afxdialogex.h"
#include "caesar.cpp";
#include "keyword.cpp";
#include "affine.cpp";
#include "vigenere cipher.cpp";
#include "Multiliteral.cpp";
#include "autokey cipher.cpp"
#include "autokey plaint.cpp"
#include "playFair.cpp"
#include "permutation.cpp"
#include "columnPermutation.cpp"
#include "Double-Transposition.cpp"
#include "RC4.cpp"
#include "ca.cpp"
#include "RSA.cpp"
#include "DES.cpp"
#include <WinSock2.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll

// CDecryptionDialog 对话框

IMPLEMENT_DYNAMIC(CDecryptionDialog, CDialogEx)

CDecryptionDialog::CDecryptionDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DIALOG32, pParent)
{

}

CDecryptionDialog::~CDecryptionDialog()
{
}

void CDecryptionDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, text_str);
    DDX_Text(pDX, IDC_EDIT3, key_str);
    DDX_CBString(pDX, IDC_COMBO1, algorithm_str);
    DDX_Control(pDX, IDC_COMBO1, m_Combo1);
}


BEGIN_MESSAGE_MAP(CDecryptionDialog, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON1, &CDecryptionDialog::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_FileBUTTON1, &CDecryptionDialog::OnBnClickedFilebutton1)
    ON_BN_CLICKED(IDEncryption, &CDecryptionDialog::OnBnClickedEncryption)
END_MESSAGE_MAP()


// CDecryptionDialog 消息处理程序


void CDecryptionDialog::OnBnClickedButton1()
{
    // TODO: 在此添加控件通知处理程序代码
    CFile File;
    CFileException e;
    if (!File.Open(_T("../../Cryptography/Cryptography/readme.txt"), CFile::modeRead, &e))
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


BOOL CDecryptionDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_Combo1.SetCurSel(0);

    // TODO:  在此添加额外的初始化

    return TRUE;  // return TRUE unless you set the focus to a control
                  // 异常: OCX 属性页应返回 FALSE
}


void CDecryptionDialog::OnBnClickedFilebutton1()
{
    CFile File;
    CFileException e;
    if (!File.Open(_T("../../Cryptography/Cryptography/keyFromA.txt"), CFile::modeRead, &e))
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
        GetDlgItem(IDC_EDIT3)->SetWindowText(cstr);
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

    //向服务器发起请求
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(2333);
    connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    //接收服务器传回的数据
    char szBuffer[MAXBYTE] = {};
    recv(sock, szBuffer, MAXBYTE, 0);
    text_str = szBuffer;
    GetDlgItem(IDC_EDIT1)->SetWindowText(text_str);

    //关闭套接字
    closesocket(sock);

    //终止使用 DLL
    WSACleanup();
    return;
}

void CDecryptionDialog::OnBnClickedEncryption()
{
    GetDlgItem(IDC_EDIT1)->GetWindowText(text_str);
    GetDlgItem(IDC_EDIT3)->GetWindowText(key_str);
    GetDlgItem(IDC_COMBO1)->GetWindowText(algorithm_str);
    //在这里写各种密码的main函数
    USES_CONVERSION;
    char* t = T2A(text_str);//密文
    char* k = T2A(key_str);//密钥

    if (algorithm_str == "Caesar cipher")
    {
        result_str = CaesarDecryption(t, k);
    }
    if (algorithm_str == "Keyword cipher")
    {
        result_str = KeywordDecryption(t, k);
    }
    if (algorithm_str == "Affine cipher")
    {
        result_str = AffineDecryption(t, k);
    }
    if (algorithm_str == "Multiliteral cipher")
    {
        result_str = MultiliteralDecryption(t, k);
    }
    if (algorithm_str == "Vigenere cipher")
    {
        result_str = VigenereDecryption(t, k);
    }
    if (algorithm_str == "Autokey ciphertext")
    {
        result_str = AutokeyCiphertextDecryption(t, k);
    }
    if (algorithm_str == "Autokey plaintext")
    {
        result_str = AutokeyPlaintextDecryption(t, k);
    }
    if (algorithm_str == "Playfair cipher")
    {
        result_str = PlayfairDecryption(t, k);
    }
    if (algorithm_str == "Permutation cipher")
    {
        result_str = PermutationDecryption(t, k);
    }
    if (algorithm_str == "Column permutation")
    {
        result_str = ColumnPermutationDecryption(t, k);
    }
    if (algorithm_str == "Double-Transposition")
    {
        result_str = DoubleTranspositionDecryption(t, k);
    }
    if (algorithm_str == "RC4")
    {
        result_str = RC4Encryption(t, k);
    }
    if (algorithm_str == "RSA")
    {
        result_str = RSADecryption(t, k);
    }
    if (algorithm_str == "DES")
    {
        result_str = DESDecryption(t, k);
    }
    char str1[1000] = {};
    CString messageStr = (_T("明文为："));
    messageStr += result_str;
    MessageBox(messageStr);

    char* r = T2A(result_str);//密文
    return;
}
