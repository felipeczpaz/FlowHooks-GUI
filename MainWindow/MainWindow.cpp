#include "MainWindow.hpp"
#include "../DirectX/DirectX.hpp"
#include "../FHGUI/Input.hpp"

LRESULT CALLBACK WndProc(HWND hWnd_, UINT uMsg, WPARAM wParam, LPARAM lParam);

bool MainWindow::Init(const wchar_t* strClassName, const wchar_t* strWindowName, int Width, int Height)
{
	memset(&WndClass_, 0, sizeof(WndClass_));
	WndClass_.cbSize = sizeof(WndClass_);
	WndClass_.style = CS_CLASSDC;
	WndClass_.lpfnWndProc = WndProc;
	WndClass_.hInstance = GetModuleHandle(nullptr);
	WndClass_.hCursor = LoadCursor(nullptr, IDC_ARROW);
	WndClass_.lpszClassName = strClassName;
	RegisterClassEx(&WndClass_);

	hWnd_ = CreateWindow(WndClass_.lpszClassName, strWindowName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, Width, Height, nullptr, nullptr, WndClass_.hInstance, nullptr);
	if (!hWnd_) return false;

	return true;
}

void MainWindow::Shutdown()
{
	DestroyWindow(hWnd_);
	UnregisterClass(WndClass_.lpszClassName, WndClass_.hInstance);
}

void MainWindow::Display()
{
	ShowWindow(hWnd_, SW_SHOWDEFAULT);
	UpdateWindow(hWnd_);
}

bool MainWindow::RunLoop()
{
	MSG msg{ 0 };
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		return true;
	}

	return false;
}

LRESULT CALLBACK WndProc(HWND hWnd_, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_SIZE:
		if (wParam == SIZE_MINIMIZED)
			return 0;

		DirectX::Get().OnSize(lParam);
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU)
			return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	if (FHGUI::Input::Get().OnWindowProc(hWnd_, uMsg, wParam, lParam))
		return 0;

	return DefWindowProc(hWnd_, uMsg, wParam, lParam);
}