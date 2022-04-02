#pragma once


// CDHDecryptionDialog 对话框

class CDHDecryptionDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CDHDecryptionDialog)

public:
	CDHDecryptionDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDHDecryptionDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG42 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	CString key_str;
	CString algorithm_str;
	CString result_str;
	CComboBox m_Combo1;
	long long int p = 0;
	afx_msg void OnBnClickedEncryption();
};
