#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include "GUI/oGLWindow.h"
#include <glad/wgl.h>
#include <glad/gl.h>
using namespace std;
HINSTANCE hInst;
LRESULT CALLBACK WndProc(
	_In_ HWND   hWnd,
	_In_ UINT   message,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
) {
	//Create the Window
	static TCHAR szWindowClass[] = _T("OpenGLTriangle");
	static TCHAR szTitle[] = _T("An OpenGL Learning Project");
	static const GLfloat clear_color[] = { 0.0f, 0.0f, 1.0f, 1.0f };

	hInst = hInstance;

	GUI::oGLWindow oGLWnd = GUI::oGLWindow(WndProc, hInstance, nCmdShow, szWindowClass, szTitle);

	//The loop
	bool quit = false;
	MSG msg;
	while (!quit) {
		quit = oGLWnd.Refresh(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	HDC hdc;

	switch (message)
	{
	case WM_DESTROY:
	case WM_QUIT:
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}