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

	void Init();
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

	class Fonts : public Singleton<Fonts>
	{
	public:
		CD3DFont* MenuFont{ nullptr };
	};
}