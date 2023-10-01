#include "DirectX/DirectX.hpp"
#include "FHGUI/FHGUI.hpp"
#include "FHGUI/Input.hpp"
#include "MainWindow/MainWindow.hpp"
#include "Menu/Menu.hpp"
#include "Render/Render.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!MainWindow::Get().Init(L"FlowHooks", L"FlowHooks GUI Showcase", 1280, 600)) {
		MessageBoxW(nullptr, L"Failed to create Window!", L"FHGUI", MB_OK | MB_ICONERROR);
		return 1;
	}

	if (!DirectX::Get().Init(MainWindow::Get().Hwnd())) {
		MessageBoxW(nullptr, L"Failed to create DirectX Device!", L"FHGUI", MB_OK | MB_ICONERROR);
		return 1;
	}

	Render::Init(DirectX::Get().Device());

	FHGUI::Input::Get().Init(MainWindow::Get().Hwnd());
	Menu::Init();

	MainWindow::Get().Display();

	while (MainWindow::Get().RunLoop()) {
		if (DirectX::Get().BeginRender()) {
			FHGUI::Instance::Get().Update();
			FHGUI::Instance::Get().Render();

			DirectX::Get().EndRender();
		}
	}

	Render::Shutdown();
	DirectX::Get().Shutdown();
	MainWindow::Get().Shutdown();

	return 0;
}