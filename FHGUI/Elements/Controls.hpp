#pragma once
#include <string>

#include "../Datatypes.hpp"

namespace FHGUI
{
	class GroupBox;
	class Tab;
	class Window;

	class Control
	{
		friend GroupBox;
		friend Tab;
	public:
		Control(const char* strTitle, int PosX, int PosY, int Width, int Height)
			: Title_{ strTitle }, PosX_{ PosX }, PosY_{ PosY }, Width_{ Width }, Height_{ Height }
		{

		}

		void SetTooltip(const char* strTooltip);

		virtual void Render() = 0;
		virtual void Update() {};
		virtual void OnClick() {};
		virtual Rect AbsoluteArea();
		virtual Rect InputArea() { return AbsoluteArea(); };
		virtual void RenderTooltip();
	protected:
		std::string Title_{};
		std::string Tooltip_{};
		int PosX_{ 0 };
		int PosY_{ 0 };
		int Width_{ 0 };
		int Height_{ 0 };
		int TooltipHeight_{ 0 };
		Tab* Tab_{ nullptr };
		Window* Window_{ nullptr };
	};

	class GroupBox : public Control
	{
	public:
		GroupBox(const char* strTitle, int PosX, int PosY, int Width, int Height);

		virtual void Render() override;

		void RegisterControl(Control* pControl);
	private:
		int OffsetX_{ 5 }, OffsetY_{ 10 };
	};

	class CheckBox : public Control
	{
	public:
		CheckBox(const char* strTitle, bool* State, const char *strTooltip = "");

		virtual void Render() override;
		virtual void OnClick() override;
		virtual Rect InputArea() override;
	private:
		bool* Checked_{ nullptr };
		int TitleWidth_{ 0 };
	};
}