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

#include "DirectX.hpp"
#include "../Render/Render.hpp"
#include "../Platform.hpp"

bool DirectX::Init(HWND hWnd)
{
    pD3D_ = Direct3DCreate9(D3D_SDK_VERSION);
    if (!pD3D_) return false;

    std::memset(&D3DPP_, 0, sizeof(D3DPP_));
    D3DPP_.Windowed = TRUE;
    D3DPP_.SwapEffect = D3DSWAPEFFECT_DISCARD;
    D3DPP_.BackBufferFormat = D3DFMT_UNKNOWN;
    D3DPP_.EnableAutoDepthStencil = TRUE;
    D3DPP_.AutoDepthStencilFormat = D3DFMT_D16;
    D3DPP_.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    if (FAILED(pD3D_->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &D3DPP_, &pDevice_)))
        return false;

    return true;
}

void DirectX::Shutdown()
{
    SAFE_RELEASE(pDevice_);
    SAFE_RELEASE(pD3D_);
}

void DirectX::ResetDevice()
{
    Render::OnLostDevice();

    pDevice_->Reset(&D3DPP_);

    Render::OnResetDevice();
}

void DirectX::OnSize(LPARAM lParam)
{
    D3DPP_.BackBufferWidth = (UINT)LOWORD(lParam);
    D3DPP_.BackBufferHeight = (UINT)HIWORD(lParam);
    ResetDevice();
}

bool DirectX::BeginRender()
{
    pDevice_->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_RGBA(40, 40, 40, 255), 1.0f, 0);
    
    if (FAILED(pDevice_->BeginScene()))
        return false;

    Render::SetupRenderStates();
    return true;
}

void DirectX::EndRender()
{
    pDevice_->EndScene();

    HRESULT hResult = pDevice_->Present(nullptr, nullptr, nullptr, nullptr);

    if (hResult == D3DERR_DEVICELOST && pDevice_->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
        ResetDevice();
    }
}