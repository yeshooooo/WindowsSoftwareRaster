#include <windows.h>
#include <iostream>
// ��wWinMain
#pragma comment(linker, "/subsystem:console /entry:wWinMainCRTStartup")
// ��main
//#pragma comment(linker, "/subsystem:console /entry:mainCRTStartup")

// �����¼��ص�
LRESULT CALLBACK Wndproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_CLOSE: {
		DestroyWindow(hWnd); // ���ٴ��壬�Զ�����WM_DESTROY��Ϣ�����Զ���ת�������case WM_DESTROY
		break;
	}
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY: {
		PostQuitMessage(0); // �����߳���ֹ����
		exit(0); // �˳�����
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
	wndClass.style = CS_HREDRAW | CS_VREDRAW; // ˮƽ����ֱ��С�����仯��ʱ���ػ洰��
	wndClass.lpfnWndProc = NULL; // �����¼��ص�����
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance; // Ӧ�ó�����ʵ��
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Ӧ�ó�����������ʾ��ͼ��
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // ���ͼ��
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // ���ڱ���ɫ
	wndClass.lpszMenuName = NULL; // �˵���
	wndClass.lpszClassName = L"AppWindow"; // ������������һ�Ѳ����Զ���Ĵ��ڵ�����
	wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO); // ���ڱ���ͼ��

	// ע�ᴰ��
	RegisterClassExW(&wndClass);
	return 0;

	// �������ڲ���ʾ
	
	// ���ô��ڷ��
	// ��չ������
	auto dwExStyle = WS_EX_APPWINDOW;
	// ����������
	auto dwStyle =
		// ӵ����ͨ���������ڵ������ص㣬�����б������б߿�
		WS_OVERLAPPEDWINDOW |
		// ���ֵܴ��ڵ�ס�����򲻻���
		WS_CLIPSIBLINGS |
		// ���Ӵ����ڵ�ס�����򲻻���
		WS_CLIPCHILDREN;

	// ���ݴ��ڷ�����Rect��С
	RECT windowRect;
	windowRect.left = 0L;
	windowRect.top = 0L;
	// �ɾ��Ļ�����С
	windowRect.right = (long)mWidth; 
	windowRect.bottom = (long)mHeight;
	// �Զ��������ڴ�С����������ܱȴ���ȥ��ֵ��΢���
	AdjustWindowRect(
		&windowRect,
		dwStyle,
		FALSE,
		dwExStyle
	);
	// �����õ�����HWND�Ĵ��ھ��
	HWND hwnd = CreateWindowW(
		mWindowClassName,
		(LPCWSTR)"SoftRenderer",
		dwStyle,
		500, // �������Ļ���Ͻǵ�x
		500, // �������Ļ���Ͻǵ�y
		windowRect.right - windowRect.left, // ���ڿ�ȣ����ﲻֱ�Ӵ���������windowRect����Ϊ������Ǵ��ھ���С���������˵�����
		windowRect.bottom - windowRect.top, // ���ڸ߶�
		nullptr, // ������
		nullptr, // �˵���
		hInstance, // ����ʵ��
		nullptr // �������
	);
	ShowWindow(hwnd, true);
	UpdateWindow(hwnd);

}

//int main() {
//	std::cout << "Hello World!" << std::endl;
//
//}