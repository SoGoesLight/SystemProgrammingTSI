#include <windows.h>
#include <string>

LONG WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);

int x0coord = 0, y0coord = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hwnd;
    MSG msg;
    WNDCLASS w;

    memset(&w, 0, sizeof(WNDCLASS));
    w.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    w.lpfnWndProc = WndProc;
    w.hInstance = hInstance;
    w.hbrBackground = (HBRUSH)GetStockObject(2);
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
    std::string str;

    switch (Message)
    {
    case WM_LBUTTONDBLCLK:
        MessageBox(NULL, "Hello!", "MSG box", MB_OK | MB_OKCANCEL);
        break;
    case WM_LBUTTONDOWN:
        hDC = GetDC(hwnd);
        x0coord = LOWORD(lParam);
        y0coord = HIWORD(lParam);
        str += std::to_string(x0coord) + " " + std::to_string(y0coord);
        TextOut(hDC, x0coord, y0coord, str.c_str(), str.length());
        break;
    case WM_RBUTTONDOWN:
        x0coord = LOWORD(lParam);
        y0coord = HIWORD(lParam);
        break;
    case WM_RBUTTONUP:
        hDC = GetDC(hwnd);
        SelectObject(hDC, GetStockObject(DC_PEN));
        SetDCPenColor(hDC, RGB(0, 0, 255));
        MoveToEx(hDC, x0coord, y0coord, NULL);
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