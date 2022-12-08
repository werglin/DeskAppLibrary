#pragma once
#include <Windows.h>
#include <d2d1.h>
class DPIScale
{
    inline static float scale = 1.0f;

public:
    static void Initialize(HWND hwnd)
    {
        float dpi = GetDpiForWindow(hwnd);
        scale = dpi / 96.0f;
    }

    template <typename T>
    static D2D1_POINT_2F PixelsToDips(T x, T y)
    {
        return D2D1::Point2F(static_cast<float>(x) / scale, static_cast<float>(y) / scale);
    }

    template <typename T>
    static FLOAT PixelsToDipsX(T x)
    {
        return static_cast<float>(x) / scale ;
    }
    template <typename T>
    static FLOAT PixelsToDipsY(T y)
    {
        return static_cast<float>(y) / scale ;
    }
};