#pragma once
#include <string>
#include <vector>

#include "../Datatypes.hpp"
#include "../../Platform.hpp"

namespace FHGUI
{
	class Control;
	class Instance;
	class Window;

	class Tab
	{
		friend Window;
	public:
		Tab(const std::string& strTitle);
		~Tab();

		void Render(const Rect& Area, bool Selected, bool FirstTab);
		void Update();

		int GetTitleWidth()
		{
			return TitleWidth_;
		}

		void RegisterControl(Control* pControl);
	private:
		std::string Title_{};
		int TitleWidth_{ 0 };
		Window* Window_{ nullptr };
		std::vector<Control*> Controls_{};
	};

	class Window
	{
		friend Control;
		friend Instance;
	public:
		Window(const std::string& strTitle, int PosX, int PosY, int Width, int Height)
			: Title_{ strTitle }, PosX_{ PosX }, PosY_{ PosY }, Width_{ Width }, Height_{ Height }
		{

		}

		~Window()
		{
			for (std::size_t i = 0; i < Tabs_.size(); ++i) {
				Tab* pTab = Tabs_[i];
				SAFE_DELETE(pTab);
			}
		}

		void Render();
		void Update();

		void SetTitle(const std::string& strTitle)
		{
			Title_ = strTitle;
		}

		void RegisterTab(Tab* pTab)
		{
			if (!SelectedTab_) {
				SelectedTab_ = pTab;
			}

			pTab->Window_ = this;
			Tabs_.emplace_back(pTab);
		}

		Rect ClientArea()
		{
			return { PosX_ + 9, PosY_ + 19, Width_ - 18, Height_ - 28 };
		}

		Point ControlPosition()
		{
			return { PosX_ + 13, PosY_ + 56 };
		}

	private:
		std::string Title_{};
		int PosX_{ 0 };
		int PosY_{ 0 };
		int Width_{ 0 };
		int Height_{ 0 };
		std::vector<Tab*> Tabs_{};
		Tab* SelectedTab_{ nullptr };
		float LastInputTime_{ 0.0f };
	};
}