// CResult.cpp: 实现文件
//

#include "pch.h"
#include "Cryptography.h"
#include "CResult.h"
#include "afxdialogex.h"


// CResult 对话框

IMPLEMENT_DYNAMIC(CResult, CDialogEx)

CResult::CResult(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG11, pParent)
{

}

CResult::~CResult()
{
}

void CResult::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}


BEGIN_MESSAGE_MAP(CResult, CDialogEx)
	ON_BN_CLICKED(IDSave, &CResult::OnBnClickedSave)
END_MESSAGE_MAP()


// CResult 消息处理程序


BOOL CResult::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	UpdateData(FALSE);
	GetDlgItem(IDC_STATIC)->SetWindowText(static_str);
	GetDlgItem(IDC_EDIT5)->SetWindowText(result_str);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CResult::OnBnClickedSave()
{
	// TODO: 在此添加控件通知处理程序代码
    CFile File;
    CFileException e;
    CString filter;
    filter = "文本文件(*.txt)|*.txt|C++文件(*.h,*.cpp)|*.h;*.cpp||";
    CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY, filter);
    if (IDOK == dlg.DoModal())
    {
        CFile File(dlg.GetPathName(), CFile::modeCreate | CFile::modeReadWrite);

        USES_CONVERSION;
        char* str = W2A(result_str);
        //写入
        File.Write(str, strlen(str));
        //刷新
        File.Flush();
        //关闭
        File.Close();
        //删除buffer，避免内存泄漏
        //delete[] str;
        str = NULL;
    }
}
