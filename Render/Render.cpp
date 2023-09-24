#include "D3DFont.hpp"
#include "Render.hpp"

#include "../DirectX/DirectX.hpp"
#include "../Platform.hpp"

namespace Render
{
    struct Vertex
    {
        float x, y, z, rhw;
        DWORD color;
    };

    LPDIRECT3DDEVICE9 Device_{ nullptr };
    CD3DFont* MenuFont{ nullptr };

    void Render::Init(LPDIRECT3DDEVICE9 Device)
    {
        Device_ = Device;

        MenuFont = new CD3DFont(L"Arial", 8, FW_NORMAL);
        MenuFont->InitDeviceObjects(Device_);
        MenuFont->RestoreDeviceObjects();
    }

    void Render::Shutdown()
    {
        if (MenuFont) {
            MenuFont->InvalidateDeviceObjects();
            MenuFont->DeleteDeviceObjects();
            SAFE_DELETE(MenuFont);
        }
    }

    void Render::OnLostDevice()
    {
        if (MenuFont) {
            MenuFont->InvalidateDeviceObjects();
            MenuFont->DeleteDeviceObjects();
        }
    }

    void Render::OnResetDevice()
    {
        if (MenuFont) {
            MenuFont->InitDeviceObjects(Device_);
            MenuFont->RestoreDeviceObjects();
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

        Device_->SetTexture(0, nullptr);
        Device_->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
        Device_->DrawPrimitiveUP(D3DPT_LINELIST, 1, &vert, sizeof(Vertex));
        Device_->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);
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

        Device_->SetTexture(0, nullptr);
        Device_->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
        Device_->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, &vert, sizeof(Vertex));
        Device_->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);
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

        Device_->SetTexture(0, nullptr);
        Device_->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &vert, sizeof(Vertex));
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

        Device_->SetTexture(0, nullptr);
        Device_->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &vert, sizeof(Vertex));
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
        Device_->SetVertexShader(nullptr);
        Device_->SetPixelShader(nullptr);
        Device_->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
        Device_->SetRenderState(D3DRS_LIGHTING, FALSE);
        Device_->SetRenderState(D3DRS_FOGENABLE, FALSE);
        Device_->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        Device_->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

        Device_->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
        Device_->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
        Device_->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
        Device_->SetRenderState(D3DRS_STENCILENABLE, FALSE);

        Device_->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
        Device_->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);

        Device_->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
        Device_->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
        Device_->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
        Device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        Device_->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA);
        Device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
        Device_->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);

        Device_->SetRenderState(D3DRS_SRGBWRITEENABLE, FALSE);
        Device_->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN |
            D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);
    }
}