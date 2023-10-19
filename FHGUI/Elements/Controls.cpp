#include <sstream>

#include "Controls.hpp"
#include "Window.hpp"

#include "../Input.hpp"

#include "../../Render/D3DFont.hpp"
#include "../../Render/Render.hpp"

namespace FHGUI
{
	constexpr int TOOLTIP_WIDTH = 220;

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
			}
			else {
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
		Render::FilledRect(TooltipArea.x + 1, TooltipArea.y + 1, TooltipArea.w - 2, TooltipArea.h - 2, { 35, 35, 35, 220 });

		Render::String(TooltipArea.x + 4, TooltipArea.y + 2, { 255, 255, 255, 255 }, Tooltip_.c_str(), Render::MenuFont);
	}

	GroupBox::GroupBox(const char* strTitle, int PosX, int PosY, int Width, int Height)
		: Control(strTitle, PosX, PosY, Width, Height)
	{

	}

	void GroupBox::RegisterControl(Control* pControl)
	{
		if (Tab_) {
			Tab_->RegisterControl(pControl);
		}

		pControl->PosX_ += PosX_ + OffsetX_;
		pControl->PosY_ += PosY_ + OffsetY_;

		OffsetY_ += pControl->Height_;
	}

	void GroupBox::Render()
	{
		const Rect& Area = AbsoluteArea();

		Render::Rect(Area.x, Area.y, Area.w, Area.h, { 0, 0, 0, 255 });

		if (!Title_.empty()) {
			Render::String(Area.x + 5, Area.y, { 255, 255, 255, 255 }, Title_.c_str(), Render::MenuFont, CD3DFONT_CENTERED_Y);
		}
	}

	CheckBox::CheckBox(const char* strTitle, bool* State, const char* strTooltip)
		: Control(strTitle, 0, 0, 14, 14, strTooltip), Checked_{ State }
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
}