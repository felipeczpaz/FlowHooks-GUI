#include "Window.hpp"
#include "../Input.hpp"

#include "../../Render/D3DFont.hpp"
#include "../../Render/Render.hpp"

namespace FHGUI
{
	constexpr int TAB_HEIGHT = 20;

	void Window::Render()
	{
		Render::Rect(PosX_, PosY_, Width_, Height_, { 0, 0, 0, 255 });
		Render::FilledRectGradient(PosX_ + 1, PosY_ + 1, Width_ - 2, 16, { 40, 40, 40, 255 }, { 12, 12, 12, 255 });
		Render::FilledRect(PosX_ + 1, PosY_ + 17, Width_ - 2, Height_ - 18, { 12, 12, 12, 255 });
		Render::Rect(PosX_ + 8, PosY_ + 18, Width_ - 16, Height_ - 26, { 0, 0, 0, 255 });
		Render::FilledRect(PosX_ + 9, PosY_ + 19, Width_ - 18, Height_ - 28, { 46, 46, 46, 255 });

		if (!Title_.empty()) {
			Render::String(PosX_ + (Width_ / 2), PosY_ + 10, { 255, 255, 255, 255 }, Title_.c_str(), Render::MenuFont, CD3DFONT_CENTERED_X | CD3DFONT_CENTERED_Y);
		}

		if (!Tabs_.empty()) {
			int ClientPosX = PosX_ + 9;
			int ClientPosY = PosY_ + 19;

			int ClientWidth = Width_ - 18;

			Render::FilledRect(ClientPosX, ClientPosY, ClientWidth, TAB_HEIGHT, { 57, 57, 57, 255 });
			Render::Line(ClientPosX, ClientPosY + TAB_HEIGHT, ClientPosX + ClientWidth, ClientPosY + TAB_HEIGHT, { 0, 0, 0, 255 });

			int OffsetX = 0;

			for (std::size_t i = 0; i < Tabs_.size(); ++i) {
				Tab* pTab = Tabs_[i];
				if (!pTab)
					continue;

				int TabWidth = pTab->GetTitleWidth() + 15;

				Rect TabArea = { ClientPosX + OffsetX, ClientPosY, TabWidth, TAB_HEIGHT };
				pTab->Render(TabArea, pTab == SelectedTab_, i == 0);

				OffsetX += TabArea.w;
			}
		}
	}

	void Window::Update()
	{
		bool LeftClick = Input::Get().KeyPressed(VK_LBUTTON);
		if (!LeftClick)
			return;

		if (!Tabs_.empty()) {
			int ClientPosX = PosX_ + 9;
			int ClientPosY = PosY_ + 19;

			int OffsetX = 0;

			for (std::size_t i = 0; i < Tabs_.size(); ++i) {
				Tab* pTab = Tabs_[i];
				if (!pTab)
					continue;

				int TabWidth = pTab->GetTitleWidth() + 15;

				Rect TabArea = { ClientPosX + OffsetX, ClientPosY, TabWidth, TAB_HEIGHT };
				if (Input::Get().MouseInArea(TabArea.x, TabArea.y, TabArea.w, TabArea.h)) {
					SelectedTab_ = pTab;
				}

				OffsetX += TabArea.w;
			}
		}
	}

	Tab::Tab(const std::string& strTitle) : Title_{ strTitle }
	{
		TitleWidth_ = Render::GetTextSize(Title_.c_str(), Render::MenuFont).w;
	}

	void Tab::Render(const Rect& Area, bool Selected, bool FirstTab)
	{
		if (Selected) {
			Render::Rect(Area.x, Area.y, Area.w, Area.h, { 0, 0, 0, 255 });

			int PosX = FirstTab ? Area.x : (Area.x + 1);
			int Width = FirstTab ? (Area.w - 1) : (Area.w - 2);

			Render::FilledRect(PosX, Area.y + 1, Width, Area.h, { 46, 46, 46, 255 });
			Render::FilledRect(PosX, Area.y + 1, Width, 2, { 255, 146, 0, 255 });
		}
		else {
			Render::FilledRect(Area.x, Area.y, Area.w, Area.h, { 24, 24, 24, 255 });
		}

		if (!Title_.empty()) {
			Render::String(Area.x + (Area.w / 2), Area.y + (Area.h / 2), { 255, 255, 255, 255 }, Title_.c_str(), Render::MenuFont, CD3DFONT_CENTERED_X | CD3DFONT_CENTERED_Y);
		}

		if (!Selected)
			return;
	}

	void Tab::Update()
	{

	}
}