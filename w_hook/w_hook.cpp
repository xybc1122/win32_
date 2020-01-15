// w_hook.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "w_hook.h"
#include <Windows.h>
#include "resource.h"
#include "load.h"
#include <direct.h>
#include <stdio.h>

INT_PTR CALLBACK Dlgproc(HWND Arg1, UINT uMsg, WPARAM Arg3, LPARAM Arg4);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine, 
                     _In_ int       nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(ID_MAIN),NULL, &Dlgproc);
	return 0;
}
void hookDll() {
	//获取当前目录
	char path[0x100] = { 0 };
	char* buffer = NULL;
	buffer = _getcwd(NULL, 0);
	if (buffer != NULL) {
		sprintf_s(path, "%s\\hook_dll.dll", buffer);
	}
	if (!loadDll(getPid("123.exe"), path)) {
		MessageBox(0, "注入失败", 0, 0);
		return;
	};
	MessageBox(0, "注入成功", 0, 0);

}

INT_PTR CALLBACK Dlgproc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM Arg4) {
	
	//消息
	switch (uMsg) {
	case WM_INITDIALOG:
		//首次加载
		break;
		//关闭
	case WM_CLOSE:
		EndDialog(hwnd,NULL);
		break;
	case WM_COMMAND:
		switch (wParam) {
			//注入
		case IN_DLL:
			hookDll();
			break;
			//卸载
		case UN_DLL:
			
			break;
		}
		break;
	}
	return 0;
		
}
