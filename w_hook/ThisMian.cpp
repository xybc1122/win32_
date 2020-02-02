// w_hook.cpp : 定义应用程序的入口点。
#include"pch.h"
#include "framework.h"
#include "ThisMian.h"
#include <Windows.h>
#include "resource.h"
#include "ThisLoad.h"
#include <direct.h>
#include <stdio.h>
#include"ExeCmd.h"
#include<StringUtils.h>
#include<Dnplayer.h>
#include<DnplayerOperate.h>
#include"DmOperate.h"
#include"InitDm.h"

//void HookDll() {
//	//获取当前目录
//	char path[0x100] = { 0 };
//	char* buffer = NULL;
//	buffer = _getcwd(NULL, 0);
//	if (buffer != NULL) {
//		sprintf_s(path, "%s\\hook_dll.dll", buffer);
//	}
//	if (!loadDll(findPid("123.exe"), path)) {
//		MessageBox(0, L"注入失败", 0, 0);
//		return;
//	};
//	MessageBox(0, L"注入成功", 0, 0);
//
//}


//static std::wstring root = L"cmd.exe /C ";
//
//static std::wstring path = L"E:\\ld\\dnplayer2\\dnconsole.exe ";


std::string LODSTR;

std::vector<Idmsoft*> DMLIST;


//加载次数索引
unsigned int index = 0;

INT_PTR CALLBACK Dlgproc(HWND Arg1, UINT uMsg, WPARAM Arg3, LPARAM Arg4);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine, 
                     _In_ int       nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(ID_MAIN),NULL, &Dlgproc);
	return 0;
}


INT_PTR CALLBACK Dlgproc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM Arg4) {
	
	//消息
	switch (uMsg) {
	case WM_INITDIALOG:
		//查询模拟器列表
		LODSTR = RunCmdRet(DnplayerOperate::GetInstance().SelectList());
		for (index; index < Split(LODSTR, "\n").size() - 1; index++) {
				//初始化加载 存入多窗口对象
			DMLIST.push_back(Init());
		}
		//置空
		LODSTR = "";
		break;
		//关闭
	case WM_CLOSE:
		EndDialog(hwnd,NULL);
		break;
	case WM_COMMAND:
		switch (wParam) {
			//注入
		case IN_DLL:
			//HookDll();
			::MessageBox(NULL, L"功能已关闭", _T("注入dll"), MB_OK);
			break;
			//卸载
		case UN_DLL:
			::MessageBox(NULL, L"功能已关闭", _T("卸载dll"), MB_OK);
			break;

		case CHECK_GEM:
			
			break;
		case START:
			//启动模拟器命令
			RunCmdEmulator(index);
			//查询启动后的模拟器列表参数
			Sleep(3000);
			LODSTR = RunCmdRet(DnplayerOperate::GetInstance().SelectList());
			break;
		case STAER_SCRIPT:
			if (LODSTR =="") {
				::MessageBox(NULL, L"请先启动模拟器", _T("error"), MB_OK);
				break;
			}
			//操作方法
			DnplayerOperate::GetInstance().PlayerOperate();
			break;
		}	
		break;
	}
	return 0;
		
}
