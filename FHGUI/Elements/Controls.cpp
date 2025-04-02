/*
*************************************************************
*                                                           *
*   Flowhooks Software - Open Source License                *
*                                                           *
*  This software is licensed under the GNU Affero General   *
*  Public License v3. You may use, modify, and distribute   *
*  this code under the terms of the AGPLv3.                 *
*                                                           *
*  This program is distributed in the hope that it will be  *
*  useful, but WITHOUT ANY WARRANTY; without even the       *
*  implied warranty of MERCHANTABILITY or FITNESS FOR A     *
*  PARTICULAR PURPOSE. See the GNU AGPLv3 for more details. *
*                                                           *
*  Author: Felipe Cezar Paz (git@felipecezar.com)           *
*  File:                                                    *
*  Description: FlowHooks Graphical User Interface (FHGUI)  *
*                                                           *
*************************************************************
*/

#include <sstream>

#include "Controls.hpp"
#include "Window.hpp"

#include "../Input.hpp"

#include "../../Render/D3DFont.hpp"
#include "../../Render/Render.hpp"

namespace FHGUI
{
	Rect Control::AbsoluteArea()
	{
		Rect Area = { PosX_, PosY_, Width_, Height_ };

		if (Window_) {
			const Point& ControlPos = Window_->ControlPosition();
			Area.x += ControlPos.x;
			Area.y += ControlPos.y;
		}

		return Area;
	}

	constexpr int TOOLTIP_WIDTH = 220;

	void Control::SetTooltip(const char* strTooltip)
	{
		if (strTooltip[0] == '\0')
			return;

		TooltipHeight_ = Render::MenuFont->iHeight + 5;

		// 
		// https://en.wikipedia.org/wiki/Line_wrap_and_word_wrap
		// 

		constexpr int LineWidth = TOOLTIP_WIDTH - 10;
		static int SpaceWidth = Render::GetTextSize(" ", Render::MenuFont).w;

		int SpaceLeft = LineWidth;

		std::istringstream iss(strTooltip);
		std::string strWord;

		while (iss >> strWord) {
			int WordWidth = Render::GetTextSize(strWord.c_str(), Render::MenuFont).w;

			if (WordWidth + SpaceWidth > SpaceLeft) {
				strWord.insert(0, "\n");
				TooltipHeight_ += Render::MenuFont->iHeight;

				SpaceLeft = LineWidth - WordWidth;
			} else {
				SpaceLeft -= WordWidth + SpaceWidth;
			}

			Tooltip_.append(strWord);
			Tooltip_.append(" ");
		}
	}

	void Control::RenderTooltip()
	{
		if (Tooltip_.empty())
			return;

		const Point& CursorPos = FHGUI::Input::Get().CursorPos();
		const Rect TooltipArea = { CursorPos.x + 10, CursorPos.y + 10, TOOLTIP_WIDTH, TooltipHeight_ };

		Render::Rect(TooltipArea.x, TooltipArea.y, TooltipArea.w, TooltipArea.h, { 0, 0, 0, 220 });
		Render::FilledRect(TooltipArea.x + 1, TooltipArea.y + 1, TooltipArea.w - 2, TooltipArea.h - 2, { 32, 32, 32, 220 });

		Render::String(TooltipArea.x + 4, TooltipArea.y + 2, { 255, 255, 255, 255 }, Tooltip_.c_str(), Render::MenuFont);
	}

	GroupBox::GroupBox(const char* strTitle, int PosX, int PosY, int Width, int Height)
		: Control(strTitle, PosX, PosY, Width, Height, ControlTypes::GROUPBOX)
	{

	}

	void GroupBox::RegisterControl(Control* pControl)
	{
		if (Tab_) {
			Tab_->RegisterControl(pControl);
		}

		pControl->PosX_ += PosX_ + OffsetX_;
		pControl->PosY_ += PosY_ + OffsetY_;

		OffsetY_ += pControl->Height_ + 2;
	}

	void GroupBox::Render()
	{
		const Rect& Area = AbsoluteArea();

		Render::Rect(Area.x, Area.y, Area.w, Area.h, { 0, 0, 0, 255 });

		if (!Title_.empty()) {
			Render::String(Area.x + 5, Area.y, { 255, 255, 255, 255 }, Title_.c_str(), Render::MenuFont, CD3DFONT_CENTERED_Y);
		}
	}

	constexpr int CHECKBOX_SIZE = 14;

	CheckBox::CheckBox(const char* strTitle, bool* State, const char* strTooltip)
		: Control(strTitle, 0, 0, CHECKBOX_SIZE, CHECKBOX_SIZE, ControlTypes::CHECKBOX, strTooltip), Checked_{ State }
	{
		if (!Title_.empty()) {
			TitleWidth_ = Render::GetTextSize(Title_.c_str(), Render::MenuFont).w;
		}
	}

