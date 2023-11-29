#include "Menu.hpp"

#include "../FHGUI/FHGUI.hpp"
#include "../FHGUI/Elements/Controls.hpp"
#include "../FHGUI/Elements/Window.hpp"

void Menu::Init()
{
	FHGUI::Window* Window = new FHGUI::Window("FlowHooks", 25, 25, 516, 608);

	FHGUI::Tab* AimbotTab = new FHGUI::Tab("Aimbot");
	Window->RegisterTab(AimbotTab);
	{
		FHGUI::GroupBox* AimbotGroup = new FHGUI::GroupBox("Aimbot", 0, 0, 246, 228);
		AimbotTab->RegisterControl(AimbotGroup);
		{
			static bool bEnabled = false;
			static bool bAutoShoot = false;
			static int iSelection = 0;

			FHGUI::CheckBox* EnabledBox = new FHGUI::CheckBox("Enabled", &bEnabled, "Enable/Disable Aimbot.");
			AimbotGroup->RegisterControl(EnabledBox);

			FHGUI::CheckBox* AutoShootBox = new FHGUI::CheckBox("Auto Shoot", &bAutoShoot, "Enable/Disable Weapon Auto Fire.");
			AimbotGroup->RegisterControl(AutoShootBox);

			FHGUI::Dropdown* SelectionDropdown = new FHGUI::Dropdown("Selection", { "Field Of View", "Health", "Damage", "K/D Ratio" }, &iSelection, "Configure Target Selection.");
			AimbotGroup->RegisterControl(SelectionDropdown);
		}

		FHGUI::GroupBox* AccuracyGroup = new FHGUI::GroupBox("Accuracy", 251, 0, 239, 164);
		AimbotTab->RegisterControl(AccuracyGroup);
		{
			static bool bNoRecoil = false;

			FHGUI::CheckBox* NoRecoilBox = new FHGUI::CheckBox("No Recoil", &bNoRecoil, "Enable/Disable No Recoil.");
			AccuracyGroup->RegisterControl(NoRecoilBox);
		}
	}

	FHGUI::Tab* VisualTab = new FHGUI::Tab("Visual");
	Window->RegisterTab(VisualTab);

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