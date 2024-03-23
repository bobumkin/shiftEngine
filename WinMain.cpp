#include <Windows.h>
#include <string>

int wWinMain(
    _In_ HINSTANCE hInstance,
    _In_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd)
{
    const wchar_t pClassName[] = L"hw3dbutts";
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(wc);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = DefWindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = nullptr;
    wc.hCursor = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = pClassName;
    wc.hIconSm = nullptr;
    RegisterClassEx( &wc );
    HWND hWnd = CreateWindowEx(
        0, pClassName,
        L"Happy Hard Windows",
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
        200, 200, 650, 480,
        nullptr, nullptr, hInstance, nullptr
    );
    ShowWindow(hWnd, SW_SHOW);
    while (true);
    return 0;
}