	void CheckBox::Render()
	{
		const Rect& Area = AbsoluteArea();

		Render::FilledRect(Area.x, Area.y, Area.w, Area.h, { 24, 24, 24, 255 });

		if (*Checked_) {
			Render::FilledRect(Area.x + 2, Area.y + 2, Area.w - 4, Area.h - 4, { 255, 146, 0, 255 });
		}

		if (!Title_.empty()) {
			Render::String(Area.x + Area.w + 2, Area.y + (Area.h / 2), { 255, 255, 255, 255 }, Title_.c_str(), Render::MenuFont, CD3DFONT_CENTERED_Y);
		}
	}

	void CheckBox::OnClick()
	{
		*Checked_ = !*Checked_;
	}

	Rect CheckBox::InputArea()
	{
		Rect Area = Control::AbsoluteArea();

		// Add title starting position and size for being able to interact with it
		Area.w += TitleWidth_ + 2;

		return Area;
	}

	constexpr int DROPDOWN_WIDTH = 80;
	constexpr int DROPDOWN_HEIGHT = 14;

	Dropdown::Dropdown(const char* strTitle, const std::vector<const char*>& Items, int* SelectedItem, const char* strTooltip)
		: Control(strTitle, 0, DROPDOWN_HEIGHT, DROPDOWN_WIDTH, DROPDOWN_HEIGHT, ControlTypes::DROPDOWN, strTooltip),
		Items_{ Items }, SelectedItem_{ SelectedItem }
	{

	}

	void Dropdown::Render()
	{
		const Rect& Area = AbsoluteArea();

		if (!Title_.empty()) {
			Render::String(Area.x, Area.y - DROPDOWN_HEIGHT, { 255, 255, 255, 255 }, Title_.c_str(), Render::MenuFont);
		}

		Render::Rect(Area.x, Area.y, Area.w, Area.h, { 0, 0, 0, 255 });
		Render::FilledRect(Area.x + 1, Area.y + 1, Area.w - 2, Area.h - 2, { 24, 24, 24, 255 });

		if (SelectedItem_) {
			const char* SelectedItemString = Items_[*SelectedItem_];
			Render::String(Area.x + 3, Area.y + (DROPDOWN_HEIGHT / 2), { 255, 255, 255, 255 }, SelectedItemString, Render::MenuFont, CD3DFONT_CENTERED_Y);
		}

		Render::Rect(Area.x + Area.w - 14, Area.y, 14, Area.h, { 0, 0, 0, 255 });
		Render::FilledRect(Area.x + Area.w - 13, Area.y + 1, 12, Area.h - 2, { 46, 46, 46, 255 });

		Render::Line(Area.x + Area.w - 10, Area.y + 7, Area.x + Area.w - 6, Area.y + 7, { 0, 0, 0, 255 });

		if (!IsOpen_) {
			Render::Line(Area.x + Area.w - 8, Area.y + 5, Area.x + Area.w - 8, Area.y + 9, { 0, 0, 0, 255 });
			return;
		}

		if (!Items_.empty() && SelectedItem_) {
			int AddOffsetY = 0;

			int VisibleItems = static_cast<int>(Items_.size()) - 1;
			Render::Rect(Area.x, Area.y + DROPDOWN_HEIGHT - 1, Area.w, (VisibleItems * DROPDOWN_HEIGHT) + 2, { 0, 0, 0, 255 });

			for (size_t i = 0; i < Items_.size(); ++i) {
				if (i == *SelectedItem_)
					continue;

				Rect ItemArea = { Area.x, Area.y + DROPDOWN_HEIGHT + AddOffsetY, Area.w, DROPDOWN_HEIGHT };

				if (FHGUI::Input::Get().MouseInArea(ItemArea)) {
					Render::FilledRect(ItemArea.x + 1, ItemArea.y, ItemArea.w - 2, ItemArea.h, { 255, 146, 0, 255 });
				} else {
					Render::FilledRect(ItemArea.x + 1, ItemArea.y, ItemArea.w - 2, ItemArea.h, { 24, 24, 24, 255 });
				}

				Render::String(ItemArea.x + 3, ItemArea.y + (ItemArea.h / 2), { 255, 255, 255, 255 }, Items_[i], Render::MenuFont, CD3DFONT_CENTERED_Y);

				AddOffsetY += ItemArea.h;
			}
		}
	}

	void Dropdown::OnClick()
	{
		if (IsOpen_) {
			const Rect& Area = AbsoluteArea();

			if (!Items_.empty() && SelectedItem_) {
				int AddOffsetY = 0;

				for (size_t i = 0; i < Items_.size(); ++i) {
					if (i == *SelectedItem_)
						continue;

					Rect ItemArea = { Area.x, Area.y + DROPDOWN_HEIGHT + AddOffsetY, Area.w, DROPDOWN_HEIGHT };
					if (Input::Get().MouseInArea(ItemArea)) {
						*SelectedItem_ = static_cast<int>(i);
					}

					AddOffsetY += ItemArea.h;
				}
			}

			IsOpen_ = false;
		} else {
			IsOpen_ = true;
		}
	}

	Rect Dropdown::InputArea()
	{
		Rect Area = Control::AbsoluteArea();

		int VisibleItems = static_cast<int>(Items_.size()) - 1;
		Area.h += (VisibleItems * DROPDOWN_HEIGHT) + 2;

		return Area;
	}
}