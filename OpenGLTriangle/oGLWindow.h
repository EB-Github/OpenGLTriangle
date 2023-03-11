#include <Windows.h>
#pragma once
class oGLWindow
{
	public: 
		oGLWindow(WNDPROC WndProc, HINSTANCE hInstance, int nCmdShow, TCHAR szWindowClass[], TCHAR szTitle[]);
		~oGLWindow();
	private:
		HWND hWnd = NULL;
};

