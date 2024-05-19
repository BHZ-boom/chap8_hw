
// chap8_hwView.cpp: Cchap8hwView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "chap8_hw.h"
#endif

#include "chap8_hwDoc.h"
#include "chap8_hwView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cchap8hwView

IMPLEMENT_DYNCREATE(Cchap8hwView, CView)

BEGIN_MESSAGE_MAP(Cchap8hwView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cchap8hwView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// Cchap8hwView 构造/析构

Cchap8hwView::Cchap8hwView() noexcept
{
	// TODO: 在此处添加构造代码
	operate = FALSE; 
	ready = TRUE; //operate为按下左键标识，ready为绘制初始图形标识
	rect = { 0,0,0,0 };
}

Cchap8hwView::~Cchap8hwView()
{
}

BOOL Cchap8hwView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// Cchap8hwView 绘图

void Cchap8hwView::OnDraw(CDC* pDC)
{
	Cchap8hwDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CRect rect2;
	GetClientRect(&rect2);
	CBrush brush(RGB(255, 255, 255));
	CBrush* pOldBrush = pDC->SelectObject(&brush);
	pDC->FillRect(&rect2, &brush);
	pDC->SelectObject(pOldBrush);
	if (ready == FALSE)//非初始状态,曾经按下了左键，绘制或大或小的灰色矩形
	{
		CBrush brush2(RGB(128, 128, 128));
		pDC->FillRect(&rect, &brush2);
		pDC->SelectObject(pOldBrush);
	}
	/*else //初始状态,或者用双击恢复到初始状态
	{
		//使用当前缺省画笔、画刷进行绘图
		pDC->Rectangle(rect.left, rect.top, rect.right, rect.bottom);
	}*/
}


// Cchap8hwView 打印


void Cchap8hwView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cchap8hwView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void Cchap8hwView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void Cchap8hwView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void Cchap8hwView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cchap8hwView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cchap8hwView 诊断

#ifdef _DEBUG
void Cchap8hwView::AssertValid() const
{
	CView::AssertValid();
}

void Cchap8hwView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cchap8hwDoc* Cchap8hwView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cchap8hwDoc)));
	return (Cchap8hwDoc*)m_pDocument;
}
#endif //_DEBUG


// Cchap8hwView 消息处理程序


void Cchap8hwView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if ((!operate) && ready)
	{
		operate = TRUE; //左键按下
		ready = FALSE; //不再是初始状态
		ClientToScreen(&point);
		GetCursorPos(&point);
		ScreenToClient(&point);
		//SetCapture(hWnd);//把所有的鼠标信息输入到被左键击活的窗口.
		//SetCursor(LoadCursor(NULL, IDC_CROSS)); //载入光标
		BeginP = point;
		
	}
	CView::OnLButtonDown(nFlags, point);
}


void Cchap8hwView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (operate) //左键按下后的移动
	{
		ClientToScreen(&point);
		GetCursorPos(&point);
		ScreenToClient(&point);
		EndP = point;
		rect.left = BeginP.x < EndP.x ? BeginP.x : EndP.x;
		rect.right = BeginP.x > EndP.x ? BeginP.x : EndP.x;
		rect.top = BeginP.y < EndP.y ? BeginP.y : EndP.y;
		rect.bottom = BeginP.y > EndP.y ? BeginP.y : EndP.y;
		SetCursor(LoadCursor(NULL, IDC_WAIT)); //载入沙漏光标
		InvalidateRect(NULL, TRUE);
	}
	CView::OnMouseMove(nFlags, point);
}


void Cchap8hwView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (operate) {
		operate = FALSE;//左键非按下状态
	}
	CView::OnLButtonUp(nFlags, point);
}


void Cchap8hwView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (ready == FALSE)//非初始状态，曾经绘制了灰色矩形
	{
		ready = TRUE;
		InvalidateRect(NULL, TRUE);
		//SetCursor(LoadCursor(NULL, IDC_ARROW));
		//ReleaseCapture(); //把鼠标从当前窗口中释放出来
	}
	CView::OnRButtonDown(nFlags, point);
}


void Cchap8hwView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	GetClientRect(&rect);//设置绘图区域为整个用户区
	InvalidateRect(&rect);
	CView::OnLButtonDblClk(nFlags, point);
}
