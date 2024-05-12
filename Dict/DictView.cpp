
// DictView.cpp: реализация класса CDictView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Dict.h"
#endif

#include "DictDoc.h"
#include "DictView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDictView

IMPLEMENT_DYNCREATE(CDictView, CFormView)

BEGIN_MESSAGE_MAP(CDictView, CFormView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_Add, &CDictView::OnAdd)
	ON_BN_CLICKED(IDC_Find, &CDictView::OnFind)
	ON_BN_CLICKED(IDC_Del, &CDictView::OnDel)
	ON_COMMAND(ID_Near, &CDictView::OnNear)
	ON_COMMAND(ID_Next, &CDictView::OnNext)
	ON_COMMAND(ID_Prev, &CDictView::OnPrev)
	ON_UPDATE_COMMAND_UI(ID_Next, &CDictView::OnUpdateNext)
	ON_UPDATE_COMMAND_UI(ID_Prev, &CDictView::OnUpdatePrev)
END_MESSAGE_MAP()

// Создание или уничтожение CDictView

CDictView::CDictView() noexcept
	: CFormView(IDD_DICT_FORM)
	, m_strTermin(_T(""))
	, m_strTranslate(_T(""))
{
	// TODO: добавьте код создания

}

CDictView::~CDictView()
{
}

void CDictView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Termin, m_strTermin);
	DDX_Text(pDX, IDC_Translate, m_strTranslate);
	DDX_Control(pDX, IDC_LDict, m_ctrlDict);
}

BOOL CDictView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CDictView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_ctrlDict.ResetContent();
	CString strKey, strValue;
	CMapStringToString& map = GetDocument()->m_Dict;
	POSITION pos = map.GetStartPosition();

	while (pos != NULL)
	{
		map.GetNextAssoc(pos, strKey, strValue);
		CString s = strKey + _T(" <-> ") + strValue;
		m_ctrlDict.AddString(s);
	}
	pos = map.GetStartPosition();
	if (pos != NULL)
	{
		map.GetNextAssoc(pos, m_strTermin, m_strTranslate);
	}
	else
	{
		m_strTermin = _T("");
		m_strTranslate = _T("");
	}
	UpdateData(FALSE);
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// Печать CDictView

BOOL CDictView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CDictView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CDictView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CDictView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте свой код печати
}


// Диагностика CDictView

#ifdef _DEBUG
void CDictView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDictView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CDictDoc* CDictView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDictDoc)));
	return (CDictDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CDictView


void CDictView::OnAdd()
{
	if (!UpdateData())
		return;
	int nIndex = FindKeylnList(m_strTermin);
	if (nIndex |= LB_ERR)
		m_ctrlDict.DeleteString(nIndex);
	CString s = m_strTermin + _T(" <-> ") + m_strTranslate;
	m_ctrlDict.AddString(s);
	m_ctrlDict.SetCurSel(nIndex);
	GetDocument()->m_Dict[m_strTermin] = m_strTranslate;
	GetDocument()->SetModifiedFlag();
}


void CDictView::OnFind()
{
	if (!UpdateData())
		return;
	CString strValue;
	if (GetDocument()->m_Dict.Lookup(m_strTermin, m_strTranslate) != TRUE)
		m_strTranslate = _T(" : - в словаре нет термина ") + m_strTermin;
	else
		FindKeylnList(m_strTermin);
	UpdateData(FALSE);
}


void CDictView::OnDel()
{
	if (!UpdateData())
		return;
	CString strValue;
	if (GetDocument()->m_Dict.Lookup(m_strTermin, m_strTranslate) != TRUE)
		m_strTranslate = _T(" : - B cлoвape нem ygaленнoгo mepmuna ") + m_strTermin;
	else
	{
		int nIndex = FindKeylnList(m_strTermin);
		m_ctrlDict.DeleteString(nIndex);
		GetDocument()->m_Dict.RemoveKey(m_strTermin);
	}
	UpdateData(FALSE);
	GetDocument()->SetModifiedFlag();
}



int CDictView::FindKeylnList(CString& strKey)
{
	CString strValue;
	if (GetDocument()->m_Dict.Lookup(strKey, strValue) != TRUE)
		return LB_ERR;
	CString s = strKey + " <-> " + strValue;
	int Index = -1;
	CString s1 = _T("");
	do
	{
		Index = m_ctrlDict.FindStringExact(Index, s);
		m_ctrlDict.GetText(Index, s1);
		if (s = s1)
			break;

	} while (TRUE);
	m_ctrlDict.SetTopIndex(Index);
	m_ctrlDict.SetCurSel(Index);
	return Index;
}








void CDictView::OnNext()
{
	int Index = m_ctrlDict.GetCurSel();
	m_ctrlDict.SetCurSel(Index + 1);
	m_ctrlDict.SetTopIndex(Index + 1);
	CString s = _T("");
	m_ctrlDict.GetText(Index + 1, s);
	Index = s.Find(_T(" <-> "));
	m_strTermin = s.Left(Index);
	m_strTranslate = s.Mid(Index + 5);
	UpdateData(FALSE);
}
void CDictView::OnUpdateNext(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_ctrlDict.GetCurSel() != (m_ctrlDict.GetCount() - 1));
}

void CDictView::OnPrev()
{
	int Index = m_ctrlDict.GetCurSel();
	m_ctrlDict.SetCurSel(Index - 1);
	m_ctrlDict.SetTopIndex(Index - 1);
	CString s = _T(" ");
	m_ctrlDict.GetText(Index - 1, s);
	Index = s.Find(_T(" <-> "));
	m_strTermin = s.Left(Index);
	m_strTranslate = s.Mid(Index + 5);
	UpdateData(FALSE);
}

void CDictView::OnUpdatePrev(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_ctrlDict.GetCurSel() != 0);
}
void CDictView::OnNear()
{
	if (!UpdateData())
		return;
	CString Sub = m_strTermin.Left(1);
	int i = 1;
	int Index = -1;
	int Len = m_strTermin.GetLength();
	do
	{
		int Ind = m_ctrlDict.FindString(Index, Sub);
		if (Ind == LB_ERR)
			break;
		Index = Ind;
		Sub = m_strTermin.Left(++i);
	} while (i <= Len);
	if (Index != -1)
	{
		m_ctrlDict.SetTopIndex(Index);
		m_ctrlDict.SetCurSel(Index);
		m_strTranslate = _T("");
		UpdateData(FALSE);
	}
}