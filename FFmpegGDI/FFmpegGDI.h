
// FFmpegGDI.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFFmpegGDIApp: 
// �йش����ʵ�֣������ FFmpegGDI.cpp
//

class CFFmpegGDIApp : public CWinApp
{
public:
	CFFmpegGDIApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFFmpegGDIApp theApp;