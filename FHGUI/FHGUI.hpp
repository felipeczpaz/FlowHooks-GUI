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
#include <vector>

#include "../Singleton.hpp"
#include "Datatypes.hpp"

namespace FHGUI
{
	class Window;

	class Instance : public Singleton<Instance>
	{
	public:
		void Update();
		void Render();
		~Instance();

		void RegisterWindow(Window* pWindow)
		{
			Windows_.emplace_back(pWindow);
		}

	private:
		bool IsOpen_{ true };
		float CurrentTime_{ -1.0f };
		std::vector<Window*> Windows_{};
		Window* DraggingWindow_{ nullptr };
		int DragOffsetX_{ 0 };
		int DragOffsetY_{ 0 };
	};
}