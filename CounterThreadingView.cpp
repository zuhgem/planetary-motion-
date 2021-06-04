
// CounterThreadingView.cpp : implementation of the CCounterThreadingView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CounterThreading.h"
#endif

#include "CounterThreadingDoc.h"
#include "CounterThreadingView.h"
#include "TestThread.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCounterThreadingView

IMPLEMENT_DYNCREATE(CCounterThreadingView, CView)

BEGIN_MESSAGE_MAP(CCounterThreadingView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_THREAD_START, &CCounterThreadingView::OnThreadStart)
	ON_COMMAND(ID_THREAD_PAUSE, &CCounterThreadingView::OnThreadPause)
	ON_COMMAND(ID_THREAD_RESUME, &CCounterThreadingView::OnThreadResume)
END_MESSAGE_MAP()

// CCounterThreadingView construction/destruction

CCounterThreadingView::CCounterThreadingView()
	
{
	
	m_iCounter = 0;
	theta = 0, a = 244, b = 244, c = 130, d = 130;
    k = 6.14 / 180;
	x = 0, y = 0;
	//x1 = 0, x2 = 0, x3 = 0, x4 = 0;
}

CCounterThreadingView::~CCounterThreadingView()
{
}

BOOL CCounterThreadingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCounterThreadingView drawing

void CCounterThreadingView::OnDraw(CDC* pDC)
{
	CCounterThreadingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	//m_iCounter++;
	


	CPen redpen;
	redpen.CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	CPen* pOldpen = pDC->SelectObject(&redpen);
	pDC->Ellipse(110, 110, 600, 600);
	pDC->SelectObject(pOldpen);

	//outer orbit rotation

	for (int i = 0; i <=m_iCounter; i++)
	{
		theta = i;
		x = a * cos(k*theta);

		y = b * sin(k*theta);

	}
	for (int i = 0; i <=m_iCounter; i++)
	{
		
		CBrush brushblue(RGB(0, 0, 255));
		CBrush *pOldBrush = pDC->SelectObject(&brushblue);
        pDC->Ellipse(355 + x + 20, 350 + y + 20, 350 + x - 20, 350 + y - 20);
	     Invalidate();
		pDC->SelectObject(pOldBrush);


	}
	CPen redpen1;
	redpen1.CreatePen(PS_SOLID, 5, RGB(0, 128, 0));
	CPen* pOldpen1 = pDC->SelectObject(&redpen1);
	pDC->Ellipse(220, 220, 480, 480);
	pDC->SelectObject(pOldpen1);


	//sun

	CBrush brushred(RGB(255, 0, 0));
	CBrush *pOldbrush = pDC->SelectObject(&brushred);
	pDC->Ellipse(305, 305, 400, 400);
	pDC->SelectObject(pOldbrush);


	//inner orbit rotation

	for (int i = 0; i <= m_iCounter; i++)
	{
		theta = i;
		x = c * cos(k*theta);
        y = d * sin(k*theta);

	}
	for (int i = 0; i <= m_iCounter; i++)
	{
		CBrush brushblue(RGB(255, 0, 0));
		CBrush *pOldBrush = pDC->SelectObject(&brushblue);
		pDC->Ellipse(350 + x + 20, 350 + y + 20, 350 + x - 20, 350 + y - 20);
        Invalidate();
		pDC->SelectObject(pOldBrush);
	}
}


// CCounterThreadingView printing

BOOL CCounterThreadingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCounterThreadingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCounterThreadingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CCounterThreadingView diagnostics

#ifdef _DEBUG
void CCounterThreadingView::AssertValid() const
{
	CView::AssertValid();
}

void CCounterThreadingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCounterThreadingDoc* CCounterThreadingView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCounterThreadingDoc)));
	return (CCounterThreadingDoc*)m_pDocument;
}
#endif //_DEBUG


// CCounterThreadingView message handlers


void CCounterThreadingView::OnThreadStart()
{
	pThread = AfxBeginThread(CTestThread::RunThreadFunction, this);
}


void CCounterThreadingView::OnThreadPause()
{
	pThread -> SuspendThread();
}


void CCounterThreadingView::OnThreadResume()
{
	pThread->ResumeThread();
}
