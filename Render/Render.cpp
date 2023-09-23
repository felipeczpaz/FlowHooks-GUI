#include "D3DFont.hpp"
#include "Render.hpp"

#include "../DirectX/DirectX.hpp"

struct Vertex
{
    float x, y, z, rhw;
    DWORD color;
};

void Render::Init()
{
    Fonts::Get().MenuFont = new CD3DFont(L"Arial", 8, FW_NORMAL);
    Fonts::Get().MenuFont->InitDeviceObjects(DirectX::Get().Device());
    Fonts::Get().MenuFont->RestoreDeviceObjects();
}

void Render::Shutdown()
{
    if (Fonts::Get().MenuFont) {
        Fonts::Get().MenuFont->InvalidateDeviceObjects();
        Fonts::Get().MenuFont->DeleteDeviceObjects();
        delete Fonts::Get().MenuFont;
    }
}

void Render::OnLostDevice()
{
    if (Fonts::Get().MenuFont) {
        Fonts::Get().MenuFont->InvalidateDeviceObjects();
        Fonts::Get().MenuFont->DeleteDeviceObjects();
    }
}

void Render::OnResetDevice()
{
    if (Fonts::Get().MenuFont) {
        Fonts::Get().MenuFont->InitDeviceObjects(DirectX::Get().Device());
        Fonts::Get().MenuFont->RestoreDeviceObjects();
    }
}

void Render::Line(int posx1, int posy1, int posx2, int posy2, Color color)
{
    D3DCOLOR dwColor = COL2DWORD(color);
    Vertex vert[2] =
    {
        { float(posx1), float(posy1), 0.0f, 1.0f, dwColor },
        { float(posx2), float(posy2), 0.0f, 1.0f, dwColor }
    };

    DirectX::Get().Device()->SetTexture(0, nullptr);
    DirectX::Get().Device()->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
    DirectX::Get().Device()->DrawPrimitiveUP(D3DPT_LINELIST, 1, &vert, sizeof(Vertex));
    DirectX::Get().Device()->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);
}

void Render::Rect(int posx, int posy, int width, int height, Color color)
{
    D3DCOLOR dwColor = COL2DWORD(color);

    /* DIFFERENT WITH/WITHOUT MULTISAMPLING */
    width -= 1; height -= 1;

    Vertex vert[5] =
    {
        { float(posx), float(posy), 1.0f, 1.0f, dwColor },
        { float(posx + width), float(posy), 1.0f, 1.0f, dwColor },
        { float(posx + width), float(posy + height), 1.0f, 1.0f, dwColor },
        { float(posx), float(posy + height), 1.0f, 1.0f, dwColor },
        { float(posx), float(posy), 1.0f, 1.0f, dwColor }
    };

    DirectX::Get().Device()->SetTexture(0, nullptr);
    DirectX::Get().Device()->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
    DirectX::Get().Device()->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, &vert, sizeof(Vertex));
    DirectX::Get().Device()->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);
}

void Render::FilledRect(int posx, int posy, int width, int height, Color color)
{
    D3DCOLOR dwColor = COL2DWORD(color);

    Vertex vert[4] =
    {
        { float(posx), float(posy), 0.0f, 1.0f, dwColor },
        { float(posx + width), float(posy), 0.0f, 1.0f, dwColor },
        { float(posx), float(posy + height), 0.0f, 1.0f, dwColor },
        { float(posx + width), float(posy + height), 0.0f, 1.0f, dwColor }
    };

    DirectX::Get().Device()->SetTexture(0, nullptr);
    DirectX::Get().Device()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &vert, sizeof(Vertex));
}

void Render::FilledRectGradient(int posx, int posy, int width, int height, Color color1, Color color2, bool horizontal)
{
    D3DCOLOR dwColor1 = COL2DWORD(color1);
    D3DCOLOR dwColor2 = COL2DWORD(color2);

    Vertex vert[4] =
    {
        { float(posx), float(posy), 0.0f, 1.0f, dwColor1 },
        { float(posx + width), float(posy), 0.0f, 1.0f, horizontal ? dwColor2 : dwColor1 },
        { float(posx), float(posy + height), 0.0f, 1.0f, horizontal ? dwColor1 : dwColor2 },
        { float(posx + width), float(posy + height), 0.0f, 1.0f, dwColor2 }
    };

    DirectX::Get().Device()->SetTexture(0, nullptr);
    DirectX::Get().Device()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &vert, sizeof(Vertex));
}

void Render::String(int x, int y, Color color, const char* strText, CD3DFont* pFont, DWORD dwFlags)
{
    D3DCOLOR dwColor = COL2DWORD(color);
    pFont->DrawString(x, y, dwColor, strText, dwFlags);
}

Render::Size Render::GetTextSize(const char* strText, CD3DFont* pFont)
{
    SIZE sz{};
    pFont->GetTextExtent(strText, &sz);

    return { sz.cx, sz.cy };
}

void Render::SetupRenderStates()
{
    DirectX::Get().Device()->SetVertexShader(nullptr);
    DirectX::Get().Device()->SetPixelShader(nullptr);
    DirectX::Get().Device()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
    DirectX::Get().Device()->SetRenderState(D3DRS_LIGHTING, FALSE);
    DirectX::Get().Device()->SetRenderState(D3DRS_FOGENABLE, FALSE);
    DirectX::Get().Device()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    DirectX::Get().Device()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

    DirectX::Get().Device()->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    DirectX::Get().Device()->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
    DirectX::Get().Device()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
    DirectX::Get().Device()->SetRenderState(D3DRS_STENCILENABLE, FALSE);

    DirectX::Get().Device()->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
    DirectX::Get().Device()->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);

    DirectX::Get().Device()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    DirectX::Get().Device()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
    DirectX::Get().Device()->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
    DirectX::Get().Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    DirectX::Get().Device()->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA);
    DirectX::Get().Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    DirectX::Get().Device()->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);

    DirectX::Get().Device()->SetRenderState(D3DRS_SRGBWRITEENABLE, FALSE);
    DirectX::Get().Device()->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN |
        D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);
}
