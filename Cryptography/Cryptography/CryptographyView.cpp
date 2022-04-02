
// CryptographyView.cpp: CCryptographyView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Cryptography.h"
#endif

#include "CryptographyDoc.h"
#include "CryptographyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCryptographyView

IMPLEMENT_DYNCREATE(CCryptographyView, CView)

BEGIN_MESSAGE_MAP(CCryptographyView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CCryptographyView 构造/析构

CCryptographyView::CCryptographyView() noexcept
{
	// TODO: 在此处添加构造代码

}

CCryptographyView::~CCryptographyView()
{
}

BOOL CCryptographyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCryptographyView 绘图

void CCryptographyView::OnDraw(CDC* /*pDC*/)
{
	CCryptographyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CCryptographyView 打印

BOOL CCryptographyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCryptographyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCryptographyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CCryptographyView 诊断

#ifdef _DEBUG
void CCryptographyView::AssertValid() const
{
	CView::AssertValid();
}

void CCryptographyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCryptographyDoc* CCryptographyView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCryptographyDoc)));
	return (CCryptographyDoc*)m_pDocument;
}
#endif //_DEBUG


// CCryptographyView 消息处理程序
