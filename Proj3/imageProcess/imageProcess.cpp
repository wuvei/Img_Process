//imageProcess.cpp: 定义应用程序的入口点。
//

#include "stdafx.h"
#include "imageProcess.h"

#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

HWND NTextPrompt;
HWND NTrack; 
HWND NText;
HWND STextPrompt;
HWND ScaleTrack;
HWND SText;
HWND CGTextPrompt;
HWND CGTrack;
HWND CGText;

int border = 50;
int scale = 50;
int maxCG = 3;

bool imgExist = false;

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_IMAGEPROCESS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_IMAGEPROCESS));

    MSG msg;

    // 主消息循环: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;

}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_IMAGEPROCESS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_IMAGEPROCESS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	
	case WM_CREATE:
	{
		//界面中的文本控件和slider控件
	HWND NTextPrompt = CreateWindow(
			L"static", //静态文本框的类名
			L"N",  //控件的文本
			WS_CHILD /*子窗口*/ | WS_VISIBLE /*创建时显示*/ | SS_CENTER /*水平居中*/ | SS_CENTERIMAGE /*垂直居中*/ | WS_EX_TRANSPARENT,
			0 /*X坐标*/, 10 /*Y坐标*/, 20 /*宽度*/, 30 /*高度*/,
			hWnd,  //父窗口句柄
			(HMENU)ID_STATIC_N1,  //为控件指定一个唯一标识符
			hInst,  //当前程序实例句柄
			NULL);
	NTrack = CreateTrackbar(hWnd, hInst, imInfo{ 20,10,200,30 }, (HMENU)ID_TRACKBAR_N,5, 200, 5, 200,50);

	NText = CreateWindow( L"static",L"5",  WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE |WS_EX_TRANSPARENT,
		      220, 10 , 20 , 30, hWnd,(HMENU)ID_STATIC_N2, hInst, NULL);
	STextPrompt = CreateWindow(L"static", 	L"scale",WS_CHILD| WS_VISIBLE| SS_CENTER| SS_CENTERIMAGE| WS_EX_TRANSPARENT,
		260, 10, 50, 30 ,hWnd,(HMENU)ID_STATIC_S1,	hInst,NULL);
	ScaleTrack = CreateTrackbar(hWnd, hInst, imInfo{ 310,10,200,30 }, (HMENU)ID_TRACKBAR_S,1, 300, 1, 300,50);

	SText = CreateWindow(L"static", L"100", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | WS_EX_TRANSPARENT,
		500, 10, 50, 30, hWnd, (HMENU)ID_STATIC_S2, hInst, NULL);
	CGTextPrompt = CreateWindow(L"static", L"maxCG", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | WS_EX_TRANSPARENT,
		560, 10, 50, 30, hWnd, (HMENU)ID_STATIC_CG1, hInst, NULL);
	CGTrack = CreateTrackbar(hWnd, hInst, imInfo{ 620,10,200,30 }, (HMENU)ID_TRACKBAR_CG, 2, 20, 2, 20,3);

	CGText = CreateWindow(L"static", L"3", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | WS_EX_TRANSPARENT,
		810, 10, 50, 30, hWnd, (HMENU)ID_STATIC_CG2, hInst, NULL);

	break;
	}
	case WM_CTLCOLORSTATIC:
	{
		HDC hdc = (HDC)wParam;
        SetTextColor(hdc, RGB(0, 0, 0));
        SetBkMode(hdc, TRANSPARENT);
        return (LRESULT)GetStockObject(NULL_BRUSH);
	}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case IDM_OPEN_IMAGE:
				if (openImage(hWnd)) {
					if (enhance(border,scale,maxCG)) {
						imgExist = true;
						InvalidateRect(hWnd, NULL, TRUE);
					}
				}
				break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
			displayMyImage(hdc);
			displayEnhanceImage( hdc);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_HSCROLL:
	{
		if (lParam == (LPARAM)NTrack) {	//识别是哪个slider的响应消息。
			TBNotifications(
				hWnd,
				wParam,  // wParam of WM_HSCROLL message 
				NTrack, // handle of trackbar window
				border,
				NText
			);

		}
		else if (lParam == (LPARAM)ScaleTrack) {
			TBNotifications(
				hWnd,
				wParam,  // wParam of WM_HSCROLL message 
				ScaleTrack, // handle of trackbar window
				scale,
				SText
			);
		}
		else if (lParam == (LPARAM)CGTrack) {
			TBNotifications(
				hWnd,
				wParam,  // wParam of WM_HSCROLL message 
				CGTrack, // handle of trackbar window
				maxCG,
				CGText
			);
		}

	}
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
