#pragma once
#include "BaseWindow.cpp"
#include <d2d1.h>
#pragma comment(lib, "d2d1")

class MainWindow : public BaseWindow<MainWindow>
{
    ID2D1Factory* pFactory;
    ID2D1HwndRenderTarget* pRenderTarget;
    ID2D1SolidColorBrush* pBrush;
    ID2D1SolidColorBrush* pBrushRect;
    D2D1_ELLIPSE            ellipse;
    //Tryin somethin
    D2D1_ROUNDED_RECT rR;

    void    CalculateLayout();
    HRESULT CreateGraphicsResources();
    void    DiscardGraphicsResources();
    void    OnPaint();
    void    Resize();

public:

    MainWindow();

    PCWSTR  ClassName() const { return L"Circle Window Class"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};
