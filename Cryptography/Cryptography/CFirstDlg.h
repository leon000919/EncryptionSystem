#pragma once


// CFirstDlg 对话框

class CFirstDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFirstDlg)

public:
	CFirstDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFirstDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedEncryption();
	afx_msg void OnBnClickedFilebutton1();
	afx_msg void OnBnClickedFilebutton2();
	afx_msg void OnBnClickedDecryption();
	CString text_str;
	CString key_str;
	CString algorithm_str;
	virtual BOOL OnInitDialog();
	CComboBox m_Combo1;
	CComboBox m_Combo2;
	afx_msg void OnBnClickedButton1();
};
