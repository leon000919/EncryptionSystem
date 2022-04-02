// CEncryptionDialog.cpp: 实现文件
//

#include "pch.h"
#include "Cryptography.h"
#include "CEncryptionDialog.h"
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
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll

// CEncryptionDialog 对话框

IMPLEMENT_DYNAMIC(CEncryptionDialog, CDialogEx)

CEncryptionDialog::CEncryptionDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG31, pParent)
{

}

CEncryptionDialog::~CEncryptionDialog()
{
}

void CEncryptionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, text_str);
    DDX_Text(pDX, IDC_EDIT3, key_str);
    DDX_CBString(pDX, IDC_COMBO1, algorithm_str);
    DDX_Control(pDX, IDC_COMBO1, m_Combo1);
}


BEGIN_MESSAGE_MAP(CEncryptionDialog, CDialogEx)
    ON_BN_CLICKED(IDC_FileBUTTON1, &CEncryptionDialog::OnBnClickedFilebutton1)
    ON_BN_CLICKED(IDEncryption, &CEncryptionDialog::OnBnClickedEncryption)
    ON_BN_CLICKED(IDC_BUTTON1, &CEncryptionDialog::OnBnClickedButton1)
END_MESSAGE_MAP()

// CEncryptionDialog 消息处理程序


void CEncryptionDialog::OnBnClickedFilebutton1()
{
    CFile File;
    CFileException e;
    CString filter;
    filter = "文本文件(*.txt)|*.txt|C++文件(*.h,*.cpp)|*.h;*.cpp||";
    CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter);
    if (IDOK == dlg.DoModal())
    {
        //构造文件，同时增加异常处理
        if (!File.Open(dlg.GetPathName(), CFile::modeRead, &e))
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
            SetDlgItemText(IDC_EDIT1, cstr);
            File.Close();
            //显示文件内容
            //删除buffer，避免内存泄漏
            delete[] str;
            str = NULL;
        }
    }
}


BOOL CEncryptionDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    m_Combo1.SetCurSel(0);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // 异常: OCX 属性页应返回 FALSE
}

void sendTo(char* str,char* ktext)
{
    //初始化 DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    //创建套接字
    SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    //绑定套接字
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = PF_INET;  //使用IPv4地址
    sockAddr.sin_addr.s_addr = INADDR_ANY;  //具体的IP地址
    sockAddr.sin_port = htons(2333);  //端口
    bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    //进入监听状态
    listen(servSock, 2);
    //密钥写入文件
    FILE* fp;
    fp = fopen("keyFromA.txt", "w");
    fprintf(fp, "%s", ktext);
    fclose(fp);
    //接收客户端请求
    SOCKADDR clntAddr;
    int nSize = sizeof(SOCKADDR);
    SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
    //向客户端发送数据
    send(clntSock, str, strlen(str) + sizeof(char), 0);
    closesocket(servSock);
    WSACleanup();

    return;
}
void CEncryptionDialog::OnBnClickedEncryption()
{
    // TODO: 在此添加控件通知处理程序代码
    GetDlgItem(IDC_EDIT1)->GetWindowText(text_str);
    GetDlgItem(IDC_EDIT3)->GetWindowText(key_str);
    GetDlgItem(IDC_COMBO1)->GetWindowText(algorithm_str);
    //在这里写各种密码的main函数
    USES_CONVERSION;
    char* t = T2A(text_str);//明文
    char* k = T2A(key_str);//密钥

    if (algorithm_str == "Caesar cipher")
    {
        result_str = CaesarEncryption(t, k);
    }
    if (algorithm_str == "Keyword cipher")
    {
        result_str = KeywordEncryption(t, k);
    }
    if (algorithm_str == "Affine cipher")
    {
        result_str = AffineEncryption(t, k);
    }
    if (algorithm_str == "Multiliteral cipher")
    {
        result_str = MultiliteralEncryption(t, k);
    }
    if (algorithm_str == "Vigenere cipher")
    {
        result_str = VigenereEncryption(t, k);
    }
    if (algorithm_str == "Autokey ciphertext")
    {
        result_str = AutokeyCiphertextEncryption(t, k);
    }
    if (algorithm_str == "Autokey plaintext")
    {
        result_str = AutokeyPlaintextEncryption(t, k);
    }
    if (algorithm_str == "Playfair cipher")
    {
        result_str = PlayfairEncryption(t, k);
    }
    if (algorithm_str == "Permutation cipher")
    {
        result_str = PermutationEncryption(t, k);
    }
    if (algorithm_str == "Column permutation")
    {
        result_str = ColumnPermutationEncryption(t, k);
    }
    if (algorithm_str == "Double-Transposition")
    {
        result_str = DoubleTranspositionEncryption(t, k);
    }
    if (algorithm_str == "RC4")
    {
        result_str = RC4Encryption(t, k);
    }
    if (algorithm_str == "CA")
    {
        result_str = CAEncryption(t, k);
    }
    if (algorithm_str == "RSAKeyGeneration")
    {
        char* etext;
        char* dtext;
        char* ntext;
        etext = strtok_s(RSAKeyGeneration(), ",", &ntext);
        dtext = strtok_s(NULL, ",", &ntext);
        CString key1_text = (_T(""));
        key1_text += etext;
        key1_text += ',';
        key1_text += ntext;
        CString key2_text = (_T(""));
        key2_text += dtext;
        key2_text += ',';
        key2_text += ntext;
        GetDlgItem(IDC_EDIT3)->SetWindowText(key1_text);
        FILE* fp;
        fp = fopen("keyFromA.txt", "r");
        fscanf(fp, "%s", &key2_text);
        fclose(fp);
        return;
    }
    if (algorithm_str == "RSA")
    {
        result_str = RSAEncryption(t, k);
    }
    if (algorithm_str == "DES")
    {
        result_str = DESEncryption(t, k);
    }
    char str1[1000] = {};
    CString messageStr = (_T("密文为："));
    messageStr += result_str;
    MessageBox(messageStr);

    char* r = T2A(result_str);//明文
    sendTo(r, k);
    return;
}


void CEncryptionDialog::OnBnClickedButton1()
{
    // TODO: 在此添加控件通知处理程序代码
    CFile File;
    CFileException e;
    if (!File.Open(_T("readme.txt"), CFile::modeRead, &e))
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
