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

#pragma once
#include <Windows.h>
#include "../Singleton.hpp"

class MainWindow : public Singleton<MainWindow>
{
public:
	bool Init(const wchar_t* strClassName, const wchar_t* strWindowName, int Width, int Height);
	void Shutdown();
	void Display();
	bool RunLoop();

	HWND Hwnd()
	{
		return hWnd_;
	}
private:
	WNDCLASSEX WndClass_{ 0 };
	HWND hWnd_{ nullptr };
};