#include <windows.h>
#include <iostream>
// ��wWinMain
//#pragma comment(linker, "/subsystem:console /entry:wWinMainCRTStartup")
// ��main
#pragma comment(linker, "/subsystem:console /entry:mainCRTStartup")

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPreInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	return 0;
}

int main() {
	std::cout << "Hello World!" << std::endl;

}