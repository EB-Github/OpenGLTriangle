#include <Windows.h>
#pragma once
namespace GUI {
	class oGLWindow
	{
	public:
		oGLWindow(WNDPROC WndProc, HINSTANCE hInstance, int nCmdShow, TCHAR szWindowClass[], TCHAR szTitle[]);
		~oGLWindow();
		bool Refresh(MSG* msg);
	private:
		HWND hWnd = NULL;
		HDC hdc = NULL;
	};

};


