#pragma once


// CDecryptionDialog 对话框

class CDecryptionDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CDecryptionDialog)

public:
	CDecryptionDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDecryptionDialog();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG32 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	CString text_str;
	CString key_str;
	CString algorithm_str;
	CString result_str;
	CComboBox m_Combo1;
	afx_msg void OnBnClickedFilebutton1();
	afx_msg void OnBnClickedEncryption();
};
