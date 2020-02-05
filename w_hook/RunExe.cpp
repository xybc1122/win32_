// w_hook.cpp : 定义应用程序的入口点。
#include"pch.h"
#include "framework.h"
#include "RunExe.h"
#include <Windows.h>
#include "resource.h"
#include "WinUtils.h"
#include <direct.h>
#include <stdio.h>
#include"ExeCmd.h"
#include<StringUtils.h>
#include<Dnplayer.h>
#include<DnplayerOperate.h>
#include"DmOperate.h"
#include"InitDm.h"
#include<ctime>
#include"OnHookOperate.h"
#include"LodThread.h"

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



std::vector<string> LODSTRLIST;

//设置大漠操作对象list
std::vector<DmOperate*> DMOPERATELIST;

std::vector<HANDLE> HTHREAD;

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
	//加载次数索引
	unsigned int bindIndex = 0;
	unsigned int unIndex = 0;
	DmOperate* bindDmOper;
	DmOperate* unDmOper;
	OnHookOperate* onHook;
	HANDLE hTherad;
	//消息
	switch (uMsg) {
	case WM_INITDIALOG:
		break;
		//关闭
	case WM_CLOSE:
		EndDialog(hwnd,NULL);
		break;
	case WM_COMMAND:
		switch (wParam) {
			//注入
		case IN_DLL:
			/*HookDll();
			::MessageBox(NULL, L"功能已关闭", _T("注入dll"), MB_OK);*/
			break;
			//卸载
		case UN_DLL:
			::MessageBox(NULL, L"功能已关闭", _T("卸载dll"), MB_OK);
			break;
		case CHECK_GEM:
			
			break;
		//获取模拟器信息
		case GET_DN_INFO:
			//查询模拟器列表
			LODSTRLIST=Split(RunCmdRet(DnplayerOperate::GetInstance().SelectList()), "\n");
			if (LODSTRLIST.size()!=0) {
				::MessageBox(NULL, L"获取成功", _T("success"), MB_OK);
				break;
			}
			::MessageBox(NULL, L"获取失败", _T("error"), MB_OK);
			break;
		case BIND:
			if (LODSTRLIST.size()==0) {
				::MessageBox(NULL, L"请先获取雷电列表参数", _T("error"), MB_OK);
				break;
			}
			// 1全部绑定   2选择绑定			
			for (bindIndex; bindIndex < LODSTRLIST.size() - 1; bindIndex++) {
				bindDmOper = new DmOperate(Init(),DnplayerOperate::GetInstance().SetPlayerInfo(LODSTRLIST[bindIndex]));
				//设置大漠操作对象以及操作的属性
				DMOPERATELIST.push_back(bindDmOper);
				bindDmOper->BindWindow();
			}
			::MessageBox(NULL, L"绑定成功", _T("success"), MB_OK);
			////启动模拟器命令
			//RunCmdEmulator(index);
			////查询启动后的模拟器列表参数
			//Sleep(3000);
			//LODSTR = RunCmdRet(DnplayerOperate::GetInstance().SelectList());
			break;
		case UN_BIND:
			if (DMOPERATELIST.size() == 0) {
				::MessageBox(NULL, L"解绑失败", _T("error"), MB_OK);
				break;
			}
			for (unIndex; unIndex < DMOPERATELIST.size(); unIndex++) {
				unDmOper = DMOPERATELIST[unIndex];
				unDmOper->UnWindow();
			}
			break;
		case STAER_SCRIPT:
			break;
			//开始挂机
		case ON_HOOK:
			if (DMOPERATELIST.size() == 0) {
				::MessageBox(NULL, L"请先绑定窗口", _T("error"), MB_OK);
				break;
			}
			onHook = new OnHookOperate(DMOPERATELIST[1]);
			LodThread(onHook);
			break;
			//暂停
		case STOP_THREAD:
			if (HTHREAD.size()==0) {
				::MessageBox(NULL, L"没有线程可以暂停", _T("error"), MB_OK);
				break;
			}
			hTherad=HTHREAD[0];
			//线程挂起
			SuspendThread(hTherad);
			break;
			//开始
		case START_THREAD:
			if (HTHREAD.size() == 0) {
				::MessageBox(NULL, L"没有线程可以开始", _T("error"), MB_OK);
				break;
			}
			//线程唤醒
			hTherad = HTHREAD[0];
			ResumeThread(hTherad);
			break;
		}	
		break;
	}
	return 0;
		
}
