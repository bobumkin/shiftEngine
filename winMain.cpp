#include <Windows.h>
#include <iostream>
#include <string>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        PostQuitMessage(1);
        break;
    case WM_KEYDOWN:
        if (wParam == 'F') {
            SetWindowText(hWnd, L"Respects");
        }
        break;
    case WM_KEYUP:
        if (wParam == 'F') {
            SetWindowText(hWnd, L"Dangerfield");
        }
        break;
    case WM_CHAR:
        static std::string title;
        title += (char)wParam;
        SetWindowText(hWnd, (LPCWSTR)title.c_str());
        break;
    case WM_LBUTTONDOWN:
        POINTS pt = MAKEPOINTS(lParam);
        std::ostringstream oss;
        oss << "(" << pt.x << ", " << pt.y << ")";
        SetWindowText(hWnd, (LPCWSTR)oss.str().c_str());
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

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
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = nullptr;
    wc.hCursor = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = pClassName;
    wc.hIconSm = nullptr;
    RegisterClassEx(&wc);
    HWND hWnd = CreateWindowEx(
        0, pClassName,
        L"Happy Hard Windows",
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
        200, 200, 600, 400,
        nullptr, nullptr, hInstance, nullptr
    );
    ShowWindow(hWnd, SW_SHOW);
    MSG msg;
    BOOL gResult;
    while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    if (gResult == -1) {
        return -1;
    }
    else {
        return (int)msg.wParam;
    }
}