
// DictView.h: интерфейс класса CDictView
//

#pragma once


class CDictView : public CFormView
{
protected: // создать только из сериализации
	CDictView() noexcept;
	DECLARE_DYNCREATE(CDictView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_DICT_FORM };
#endif

// Атрибуты
public:
	CDictDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	virtual void OnInitialUpdate(); // вызывается в первый раз после конструктора
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CDictView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	CString m_strTermin;
	CString m_strTranslate;
	CListBox m_ctrlDict;
	afx_msg void OnAdd();
	afx_msg void OnFind();
	afx_msg void OnDel();
	int FindKeylnList(CString& strKey);
	
	afx_msg void OnNear();
	afx_msg void OnNext();
	afx_msg void OnPrev();
	afx_msg void OnUpdateNext(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePrev(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // версия отладки в DictView.cpp
inline CDictDoc* CDictView::GetDocument() const
   { return reinterpret_cast<CDictDoc*>(m_pDocument); }
#endif

