
// RenderFilterGDI.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRenderFilterGDIApp: 
// �йش����ʵ�֣������ RenderFilterGDI.cpp
//

class CRenderFilterGDIApp : public CWinApp
{
public:
	CRenderFilterGDIApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRenderFilterGDIApp theApp;