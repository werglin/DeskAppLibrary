#pragma once
// main document : https://learn.microsoft.com/en-us/windows/win32/directx
// last document : https://learn.microsoft.com/en-us/windows/win32/learnwin32/dpi-and-device-independent-pixels
// helper document : https://learn.microsoft.com/en-us/windows/win32/api/_direct2d/
// To make program scale with screensize (ex: texts)
/*
* On the Project menu, click Property.
In the left pane, expand Configuration Properties, expand Manifest Tool, and then click Input and Output.
In the Additional Manifest Files text box, type the name of the manifest file, and then click OK.
*/



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
