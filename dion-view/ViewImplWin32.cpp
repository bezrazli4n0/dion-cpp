#include "ViewImplWin32.h"
#include <tinyxml2.h>
#include <stdexcept>

namespace dion {
	void ViewImplWin32::init()
	{
		WNDCLASSEX wc{ sizeof(wc) };
		wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
		wc.style = CS_VREDRAW | CS_HREDRAW;
		wc.lpszClassName = title.c_str();
		wc.lpfnWndProc = windowProc;

		if (!RegisterClassEx(&wc))
			throw std::runtime_error{ "Failed to init ViewImplWin32" };

		auto handle = CreateWindowEx(0, wc.lpszClassName, title.c_str(), WS_OVERLAPPEDWINDOW, x, y, 640, 480, nullptr, nullptr, nullptr, this);
		UpdateWindow(handle);
		ShowWindow(handle, SW_SHOW);
	}

	ViewImplWin32::ViewImplWin32(const char* src)
	{
		tinyxml2::XMLDocument doc;
		doc.Parse(src);

		auto windowElement = doc.RootElement();

		std::string title{ windowElement->Attribute("title") };
		this->title = std::wstring(title.begin(), title.end());
		x = std::atoi(windowElement->Attribute("x"));
		y = std::atoi(windowElement->Attribute("y"));
	}

	LRESULT ViewImplWin32::windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		ViewImplWin32* pView{};

		if (uMsg == WM_NCCREATE)
		{
			pView = static_cast<ViewImplWin32*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);

			SetLastError(0);
			if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pView)))
				if (GetLastError() != 0)
					return false;
		}
		else
			pView = reinterpret_cast<ViewImplWin32*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		if (pView)
			return pView->viewProc(hWnd, uMsg, wParam, lParam);

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	LRESULT ViewImplWin32::viewProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
			case WM_DESTROY:
			{
				PostQuitMessage(EXIT_SUCCESS);
				return 0;
			}
		}

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	void ViewImplWin32::free()
	{
		UnregisterClass(title.c_str(), nullptr);
	}
}