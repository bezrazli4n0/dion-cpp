#include <Windows.h>
#include "../dion-view/View.h"
#include "../dion-view/ViewRunner.h"

int CALLBACK wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
	auto view = dion::View::CreateInstance("<View title=\"Hello World\" x=\"10\" y=\"15\"></View>");
	view->init();
	auto result = dion::ViewRunner::run();
	view->free();
	return result;
}