#include <algorithm>

#include "FHGUI.hpp"
#include "Input.hpp"
#include "Elements/Window.hpp"

namespace FHGUI
{
	void Instance::Update()
	{
		Input::Get().Update();

		if (Input::Get().KeyPressed(VK_INSERT)) {
			IsOpen_ = !IsOpen_;
		}

		if (!IsOpen_) return;
		if (Windows_.empty()) return;

		CurrentTime_ += 0.01f;

		if (DraggingWindow_ && !Input::Get().KeyHeld(VK_LBUTTON)) {
			DraggingWindow_ = nullptr;
		}

		Point CursorPos = Input::Get().CursorPos();

		if (DraggingWindow_) {
			DraggingWindow_->PosX_ = CursorPos.x - DragOffsetX_;
			DraggingWindow_->PosY_ = CursorPos.y - DragOffsetY_;
		}

		bool LeftClick = Input::Get().KeyPressed(VK_LBUTTON);

		for (std::size_t i = 0; i < Windows_.size(); ++i) {
			Window* pWindow = Windows_[i];
			if (!pWindow) continue;

			bool ShouldHandleInput = true;

			for (std::size_t j = 0; j < Windows_.size(); ++j) {
				Window* pOther = Windows_[j];
				if (!pOther || pWindow == pOther) continue;

				if (pOther->LastInputTime_ > pWindow->LastInputTime_) {
					if (Input::Get().MouseInArea(pOther->Area())) {
						ShouldHandleInput = false;
						break;
					}
				}
			}

			if (!ShouldHandleInput)
				continue;

			if (LeftClick && Input::Get().MouseInArea(pWindow->DragArea())) {
				pWindow->LastInputTime_ = CurrentTime_;

				DragOffsetX_ = CursorPos.x - pWindow->PosX_;
				DragOffsetY_ = CursorPos.y - pWindow->PosY_;

				DraggingWindow_ = pWindow;
			}

			pWindow->Update();
		}
	}

	void Instance::Render()
	{
		if (!IsOpen_) return;
		if (Windows_.empty()) return;

		std::sort(Windows_.begin(), Windows_.end(), [](const Window* a, const Window* b) {
			return a->LastInputTime_ < b->LastInputTime_;
			});

		for (std::size_t i = 0; i < Windows_.size(); ++i) {
			Window* pWindow = Windows_[i];
			if (!pWindow) continue;

			pWindow->Render();
		}
	}

	Instance::~Instance()
	{
		for (std::size_t i = 0; i < Windows_.size(); ++i) {
			Window* pWindow = Windows_[i];
			SAFE_DELETE(pWindow);
		}
	}
}