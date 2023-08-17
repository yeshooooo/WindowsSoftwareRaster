#include <windows.h>
#include <iostream>
// 走wWinMain
#pragma comment(linker, "/subsystem:console /entry:wWinMainCRTStartup")
// 走main
//#pragma comment(linker, "/subsystem:console /entry:mainCRTStartup")

// 窗体事件回调
LRESULT CALLBACK Wndproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_CLOSE: {
		DestroyWindow(hWnd); // 销毁窗体，自动发出WM_DESTROY消息，会自动跳转到下面的case WM_DESTROY
		break;
	}
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY: {
		PostQuitMessage(0); // 发出线程终止请求
		exit(0); // 退出进程
		break;
	}
	return(DefWindowProc(hWnd, message, wParam, lParam));

	}
}

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPreInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	WNDCLASSEXW wndClass;
	wndClass.cbSize = sizeof(WNDCLASSEXW);
	wndClass.style = CS_HREDRAW | CS_VREDRAW; // 水平、垂直大小发生变化的时候重绘窗口
	wndClass.lpfnWndProc = NULL; // 窗口事件回调函数
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance; // 应用程序句柄实例
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 应用程序任务栏显示的图标
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // 鼠标图标
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // 窗口背景色
	wndClass.lpszMenuName = NULL; // 菜单栏
	wndClass.lpszClassName = L"AppWindow"; // 窗口类名，这一堆参数自定义的窗口的类名
	wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO); // 窗口标题图标

	// 注册窗口
	RegisterClassExW(&wndClass);
	return 0;

	// 创建窗口并显示
	
	// 设置窗口风格
	// 扩展窗体风格
	auto dwExStyle = WS_EX_APPWINDOW;
	// 基础窗体风格
	auto dwStyle =
		// 拥有普通程序主窗口的所有特点，必须有标题且有边框
		WS_OVERLAPPEDWINDOW |
		// 被兄弟窗口挡住的区域不绘制
		WS_CLIPSIBLINGS |
		// 被子窗口遮挡住的区域不绘制
		WS_CLIPCHILDREN;

	// 根据窗口风格调整Rect大小
	RECT windowRect;
	windowRect.left = 0L;
	windowRect.top = 0L;
	// 干净的画布大小
	windowRect.right = (long)mWidth; 
	windowRect.bottom = (long)mHeight;
	// 自动调整窗口大小，调整完可能比传进去的值稍微大点
	AdjustWindowRect(
		&windowRect,
		dwStyle,
		FALSE,
		dwExStyle
	);
	// 最终拿到的是HWND的窗口句柄
	HWND hwnd = CreateWindowW(
		mWindowClassName,
		(LPCWSTR)"SoftRenderer",
		dwStyle,
		500, // 相对于屏幕左上角的x
		500, // 相对于屏幕左上角的y
		windowRect.right - windowRect.left, // 窗口宽度，这里不直接传参数而用windowRect是因为计算的是窗口净大小，不包括菜单栏等
		windowRect.bottom - windowRect.top, // 窗口高度
		nullptr, // 父窗口
		nullptr, // 菜单栏
		hInstance, // 程序实例
		nullptr // 额外参数
	);
	ShowWindow(hwnd, true);
	UpdateWindow(hwnd);

}

//int main() {
//	std::cout << "Hello World!" << std::endl;
//
//}