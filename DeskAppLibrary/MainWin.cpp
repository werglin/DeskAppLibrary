#include "MainWin.h"

template <class T>
void SafeRelease(T** ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}


// Recalculate drawing layout when the size of the window changes.

void MainWindow::CalculateLayout()
{
    if (pRenderTarget != NULL)
    {
        D2D1_SIZE_F size = pRenderTarget->GetSize();
        const float x = size.width / 2;
        const float y = size.height / 2;
        const float radius = min(x, y);
        ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius);
        //tryin 
        D2D1_RECT_F rectRr = { 
                ellipse.point.x-(ellipse.radiusX/2)
                ,ellipse.point.y - (ellipse.radiusY / 2)
                ,ellipse.point.x + (ellipse.radiusX / 2),
                ellipse.point.y + (ellipse.radiusY / 2) };
        rR = D2D1::RoundedRect(rectRr, 1.0f, 1.0f);
    }
}

HRESULT MainWindow::CreateGraphicsResources()
{
    HRESULT hr = S_OK;
    if (pRenderTarget == NULL)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc); // Screen size to rect

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom); // rect to directx type size

        hr = pFactory->CreateHwndRenderTarget( // factory makes the render target
            D2D1::RenderTargetProperties(), // default props
            D2D1::HwndRenderTargetProperties(m_hwnd, size),  // my props
            &pRenderTarget);    // target

        if (SUCCEEDED(hr))
        {
            const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 0); // solid ellipse color
            hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);


            if (SUCCEEDED(hr) && SUCCEEDED( pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Aqua), &pBrushRect) ))
            {
                // added brush for rect
                CalculateLayout();
            }
        }
    }
    return hr;
}

void MainWindow::DiscardGraphicsResources()
{
    SafeRelease(&pRenderTarget);
    SafeRelease(&pBrush);
    SafeRelease(&pBrushRect);
}

void MainWindow::OnPaint()
{
    HRESULT hr = CreateGraphicsResources();
    if (SUCCEEDED(hr))
    {
        PAINTSTRUCT ps;
        BeginPaint(m_hwnd, &ps);

        pRenderTarget->BeginDraw();// simply a message which tells we are starting to draw

        //pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));  // paints background skyblue , default is black
        pRenderTarget->FillEllipse(ellipse, pBrush);  // paints ellips
        pRenderTarget->FillRoundedRectangle(rR,pBrushRect); // paints roundedrect

        hr = pRenderTarget->EndDraw(); // end message
        if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET) // if there is a problem 
        {
            DiscardGraphicsResources(); // just let resources go
        }
        EndPaint(m_hwnd, &ps);
    }
}

void MainWindow::Resize()
{
    if (pRenderTarget != NULL)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        pRenderTarget->Resize(size);
        CalculateLayout();
        InvalidateRect(m_hwnd, NULL, FALSE);
    }
}


MainWindow::MainWindow() : pFactory(NULL), pRenderTarget(NULL), pBrush(NULL)
{
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        if (FAILED(D2D1CreateFactory(
            D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
        {
            return -1;  // Fail CreateWindowEx.
        }
        return 0;

    case WM_DESTROY:
        DiscardGraphicsResources();
        SafeRelease(&pFactory);
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        OnPaint();
        return 0;



    case WM_SIZE:
        Resize();
        return 0;
    }
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}


