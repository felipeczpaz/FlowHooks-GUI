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