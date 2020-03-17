

#include "Window.h"


#ifdef _WIN32

Renderer* window_renderer = NULL;

LRESULT CALLBACK WindowProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        if(window_renderer != NULL)
            window_renderer->Render();
        ValidateRect(hwnd, NULL);   // 更新客户区的显示
        break;
    default:
        if (window_renderer != NULL)
            window_renderer->Render();
        break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

#endif // _WIN32

Window::Window(char* window_title, int window_width, int window_height)
{
    
#ifdef _WIN32
    int title_n = MultiByteToWideChar(0,0,window_title,-1,NULL,0);
    WCHAR* class_name = new WCHAR[title_n];
    MultiByteToWideChar(0, 0, window_title, -1, class_name, title_n);

    this->title = (char*)class_name;
    this->width = window_width;
    this->height = window_height;

    this->WindowCreate(this->width, this->height);
#endif // _WIN32
    
#ifdef __linux
    this->title = window_title;
    this->width = window_width;
    this->height = window_height;

    glutInit(NULL, NULL);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    this->WindowCreate(this->width, this->height);
#endif // __linux

}

Window::~Window()
{
}

void Window::WindowCreate(int window_width, int window_height)
{
#ifdef _WIN32

    this->width = window_width;
    this->height = window_height;

    // Register the window class.
    this->window_class = { sizeof(WNDCLASSEX), CS_CLASSDC, WindowProc, 0L, 0L,
    GetModuleHandle(NULL), NULL, NULL, NULL, NULL,(WCHAR*)this->title, NULL };

    RegisterClassEx(&this->window_class);

    this->hWnd = CreateWindow((WCHAR*)this->title, (WCHAR*)this->title,WS_OVERLAPPEDWINDOW,
        0, 0, this->width, this->height,GetDesktopWindow(), NULL, this->window_class.hInstance, NULL);

    ShowWindow(this->hWnd, SW_SHOWDEFAULT);
    UpdateWindow(this->hWnd);
#endif // _WIN32

#ifdef __linux
    this->width = window_width;
    this->height = window_height;

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(this->width, this->height);
    glutCreateWindow(this->title);

    glutMainLoop();
#endif // __linux

}

void Window::MainLoop()
{
#ifdef _WIN32

    //if (this->renderer != NULL)
        //goto RendererIsTrue;

    while (GetMessage(&this->msg, NULL, 0, 0))
    {
        TranslateMessage(&this->msg);
        DispatchMessage(&this->msg);
    }
    goto Unregister;

RendererIsTrue:
    while (this->msg.message != WM_QUIT)
    {
        if (PeekMessage(&this->msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&this->msg);
            DispatchMessage(&this->msg);
        }
    }

Unregister:
    UnregisterClass((WCHAR*)this->title, this->window_class.hInstance);  //程序准备结束，注销窗口类
    
#endif // _WIN32
}

void Window::SetRenderer(Renderer* renderer)
{
    this->renderer = renderer;

#ifdef _WIN32
    window_renderer = this->renderer;
#endif // _WIN32
    
}

