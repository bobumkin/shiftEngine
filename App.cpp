#include "App.h"
#include <sstream>
#include <iomanip>

App::App()
	:
	wnd(800, 600, "Shift engine")
{}

int App::Go()
{
	while (true) {
		if (const auto ecode = Window::ProcessMessages()) {
			return *ecode;
		}
		DoFrame();
	}
}

void App::DoFrame()
{
	wnd.Gfx().ClearBuffer(0.0f, 0.0f, 0.0f);
	wnd.Gfx().DrawTestTriangle(-timer.Peek()/4.0f);
	wnd.Gfx().EndFrame();
}