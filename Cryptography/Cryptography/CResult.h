#pragma once


// CResult 对话框

class CResult : public CDialogEx
{
	DECLARE_DYNAMIC(CResult)

public:
	CResult(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CResult();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG11 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString result_str;
	CString static_str;
	virtual BOOL OnInitDialog();
	
	afx_msg void OnBnClickedSave();
};
