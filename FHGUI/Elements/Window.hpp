#pragma once
#include <string>
#include <vector>

#include "../Datatypes.hpp"

namespace FHGUI
{
	class Tab
	{
	public:
		Tab(const std::string& strTitle);

		void Render(const Rect& Area, bool Selected, bool FirstTab);
		void Update();

		int GetTitleWidth()
		{
			return TitleWidth_;
		}
	private:
		std::string Title_{};
		int TitleWidth_;
	};

	class Window
	{
		friend class Instance;
	public:
		Window(const std::string& strTitle, int PosX, int PosY, int Width, int Height)
			: Title_{ strTitle }, PosX_{ PosX }, PosY_{ PosY }, Width_{ Width }, Height_{ Height }
		{

		}

		~Window()
		{
			for (std::size_t i = 0; i < Tabs_.size(); ++i) {
				Tab* pTab = Tabs_[i];
				if (pTab) {
					delete pTab;
				}
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

			Tabs_.emplace_back(pTab);
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