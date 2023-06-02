#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <windows.h>

LPCWSTR className = L"e9ec3947-4209-4eb4-9f91-36ef7ffbe183";
HWND handle = 0;

std::string (*build)(const char* data) = NULL;

LRESULT APIENTRY handler(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_USER) {
        return wParam;
    } else if (msg == WM_COPYDATA) {
    	PCOPYDATASTRUCT in = (PCOPYDATASTRUCT) lParam;
    	if (build != NULL) {
    		std::string result = build((const char*) in->lpData);

    		COPYDATASTRUCT out;
    		out.dwData = 0;
    		out.cbData = result.length() + 1;
    		out.lpData = (void*) result.c_str();
    		SendMessage((HWND) wParam, WM_COPYDATA, (WPARAM) handle, (LPARAM) &out);
    	}
    }

    return DefWindowProc(handle, msg, wParam, lParam);
}

int start() {
    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASSW wndClass;
    wndClass.style = 0;
    wndClass.lpfnWndProc = &handler;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = 0;
    wndClass.hCursor = 0;
    wndClass.hbrBackground = 0;
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = className;

    if (!RegisterClassW(&wndClass)) {
        return -1;
    }

    handle = CreateWindowExW(
        0,
        className,
        L"",
        WS_POPUP,
        0, 0, 0, 0,
        0, 0,
        hInstance,
        NULL
    );
    if (handle == NULL) {
        return -2;
    }

    MSG msg;
    while (GetMessageW(&msg, 0, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    
    return 0;
}
