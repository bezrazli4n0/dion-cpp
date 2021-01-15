#include "View.h"

#ifdef _WIN32
	#include "ViewImplWin32.h"
#endif

#include <stdexcept>

namespace dion {
	ViewImpl* View::CreateInstance(const char* src)
	{
		#ifdef _WIN32
			return new ViewImplWin32{ src };
		#elif
			throw std::runtime_error{ "Not implemented" };
			return nullptr;
		#endif
	}

	ViewImpl* View::CreateFileInstance(const char* filename)
	{
		return nullptr;
	}
}
