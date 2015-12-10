
// MFCTestView.cpp : CMFCTestView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCTestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CMFCTestView ����/����

CMFCTestView::CMFCTestView()
{
	// TODO: �ڴ˴���ӹ������

}

CMFCTestView::~CMFCTestView()
{
}

BOOL CMFCTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMFCTestView ����

void CMFCTestView::OnDraw(CDC* pDC)
{
	CMFCTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	//��Ongoing��CRect����ģ�
	//����ս�����ܷ���OnDraw��
	CRect rect;
	GetClientRect(&rect);

	//pDCָ��ָ��TextOutW����������֣������������������Ϳ�����ϸ��ǣ��޷���ʾ��
	pDC->TextOutW(200, 200, _T("Hello World!"));

	//����Ͱ���ʹ������һ������
	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 255));
	CBrush *oldBrush = pDC->SelectObject(&brush);
	pDC->Rectangle(1, 1, 200, 200);
	pDC->SelectObject(&oldBrush);

	//�������
	pDC->TextOutW(50, 50, _T("���ɶ��"));

	//���������˵ɶ�����б任
	CFont font;
	font.CreateFont(40, 20, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("����"));
	CFont *oldFont = pDC->SelectObject(&font);
	pDC->TextOutW(300, 300, _T("����զ�أ�"));
	pDC->SelectObject(&oldFont);
	pDC->TextOutW(400, 400, _T("�ٳ�һ�����ԣ�"));//��OK��ò��ûִ�У��ѽ���������ˣ�ֻ����500 500��ʱ�򳬳�����


	//���ʹ���
	CPen pen;
	pen.CreatePen(PS_DASH, 10, RGB(6, 6, 173));
	CPen *oldPen = pDC->SelectObject(&pen);
	pDC->MoveTo(100, 200);
	pDC->LineTo(700, 900);
	pDC->SelectObject(&oldPen);

	//����ս��
	CBitmap bmp;
	bmp.LoadBitmapW(IDB_ME);
	CImageList imgList;
	imgList.Create(50, 60, ILC_COLOR8 | ILC_MASK, 1, 0);
	imgList.Add(&bmp, RGB(0, 0, 0));
	imgList.Draw(pDC, 0, CPoint(200, 200), ILD_TRANSPARENT);
}


// CMFCTestView ��ӡ




void CMFCTestView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMFCTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMFCTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CMFCTestView ���

#ifdef _DEBUG
void CMFCTestView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCTestDoc* CMFCTestView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCTestDoc)));
	return (CMFCTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCTestView ��Ϣ�������


void CMFCTestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (nIDEvent == 1)
	{
		t++;
	}

	CDC *pDC = GetDC();//�粻ʹ��ȴ���ͷţ��򰾳��ڴ����


	//ÿ��ִ�У�ˢ�´��������Ӷ�ʵ��ǰ������ɵ����������¡�Ӱ�ۡ�
	CRect rect;
	GetClientRect(&rect);
	pDC->Rectangle(&rect);

	CString s;
	s.Format(_T("%d"), t);
	pDC->TextOutW(350, 450, s);

	//����ս��ͼƬ
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

	ReleaseDC(pDC);//�ͷŲ���Ҫ���ڴ�

	CView::OnTimer(nIDEvent);
}


int CMFCTestView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	SetTimer(1, 100, 0);
	t = 0;
	posUpDown = 0;
	posLeftRight = 0;
	return 0;
}


void CMFCTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
