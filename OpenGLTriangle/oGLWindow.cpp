#include "oGLWindow.h"
#include <tchar.h>

oGLWindow::oGLWindow(WNDPROC WndProc, HINSTANCE hInstance, int nCmdShow, TCHAR szWindowClass[], TCHAR szTitle[])
{
	//Set up the window structure
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	//Register the class
	if (!RegisterClassEx(&wcex)) {
		MessageBoxW(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);
		return;
	}


	hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		szWindowClass, //Name of the Application
		szTitle,	//Title bar text
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		500, //Width
		100, //Length
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hWnd == NULL) {
		return;
	}
	//Display the window
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
}

oGLWindow::~oGLWindow()
{
	DestroyWindow(hWnd);
}
