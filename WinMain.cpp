#include "Window.h"

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow)
{
	try {
		Window wnd(800, 600, L"Donkey Fart Box");
		MSG msg;
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (gResult == -1) {
			return -1;
		}
		return msg.wParam;
	}
	catch (const CustomException& e) {
		MessageBox(nullptr, (LPCWSTR)e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e) {
		MessageBox(nullptr, (LPCWSTR)e.what(), L"Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...) {
		MessageBox(nullptr, L"No details available", L"Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
}
