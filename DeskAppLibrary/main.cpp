#pragma once
// main document : https://learn.microsoft.com/en-us/windows/win32/directx
// last document : https://learn.microsoft.com/en-us/windows/win32/learnwin32/render-targets--devices--and-resources
// helper document : https://learn.microsoft.com/en-us/windows/win32/api/_direct2d/

#include"MainWin.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
    MainWindow win;

    if (!win.Create(L"Circle", WS_OVERLAPPEDWINDOW))
    {
        return 0;
    }

    ShowWindow(win.Window(), nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
