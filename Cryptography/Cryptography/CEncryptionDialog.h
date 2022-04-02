#pragma once


// CEncryptionDialog 对话框

class CEncryptionDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CEncryptionDialog)

public:
	CEncryptionDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CEncryptionDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG31 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CString text_str;
	CString key_str;
	CString algorithm_str;
	CString result_str;
	CComboBox m_Combo1;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedFilebutton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedEncryption();

	afx_msg void OnBnClickedButton1();
};
