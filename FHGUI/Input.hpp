#pragma once
#include <Windows.h>

#include "Datatypes.hpp"
#include "../Singleton.hpp"

#define MAX_KEYS 255

namespace FHGUI
{
	class Input : public Singleton<Input>
	{
	public:
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

	private:
		Point MousePos_{ 0, 0 };
		bool PressedKeys_[MAX_KEYS], PrevPressedKeys_[MAX_KEYS];
	};
}