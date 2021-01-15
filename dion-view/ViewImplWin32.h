#pragma once
#include "ViewImpl.h"
#include <Windows.h>

namespace dion {
	class View;

	class ViewImplWin32 : public ViewImpl {
	private:
		ViewImplWin32(const char* src);

		static LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK viewProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		HWND handle{};
	public:
		void init();
		void free();

		friend class View;
	};
}