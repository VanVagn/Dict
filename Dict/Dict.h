
// Dict.h: основной файл заголовка для приложения Dict
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CDictApp:
// Сведения о реализации этого класса: Dict.cpp
//

class CDictApp : public CWinApp
{
public:
	CDictApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDictApp theApp;
