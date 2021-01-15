#pragma once

#include "ViewImpl.h"

namespace dion {
	class View {
	private:
		View();
		View(View&) = delete;

	public:
		static ViewImpl* CreateInstance(const char* src);
		static ViewImpl* CreateFileInstance(const char* filename);
	};
}