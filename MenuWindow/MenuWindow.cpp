#include "MenuWindow.hpp"

#include "../FHGUI/FHGUI.hpp"
#include "../FHGUI/Elements/Window.hpp"

namespace MenuWindow
{
	void Init()
	{
		FHGUI::Window* Window = new FHGUI::Window("FlowHooks", 25, 25, 516, 608);

		FHGUI::Tab* AimbotTab = new FHGUI::Tab("Aimbot");
		Window->RegisterTab(AimbotTab);

		FHGUI::Tab* VisualsTab = new FHGUI::Tab("Visuals");
		Window->RegisterTab(VisualsTab);

		FHGUI::Tab* MiscTab = new FHGUI::Tab("Misc");
		Window->RegisterTab(MiscTab);

		FHGUI::Tab* SteamAPITab = new FHGUI::Tab("SteamAPI");
		Window->RegisterTab(SteamAPITab);

		FHGUI::Tab* ConfigTab = new FHGUI::Tab("Config");
		Window->RegisterTab(ConfigTab);

		FHGUI::Instance::Get().RegisterWindow(Window);

		FHGUI::Window* PlayerListWindow = new FHGUI::Window("Player List", 566, 50, 616, 548);
		FHGUI::Instance::Get().RegisterWindow(PlayerListWindow);
	}
}