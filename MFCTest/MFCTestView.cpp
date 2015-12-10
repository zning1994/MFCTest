
// MFCTestView.cpp : CMFCTestView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCTest.h"
#endif

#include "MFCTestDoc.h"
#include "MFCTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCTestView

IMPLEMENT_DYNCREATE(CMFCTestView, CView)

BEGIN_MESSAGE_MAP(CMFCTestView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCTestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CMFCTestView 构造/析构

CMFCTestView::CMFCTestView()
{
	// TODO: 在此处添加构造代码

}

CMFCTestView::~CMFCTestView()
{
}

BOOL CMFCTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCTestView 绘制

void CMFCTestView::OnDraw(CDC* pDC)
{
	CMFCTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	//【Ongoing】CRect干嘛的？
	//绘制战机不能放在OnDraw中
	CRect rect;
	GetClientRect(&rect);

	//pDC指针指向TextOutW方法输出文字，本文字由于下面代码涂层在上覆盖，无法显示。
	pDC->TextOutW(200, 200, _T("Hello World!"));

	//油漆桶画笔工具填充一个矩形
	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 255));
	CBrush *oldBrush = pDC->SelectObject(&brush);
	pDC->Rectangle(1, 1, 200, 200);
	pDC->SelectObject(&oldBrush);

	//输出文字
	pDC->TextOutW(50, 50, _T("你瞅啥？"));

	//输出文字你说啥并进行变换
	CFont font;
	font.CreateFont(40, 20, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("楷体"));
	CFont *oldFont = pDC->SelectObject(&font);
	pDC->TextOutW(300, 300, _T("瞅你咋地？"));
	pDC->SelectObject(&oldFont);
	pDC->TextOutW(400, 400, _T("再瞅一个试试？"));//【OK】貌似没执行？已解决，出现了，只不过500 500的时候超出画布


	//画笔工具
	CPen pen;
	pen.CreatePen(PS_DASH, 10, RGB(6, 6, 173));
	CPen *oldPen = pDC->SelectObject(&pen);
	pDC->MoveTo(100, 200);
	pDC->LineTo(700, 900);
	pDC->SelectObject(&oldPen);

	//绘制战机
	CBitmap bmp;
	bmp.LoadBitmapW(IDB_ME);
	CImageList imgList;
	imgList.Create(50, 60, ILC_COLOR8 | ILC_MASK, 1, 0);
	imgList.Add(&bmp, RGB(0, 0, 0));
	imgList.Draw(pDC, 0, CPoint(200, 200), ILD_TRANSPARENT);
}


// CMFCTestView 打印




void CMFCTestView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMFCTestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCTestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCTestView 诊断

#ifdef _DEBUG
void CMFCTestView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCTestDoc* CMFCTestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCTestDoc)));
	return (CMFCTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCTestView 消息处理程序


void CMFCTestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (nIDEvent == 1)
	{
		t++;
	}

	CDC *pDC = GetDC();//如不使用却不释放，则熬成内存溢出


	//每次执行，刷新窗口区，从而实现前景物体飞但并不会留下“影痕”
	CRect rect;
	GetClientRect(&rect);
	pDC->Rectangle(&rect);

	CString s;
	s.Format(_T("%d"), t);
	pDC->TextOutW(350, 450, s);

	//插入战机图片
	CBitmap bmp;
	bmp.LoadBitmapW(IDB_ME);
	CImageList imgList;
	imgList.Create(50, 60, ILC_COLOR8 | ILC_MASK, 1, 0);
	imgList.Add(&bmp, RGB(0, 0, 0));
	imgList.Draw(pDC, 0, CPoint(200 + posLeftRight, 200 + posUpDown), ILD_TRANSPARENT);

	short key = GetKeyState(VK_RIGHT);
	if (key & 0x80 != 0)
	{
		posLeftRight += 5;
		key = 0;
	}

	ReleaseDC(pDC);//释放不需要的内存

	CView::OnTimer(nIDEvent);
}


int CMFCTestView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	SetTimer(1, 100, 0);
	t = 0;
	posUpDown = 0;
	posLeftRight = 0;
	return 0;
}


void CMFCTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nChar==VK_DOWN)
		posUpDown += 10;
	if (nChar == VK_UP)
		posUpDown -= 10;
	if (nChar == VK_LEFT)
		posLeftRight -= 10;
	if (nChar == VK_RIGHT)
		posLeftRight += 10;
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
