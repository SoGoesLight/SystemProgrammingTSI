#include <windows.h>

LONG WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);

int x0 = 0, y0 = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hwnd;
    MSG msg;
    WNDCLASS w;

    memset(&w, 0, sizeof(WNDCLASS));
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.lpfnWndProc = WndProc;
    w.hInstance = hInstance;
    w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    w.lpszClassName = "My Class";
    RegisterClass(&w);

    hwnd = CreateWindow("My Class", "My title", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LONG WINAPI WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    HDC hDC;

    switch (Message)
    {
    case WM_RBUTTONDOWN:
        x0 = LOWORD(lParam);
        y0 = HIWORD(lParam);
        break;
    case WM_RBUTTONUP:
        hDC = GetDC(hwnd);
        MoveToEx(hDC, x0, y0, NULL);
        LineTo(hDC, LOWORD(lParam), HIWORD(lParam));
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, Message, wParam, lParam);
    }

    return 0;
}