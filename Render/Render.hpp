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
#include <cstdint>
#include <d3d9.h>

#include "../Singleton.hpp"

#define COL2DWORD(x) (D3DCOLOR_ARGB(x.alpha, x.red, x.green, x.blue))

class CD3DFont;

namespace Render
{
	struct Color
	{
		std::uint8_t red, green, blue, alpha;
	};

	struct Size
	{
		int w, h;
	};

	void Init(LPDIRECT3DDEVICE9 Device);
	void OnLostDevice();
	void OnResetDevice();
	void Shutdown();
	void Line(int posx1, int posy1, int posx2, int posy2, Color color);
	void Rect(int posx, int posy, int width, int height, Color color);
	void FilledRect(int posx, int posy, int width, int height, Color color);
	void FilledRectGradient(int posx, int posy, int width, int height, Color color1, Color color2, bool horizontal = false);
	void String(int x, int y, Color color, const char* strText, CD3DFont* pFont, DWORD dwFlags = 0UL);
	Size GetTextSize(const char* strText, CD3DFont* pFont);
	void SetupRenderStates();

	extern LPDIRECT3DDEVICE9 Device_;
	extern CD3DFont* MenuFont;
}