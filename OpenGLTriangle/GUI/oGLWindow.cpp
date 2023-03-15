
#include "oGLWindow.h"
#include <tchar.h>
#include <glad/wgl.h>
#include <glad/gl.h>
#include "../Graphics/GLGraphics.h"
#include "../Graphics/GLShaders.h"
using namespace GUI;
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
	ATOM wndClass = RegisterClassEx(&wcex);
	if (!wndClass) {
		MessageBoxW(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);
		return;
	}


	hWnd = CreateWindow(
		MAKEINTATOM(wndClass),
		szTitle,	//Title bar text
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		800, //Width
		600, //Length
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hWnd == NULL) {
		return;
	}

	//get device context
	hdc = GetDC(hWnd);
	if (hdc == NULL) {
		DestroyWindow(hWnd);
		return;
	}

	PIXELFORMATDESCRIPTOR pfd;
	pfd.nSize = sizeof(pfd);
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.dwFlags = PFD_DOUBLEBUFFER | //double buffering
				  PFD_SUPPORT_OPENGL |  //opengl support
				  PFD_DRAW_TO_WINDOW; //Drawing to window
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;
	int format = ChoosePixelFormat(hdc, &pfd);
	if (format = 0 || SetPixelFormat(hdc, format, &pfd) == FALSE) {
		ReleaseDC(hWnd, hdc);
		DestroyWindow(hWnd);
		return;
	}

	HGLRC temp_context = NULL;


	if (NULL == (temp_context = wglCreateContext(hdc))) {
		ReleaseDC(hWnd, hdc);
		DestroyWindow(hWnd);
		return;
	}

	wglMakeCurrent(hdc, temp_context);

	gladLoaderLoadWGL(hdc);

	int attributes[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 2,
		WGL_CONTEXT_FLAGS_ARB,
		WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		0
	};

	HGLRC opengl_context = NULL;

	if (NULL == (opengl_context = wglCreateContextAttribsARB(hdc, NULL, attributes))) {
		wglDeleteContext(temp_context);
		ReleaseDC(hWnd, hdc);
		DestroyWindow(hWnd);
		return;
	}
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(temp_context);
	wglMakeCurrent(hdc, opengl_context);

	if (!gladLoaderLoadGL()) {
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(opengl_context);
		ReleaseDC(hWnd, hdc);
		DestroyWindow(hWnd);
		return;
	}

	vec = math::Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	gph = GLGraphics(vec);
	GLuint programID = GLShaders::LoadShaders("Graphics/Shaders/test.vert", "Graphics/Shaders/test.frag");
	m_GLSL = programID;
	//gph.setWindow(getWindowSize());
	//Display the window
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
}

oGLWindow::~oGLWindow()
{
	DestroyWindow(hWnd);
}

bool GUI::oGLWindow::Refresh(MSG* msg)
{
	MSG msgRef = *msg;
	const GLfloat clear_color[] = { 0.0f,  0.0f,  0.0f,  0.0f };
	while (PeekMessage(&msgRef, hWnd, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msgRef);
		DispatchMessage(&msgRef);

		if (msgRef.message == WM_QUIT || (msgRef.message == WM_KEYDOWN && msgRef.wParam == VK_ESCAPE)) {
			return true;
		}


	}
	gph.setVertexArrays();
	gph.Clear();
	glUseProgram(m_GLSL);
	gph.setVertexBuffers();
	gph.drawTriangle();
	gph.cleanUp();

	SwapBuffers(hdc);
	return false;
}

math::Rectangle GUI::oGLWindow::getWindowSize()
{
	RECT rc = {};
	GetClientRect(hWnd, &rc);
	return math::Rectangle(rc.left, rc.right, rc.left, rc.top);
}
