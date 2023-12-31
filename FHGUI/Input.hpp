#pragma once
#include <Windows.h>

#include "Datatypes.hpp"
#include "../Singleton.hpp"

namespace FHGUI
{
	constexpr int MAX_KEYS = 255;

	class Input : public Singleton<Input>
	{
	public:
		void Init(HWND hWnd);
		void Update();
		bool OnWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		bool KeyPressed(int Key)
		{
			return PressedKeys_[Key] && !PrevPressedKeys_[Key];
		}

		bool KeyHeld(int Key)
		{
			return PrevPressedKeys_[Key] && PressedKeys_[Key];
		}

		Point CursorPos()
		{
			return MousePos_;
		}

		bool MouseInArea(int left, int top, int right, int bottom)
		{
			return MousePos_.x >= left && MousePos_.y >= top && MousePos_.x < left + right && MousePos_.y < top + bottom;
		}

		bool MouseInArea(const Rect& area)
		{
			return MouseInArea(area.x, area.y, area.w, area.h);
		}

	private:
		HWND hWnd_{ nullptr };
		Point MousePos_{ 0, 0 };
		bool PressedKeys_[MAX_KEYS]{ false }, PrevPressedKeys_[MAX_KEYS]{ false };
	};
}