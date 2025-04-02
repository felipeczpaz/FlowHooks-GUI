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

#include <cstring>
#include "Input.hpp"

#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))

namespace FHGUI
{
	void Input::Init(HWND hWnd)
	{
		hWnd_ = hWnd;
	}

	void Input::Update()
	{
		std::memcpy(PrevPressedKeys_, PressedKeys_, sizeof(PrevPressedKeys_));

		bool OutOfFocus = GetForegroundWindow() != hWnd_;

		for (int i = 0; i < MAX_KEYS; ++i) {
			PressedKeys_[i] = OutOfFocus ? false : (GetAsyncKeyState(i) & 0xFFFF);
		}
	}

	bool Input::OnWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg) {
		case WM_MOUSEMOVE:
			MousePos_ = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
			return true;
		}

		return false;
	}
}