#pragma once
#include "resource.h"
#include "Decoder.h"


// �˴���ģ���а����ĺ�����ǰ������: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL				Init();
BOOL				InitD3D();
void				Clear();
void				Render();
void				OnPresent(VMR9PresentationInfo* info);
