#include "HwndViewport.h"
#include "standart_resources.h"

namespace onyxengine
{
    LRESULT CALLBACK vpProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
    {
        switch (Msg)
        {
        case WM_ACTIVATE:
            MessageBox(hWnd, L"OKOK", L"caption", MB_OK);
            return 0;

        case WM_CLOSE:
            DestroyWindow(hWnd);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
            break;

        case WM_SIZE:
            break;

        default:break;
        }

        return DefWindowProc(hWnd, Msg, wParam, lParam);
    }

    HwndViewport::HwndViewport(HWND Parent, int Width, int Height)
    {
        WNDCLASSEX wc;
        ZeroMemory(&wc, sizeof(wc));

        wc.cbSize = sizeof(wc);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = vpProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = 0;
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = STANDART_BACKCOLOR;
        wc.lpszMenuName = NULL;
        wc.lpszClassName = STANDART_WINDOW_CLASSNAME;
        wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

        RegisterClassEx(&wc);

        RECT rect{};
        GetWindowRect(Parent, &rect);

        AdjustWindowRect(&rect, WS_CHILD, FALSE);

        const int top{ rect.top };
        const int left{ rect.left };
        const int width{ rect.right - left };
        const int height{ rect.bottom - top };

        const wchar_t* caption{ L"Onyx Editor Viewport" };

        Handle = CreateWindowEx(0, wc.lpszClassName, caption, WS_CHILD, left, top, width, height, Parent, NULL, NULL, NULL);

        ShowWindow(Handle, SW_SHOWNORMAL);
        UpdateWindow(Handle);
    }

    HwndViewport::~HwndViewport()
    {
    }

    HWND HwndViewport::GetHandle()
    {
        return Handle;
    }
}