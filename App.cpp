#include "App.h"
#include <sstream>
#include <iomanip>

App::App()
	:
	wnd(1200, 800, "Shift engine")
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
	wnd.Gfx().DrawTestTriangle(
		-timer.Peek(),
		0.0f,
		0.0f
	);
	wnd.Gfx().DrawTestTriangle(timer.Peek(),
		wnd.mouse.GetPosX() / 600.0f - 1,
		-wnd.mouse.GetPosY() / 400.0f + 1);
	wnd.Gfx().EndFrame();
}