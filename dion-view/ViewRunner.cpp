#include "ViewRunner.h"
#include <Windows.h>

namespace dion {
    int ViewRunner::run()
    {
        MSG msg{};
        while (GetMessage(&msg, nullptr, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return static_cast<int>(msg.wParam);
    }
}
