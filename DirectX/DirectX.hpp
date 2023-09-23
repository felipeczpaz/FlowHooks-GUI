#pragma once
#include <d3d9.h>
#include "../Singleton.hpp"

class DirectX : public Singleton<DirectX>
{
public:
	bool Init(HWND hWnd);
	void Shutdown();
	void Reset();
	void OnSize(int ResizeWidth, int ResizeHeight);
	bool BeginRender();
	void EndRender();

	LPDIRECT3DDEVICE9 Device()
	{
		return Device_;
	}

private:
	LPDIRECT3D9 D3D_{ nullptr };
	LPDIRECT3DDEVICE9 Device_{ nullptr };
	D3DPRESENT_PARAMETERS D3DPP_{ 0 };
};