#pragma once


// CDHEncryptionDialog 对话框

class CDHEncryptionDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CDHEncryptionDialog)

public:
	CDHEncryptionDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDHEncryptionDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG41 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	long long int Xa;
	long long int Ya;
	long long int p;
	long long int a;
	CString algorithm_str;
	CComboBox m_Combo1;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedEncryption();
};
