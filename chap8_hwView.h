
// chap8_hwView.h: Cchap8hwView 类的接口
//

#pragma once


class Cchap8hwView : public CView
{
public:
	BOOL operate, ready;//operate为按下左键标识，ready为绘制初始图形标识
	CPoint BeginP, EndP;
	CRect rect;
protected: // 仅从序列化创建
	Cchap8hwView() noexcept;
	DECLARE_DYNCREATE(Cchap8hwView)

// 特性
public:
	Cchap8hwDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~Cchap8hwView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // chap8_hwView.cpp 中的调试版本
inline Cchap8hwDoc* Cchap8hwView::GetDocument() const
   { return reinterpret_cast<Cchap8hwDoc*>(m_pDocument); }
#endif

