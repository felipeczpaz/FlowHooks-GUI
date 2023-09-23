#include "DirectX.hpp"
#include "../Render/Render.hpp"

bool DirectX::Init(HWND hWnd)
{
    D3D_ = Direct3DCreate9(D3D_SDK_VERSION);
    if (!D3D_) return false;

    ZeroMemory(&D3DPP_, sizeof(D3DPP_));
    D3DPP_.Windowed = TRUE;
    D3DPP_.SwapEffect = D3DSWAPEFFECT_DISCARD;
    D3DPP_.BackBufferFormat = D3DFMT_UNKNOWN;
    D3DPP_.EnableAutoDepthStencil = TRUE;
    D3DPP_.AutoDepthStencilFormat = D3DFMT_D16;
    D3DPP_.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    if (FAILED(D3D_->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &D3DPP_, &Device_)))
        return false;

    return true;
}

void DirectX::Shutdown()
{
    if (Device_) {
        Device_->Release();
    }

    if (D3D_) {
        D3D_->Release();
    }
}

void DirectX::Reset()
{
    Render::OnLostDevice();

    Device_->Reset(&D3DPP_);

    Render::OnResetDevice();
}

void DirectX::OnSize(int ResizeWidth, int ResizeHeight)
{
    D3DPP_.BackBufferWidth = ResizeWidth;
    D3DPP_.BackBufferHeight = ResizeHeight;
    Reset();
}

bool DirectX::BeginRender()
{
    Device_->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_RGBA(40, 40, 40, 255), 1.0f, 0);

    if (FAILED(Device_->BeginScene()))
        return false;

    Render::SetupRenderStates();
    return true;
}

void DirectX::EndRender()
{
    Device_->EndScene();

    HRESULT Result = Device_->Present(NULL, NULL, NULL, NULL);

    if (Result == D3DERR_DEVICELOST && Device_->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
        Reset();
    }
}