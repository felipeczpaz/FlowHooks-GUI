#pragma once
#include <d3d9.h>
#include "../Singleton.hpp"

class DirectX : public Singleton<DirectX>
{
public:
	bool Init(HWND hWnd);
	void Shutdown();
	void ResetDevice();
	void OnSize(LPARAM lParam);
	bool BeginRender();
	void EndRender();

	LPDIRECT3DDEVICE9 Device()
	{
		return pDevice_;
	}
private:
	LPDIRECT3D9 pD3D_{ nullptr };
	LPDIRECT3DDEVICE9 pDevice_{ nullptr };
	D3DPRESENT_PARAMETERS D3DPP_{ 0 };
};