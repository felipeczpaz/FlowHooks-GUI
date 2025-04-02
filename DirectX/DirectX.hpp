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