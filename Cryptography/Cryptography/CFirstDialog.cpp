// CFirstDlg.cpp: 实现文件
//

#include "pch.h"
#include "Cryptography.h"
#include "CFirstDlg.h"
#include "afxdialogex.h"
#include "CResult.h"
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
#include "md5.cpp"

// CFirstDlg 对话框

IMPLEMENT_DYNAMIC(CFirstDlg, CDialogEx)

CFirstDlg::CFirstDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
    , algorithm_str(_T(""))
{

}

CFirstDlg::~CFirstDlg()
{
}

void CFirstDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, text_str);
    DDX_Text(pDX, IDC_EDIT2, text_str);
    DDX_Text(pDX, IDC_EDIT3, key_str);
    DDX_Text(pDX, IDC_EDIT4, key_str);
    DDX_CBString(pDX, IDC_COMBO1, algorithm_str);
    DDX_CBString(pDX, IDC_COMBO2, algorithm_str);
    DDX_Control(pDX, IDC_COMBO1, m_Combo1);
    DDX_Control(pDX, IDC_COMBO2, m_Combo2);
}


BEGIN_MESSAGE_MAP(CFirstDlg, CDialogEx)
	ON_BN_CLICKED(IDEncryption, &CFirstDlg::OnBnClickedEncryption)
    ON_BN_CLICKED(IDDecryption, &CFirstDlg::OnBnClickedDecryption)
	ON_BN_CLICKED(IDC_FileBUTTON1, &CFirstDlg::OnBnClickedFilebutton1)
    ON_BN_CLICKED(IDC_FileBUTTON2, &CFirstDlg::OnBnClickedFilebutton2)
    ON_BN_CLICKED(IDC_BUTTON1, &CFirstDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

// CFirstDlg 消息处理程序


void CFirstDlg::OnBnClickedEncryption()
{
	// TODO: 在此添加控件通知处理程序代码
    CResult dlg;
    GetDlgItem(IDC_EDIT1)->GetWindowText(text_str);
    GetDlgItem(IDC_EDIT3)->GetWindowText(key_str);
    GetDlgItem(IDC_COMBO1)->GetWindowText(algorithm_str);
    dlg.static_str = L"密文为：";
    //在这里写各种密码的main函数
    USES_CONVERSION;
    char* t = T2A(text_str);//明文
    char* k = T2A(key_str);//密钥

    if (algorithm_str == "Caesar cipher")
    {
        dlg.result_str = CaesarEncryption(t, k);
    }
    if (algorithm_str == "Keyword cipher")
    {
        dlg.result_str = KeywordEncryption(t, k);
    }
    if (algorithm_str == "Affine cipher")
    {
        dlg.result_str = AffineEncryption(t, k);
    }
    if (algorithm_str == "Multiliteral cipher")
    {
        dlg.result_str = MultiliteralEncryption(t, k);
    }
    if (algorithm_str == "Vigenere cipher")
    {
        dlg.result_str = VigenereEncryption(t, k);
    }
    if (algorithm_str == "Autokey ciphertext")
    {
        dlg.result_str = AutokeyCiphertextEncryption(t, k);
    }
    if (algorithm_str == "Autokey plaintext")
    {
        dlg.result_str = AutokeyPlaintextEncryption(t, k);
    }
    if (algorithm_str == "Playfair cipher")
    {
        dlg.result_str = PlayfairEncryption(t, k);
    }
    if (algorithm_str == "Permutation cipher")
    {
        dlg.result_str = PermutationEncryption(t, k);
    }
    if (algorithm_str == "Column permutation")
    {
        dlg.result_str = ColumnPermutationEncryption(t, k);
    }
    if (algorithm_str == "Double-Transposition")
    {
        dlg.result_str = DoubleTranspositionEncryption(t, k);
    }
    if (algorithm_str == "RC4")
    {
        dlg.result_str = RC4Encryption(t, k);
    }
    if (algorithm_str == "CA")
    {
        dlg.result_str = CAEncryption(t, k);
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
        GetDlgItem(IDC_EDIT4)->SetWindowText(key2_text);
        return;
    }
    if (algorithm_str == "RSA")
    {
        dlg.result_str = RSAEncryption(t, k);
    }
    if (algorithm_str == "DES")
    {
        dlg.result_str = DESEncryption(t, k);
    }
    if (algorithm_str == "MD5")
    {
        dlg.result_str = MD5Encryption(t);
    }

    dlg.DoModal();     
}

void CFirstDlg::OnBnClickedDecryption()
{
    // TODO: 在此添加控件通知处理程序代码
    CResult dlg;
    GetDlgItem(IDC_EDIT2)->GetWindowText(text_str);
    GetDlgItem(IDC_EDIT4)->GetWindowText(key_str);
    GetDlgItem(IDC_COMBO2)->GetWindowText(algorithm_str);
    dlg.static_str = L"明文为：";
    //在这里写各种密码的main函数
    USES_CONVERSION;
    char* t = T2A(text_str);//密文
    char* k = T2A(key_str);//密钥

    if (algorithm_str == "Caesar cipher")
    {
        dlg.result_str = CaesarDecryption(t, k);
    }
    if (algorithm_str == "Keyword cipher")
    {
        dlg.result_str = KeywordDecryption(t, k);
    }
    if (algorithm_str == "Affine cipher")
    {
        dlg.result_str = AffineDecryption(t, k);
    }
    if (algorithm_str == "Multiliteral cipher")
    {
        dlg.result_str = MultiliteralDecryption(t, k);
    }
    if (algorithm_str == "Vigenere cipher")
    {
        dlg.result_str = VigenereDecryption(t, k);
    }
    if (algorithm_str == "Autokey ciphertext")
    {
        dlg.result_str = AutokeyCiphertextDecryption(t, k);
    }
    if (algorithm_str == "Autokey plaintext")
    {
        dlg.result_str = AutokeyPlaintextDecryption(t, k);
    }
    if (algorithm_str == "Playfair cipher")
    {
        dlg.result_str = PlayfairDecryption(t, k);
    }
    if (algorithm_str == "Permutation cipher")
    {
        dlg.result_str = PermutationDecryption(t, k);
    }
    if (algorithm_str == "Column permutation")
    {
        dlg.result_str = ColumnPermutationDecryption(t, k);
    }
    if (algorithm_str == "Double-Transposition")
    {
        dlg.result_str = DoubleTranspositionDecryption(t, k);
    }
    if (algorithm_str == "CA")
    {
        //dlg.result_str = CADecryption(t, k);
    }
    if (algorithm_str == "RSA")
    {
        dlg.result_str = RSADecryption(t, k);
    }
    if (algorithm_str == "RC4")
    {
        dlg.result_str = RC4Encryption(t, k);
    }
    if (algorithm_str == "DES")
    {
        dlg.result_str = DESDecryption(t, k);
    }

    dlg.DoModal();
}

void CFirstDlg::OnBnClickedFilebutton1()
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
            free(str);
            str = NULL;
        }
    }
}


void CFirstDlg::OnBnClickedFilebutton2()
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
            SetDlgItemText(IDC_EDIT2, cstr);
            File.Close();
            //显示文件内容
            //删除buffer，避免内存泄漏
            free(str);
            str = NULL;
        }
    }
}


BOOL CFirstDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_Combo1.SetCurSel(0);
    m_Combo2.SetCurSel(0);

    // TODO:  在此添加额外的初始化

    return TRUE;  // return TRUE unless you set the focus to a control
                  // 异常: OCX 属性页应返回 FALSE
}


void CFirstDlg::OnBnClickedButton1()
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
