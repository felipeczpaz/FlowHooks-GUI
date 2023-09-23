#include "DirectX/DirectX.hpp"
#include "FHGUI/FHGUI.hpp"
#include "MainWindow/MainWindow.hpp"
#include "MenuWindow/MenuWindow.hpp"
#include "Render/Render.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!MainWindow::Get().Init(1280, 600)) {
		MessageBoxW(NULL, L"Failed to create Window!", L"FHGUI", MB_OK | MB_ICONERROR);
		return 1;
	}

	if (!DirectX::Get().Init(MainWindow::Get().Hwnd())) {
		MessageBoxW(NULL, L"Failed to create DirectX Device!", L"FHGUI", MB_OK | MB_ICONERROR);
		return 1;
	}

	Render::Init();

	MainWindow::Get().Display();

	MenuWindow::Init();

	while (MainWindow::Get().RunLoop()) {
		if (DirectX::Get().BeginRender()) {
			FHGUI::Instance::Get().Update();
			FHGUI::Instance::Get().Render();

			DirectX::Get().EndRender();
		}
	}

	return 0;
}