#include <Windows.h>
#include "../math/Rectangle.h"
#include "../math/Vector4.h"
#include "../Graphics/GLGraphics.h"
#pragma once
namespace GUI {
	class oGLWindow
	{
	public:
		oGLWindow(WNDPROC WndProc, HINSTANCE hInstance, int nCmdShow, TCHAR szWindowClass[], TCHAR szTitle[]);
		~oGLWindow();
		bool Refresh(MSG* msg);
		math::Rectangle getWindowSize();
	private:
		HWND hWnd = NULL;
		HDC hdc = NULL;
		GLGraphics gph = GLGraphics();
		math::Vector4 vec;
	};

};


