#pragma once


// CSecondDlg 对话框

class CSecondDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSecondDlg)

public:
	CSecondDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSecondDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedEncryption();
	long long int Xa;
	long long int Ya;
	long long int Xb;
	long long int Yb;
	CString algorithm_str;
	CComboBox m_Combo1;
	CComboBox m_Combo2;
	long long int p;
	long long int a;
	afx_msg void OnBnClickedDecryption();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
};
