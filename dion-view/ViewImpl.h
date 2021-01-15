#pragma once
#include <string>

namespace dion {
	class ViewImpl {
	protected:
		std::wstring title{};
		unsigned int x{}, y{};

	public:
		virtual void init() = 0;
		virtual void free() = 0;
	};
}