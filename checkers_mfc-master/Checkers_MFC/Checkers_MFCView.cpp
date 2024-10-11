
// Checkers_MFCView.cpp: реализация класса CCheckersMFCView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Checkers_MFC.h"
#endif

#include "Checkers_MFCDoc.h"
#include "Checkers_MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCheckersMFCView

IMPLEMENT_DYNCREATE(CCheckersMFCView, CView)

BEGIN_MESSAGE_MAP(CCheckersMFCView, CView)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_NEW_GAME, &CCheckersMFCView::OnNewGame)
END_MESSAGE_MAP()

// Создание или уничтожение CCheckersMFCView

CCheckersMFCView::CCheckersMFCView()
{
	// TODO: добавьте код создания

}

CCheckersMFCView::~CCheckersMFCView()
{
}

BOOL CCheckersMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CCheckersMFCView

void CCheckersMFCView::OnDraw(CDC* pDC)
{
	CCheckersMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int nDCSave = pDC->SaveDC();
	

	CRect rcClient;
	GetClientRect(&rcClient);

	//CMemDC memDC(*pDC, this);
	//CDC* pTemp = &memDC.GetDC();
	/*Фон*/
	COLORREF clr; 

	/*Отрисовка доски*/
	for (int row = 0; row < pDoc->GetRows(); ++row) {
		for (int col = 0; col < pDoc->GetColumns(); ++col) {
			pDC->SelectStockObject(HOLLOW_BRUSH);
			CGameBoard::Status st = pDoc->GetCellStatus(row, col);
			switch (st) {
			case CGameBoard::Status::available_cell:
				clr = RGB(30, 144, 225);
				break;
			case CGameBoard::Status::white_empty:
				clr = RGB(255, 255, 255);
				break;
			default:
				clr = RGB(0, 0, 0);
				break;
			}

			/*Рисование клеток*/
			CRect rcBlock;
			rcBlock.top = row * pDoc->GetHeight();
			rcBlock.left = col * pDoc->GetWidth();
			rcBlock.right = rcBlock.left + pDoc->GetWidth();
			rcBlock.bottom = rcBlock.top + pDoc->GetHeight();

			pDC->FillSolidRect(&rcBlock, clr);

			pDC->Rectangle(&rcBlock);
			CBrush br;
			switch (st) {
			case CGameBoard::Status::white_cell:
			case CGameBoard::Status::white_queen:
				clr = RGB(224, 238, 224);
				br.CreateSolidBrush(clr);
				pDC->SelectObject(br);
				pDC->Ellipse(&rcBlock);
				break;
			case CGameBoard::Status::black_cell:
			case CGameBoard::Status::black_queen:
				clr = RGB(79, 79, 79);
				br.CreateSolidBrush(clr);
				pDC->SelectObject(br);
				pDC->Ellipse(&rcBlock);
				break;
			}
			br.DeleteObject();

			/*Отрисовка дамок*/
			switch (st) {
			case CGameBoard::Status::white_queen:
			case CGameBoard::Status::black_queen:
				clr = RGB(255, 0, 0);
				br.CreateSolidBrush(clr);
				pDC->SelectObject(br);
				rcBlock.top += static_cast<LONG>(pDoc->GetHeight()*0.1);
				rcBlock.left += static_cast<LONG>(pDoc->GetWidth()*0.1);
				rcBlock.right -= static_cast<LONG>(pDoc->GetWidth()*0.1);
				rcBlock.bottom -= static_cast<LONG>(pDoc->GetHeight()*0.1);
				pDC->Ellipse(&rcBlock);
			}
			br.DeleteObject();
		}
	}
	/*Восстановление контекста*/
	pDC->RestoreDC(nDCSave);
}


// Диагностика CCheckersMFCView

#ifdef _DEBUG
void CCheckersMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CCheckersMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCheckersMFCDoc* CCheckersMFCView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCheckersMFCDoc)));
	return (CCheckersMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CCheckersMFCView


void CCheckersMFCView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	/*Изменяем размер окна*/
	ResizeWindow();
}


void CCheckersMFCView::ResizeWindow()
{
	// Создаем указатель на Document
	CCheckersMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// Получаем размеры клиентской области
	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();

	// Изменяем размеры окна, исходя из размеров нашей доски
	rcWindow.right = rcWindow.left +
		pDoc->GetWidth() * pDoc->GetColumns() + nWidthDiff;
	rcWindow.bottom = rcWindow.top +
		pDoc->GetHeight() * pDoc->GetRows() + nHeightDiff;

	// Функция MoveWindow() изменяет размер окна фрейма
	GetParentFrame()->MoveWindow(&rcWindow);
}

void CCheckersMFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CCheckersMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// Получаем индекс строки и столбца элемента, по которому был осуществлен клик мышкой
	int row = point.y / pDoc->GetHeight();
	int col = point.x / pDoc->GetWidth();

	CGameBoard::Status st = pDoc->GetCellStatus(row, col);

	if (st != CGameBoard::Status::available_cell) {
		pDoc->ResetAvailable();
	}

	bool next_move = pDoc->GetMove();

	if (((st == CGameBoard::Status::black_cell || st == CGameBoard::Status::black_queen)&&!next_move)
		|| ((st == CGameBoard::Status::white_cell || st == CGameBoard::Status::white_queen)&&next_move)) {
		for (auto item : pDoc->getAvailableCellsList(row, col)) {
			pDoc->SetCell(item.first, item.second, CGameBoard::Status::available_cell);
		}
		pDoc->SetCurrCheckerCol(col);
		pDoc->SetCurrCheckerRow(row);
	}

	if (st == CGameBoard::Status::available_cell) {
		int active_row = pDoc->GetCurrCheckerRow(), active_col = pDoc->GetCurrCheckerCol();
		CGameBoard::Status st1 = pDoc->GetCellStatus(active_row, active_col);
		pDoc->BittMiddle(active_row, active_col, row, col);
		pDoc->SetCell(active_row, active_col, CGameBoard::Status::black_empty);
		pDoc->ResetAvailable();

		if (row == 0 && st1 == CGameBoard::Status::white_cell) {
			pDoc->SetCell(row, col, CGameBoard::Status::white_queen);
		}
		else if (row == 7 && st1 == CGameBoard::Status::black_cell) {
			pDoc->SetCell(row, col, CGameBoard::Status::black_queen);
		}
		else {
			pDoc->SetCell(row, col, st1);
		}
		pDoc->NextMove();
	}

	Invalidate();
	UpdateWindow();

	if (pDoc->IsGameOver()) {
		CString message;
		switch (pDoc->GetResult()) {
			case -1: message = "Победа чёрных!"; break;
			case 0: message = "Ничья!"; break;
			case 1: message = "Победа белых!"; break;
			default: message = "Исход партии не определён!";
		}
		// Отображаем пользователю результат игры
		MessageBox(message, _T("Игра окончена"), MB_OK | MB_ICONINFORMATION);
	}

	CView::OnLButtonDown(nFlags, point);
}


void CCheckersMFCView::OnNewGame()
{
	CCheckersMFCDoc* pDoc = GetDocument();
	pDoc->DeleteBoard();
	pDoc->SetupBoard();
	Invalidate();
	UpdateWindow();
}
