// CDHEncryptionDialog.cpp: 实现文件
//

#include "pch.h"
#include "Cryptography.h"
#include "CDHEncryptionDialog.h"
#include "afxdialogex.h"
#include "RSA.cpp"
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll

// CDHEncryptionDialog 对话框

IMPLEMENT_DYNAMIC(CDHEncryptionDialog, CDialogEx)

CDHEncryptionDialog::CDHEncryptionDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG41, pParent)
{

}

CDHEncryptionDialog::~CDHEncryptionDialog()
{
}

void CDHEncryptionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_CBString(pDX, IDC_COMBO1, algorithm_str);
    DDX_Control(pDX, IDC_COMBO1, m_Combo1);
}


BEGIN_MESSAGE_MAP(CDHEncryptionDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDHEncryptionDialog::OnBnClickedButton1)
    ON_BN_CLICKED(IDEncryption, &CDHEncryptionDialog::OnBnClickedEncryption)
END_MESSAGE_MAP()


// CDHEncryptionDialog 消息处理程序


BOOL CDHEncryptionDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Combo1.SetCurSel(0);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDHEncryptionDialog::OnBnClickedButton1()
{
    // TODO: 在此添加控件通知处理程序代码
    CFile File;
    CFileException e;
    if (!File.Open(_T("readmeDH.txt"), CFile::modeRead, &e))
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

void CDHEncryptionDialog::OnBnClickedEncryption()
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
        char Ya_str[100] = {};
        itoa(Ya, Ya_str, 10);
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
        sockAddr.sin_port = htons(1234);  //端口
        //p写入文件
        FILE* fp;
        fp = fopen("DHkeyFromA.txt", "w");
        fprintf(fp, "%lld", p);
        fclose(fp);
        bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
        //进入监听状态
        listen(servSock, 2);
        //接收客户端请求
        SOCKADDR clntAddr;
        int nSize = sizeof(SOCKADDR);
        SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
        //向客户端发送数据
        send(clntSock, Ya_str, strlen(Ya_str) + sizeof(char), 0);

        char szBuffer[MAXBYTE] = {};
        recv(clntSock, szBuffer, MAXBYTE, 0);
        //关闭套接字
        int Yb = 0;
        for (int i = 0;szBuffer[i] != '\0';i++)
        {
            Yb *= 10;
            Yb += szBuffer[i] - '0';
        }
        CString szBuffer_str;
        szBuffer_str = szBuffer;
        GetDlgItem(IDC_EDIT3)->SetWindowText(szBuffer_str);
        closesocket(clntSock);
        closesocket(servSock);

        //终止 DLL 的使用
        WSACleanup();
        ll Ka = q_pow(Yb, Xa, p);
        char Ka_char[100];
        itoa(Ka, Ka_char, 10);
        CString Ka_str = (_T("密钥为："));
        Ka_str += Ka_char;
        MessageBox(Ka_str);
        return;
    }
}
