// w_hook.cpp : 定义应用程序的入口点。
#include"pch.h"
#include "framework.h"
#include "ThisMian.h"
#include <Windows.h>
#include "resource.h"
#include "ThisLoad.h"
#include <direct.h>
#include <stdio.h>
#include "RegDm.h"
#include "ExeCmd.h"
#include<vector>
#include<StringUtils.h>
#include<Dnplayer.h>
#include<DnplayerOperate.h>

void hookDll() {
	//获取当前目录
	char path[0x100] = { 0 };
	char* buffer = NULL;
	buffer = _getcwd(NULL, 0);
	if (buffer != NULL) {
		sprintf_s(path, "%s\\hook_dll.dll", buffer);
	}
	if (!loadDll(findPid("123.exe"), path)) {
		MessageBox(0, L"注入失败", 0, 0);
		return;
	};
	MessageBox(0, L"注入成功", 0, 0);

}
static std::wstring root = L"cmd.exe /C ";

static std::wstring path = L"E:\\ld\\dnplayer2\\dnconsole.exe ";


//加载模拟器列表 str
static std::string lodStr;

static std::vector<Idmsoft*> dmList;
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
		lodStr = runCmdRet(DnplayerOperate::getInstance().selectList());
		for (index; index < split(lodStr, "\n").size() - 1; index++) {
			//初始化加载 存入多窗口对象
				dmList.push_back(init());
		}
		//置空
		lodStr = "";
		break;
		//关闭
	case WM_CLOSE:
		EndDialog(hwnd,NULL);
		break;
	case WM_COMMAND:
		switch (wParam) {
			//注入
		case IN_DLL:
			//hookDll();
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
			runCmdEmulator(index);
			//查询启动后的模拟器列表参数
			Sleep(3000);
			lodStr = runCmdRet(DnplayerOperate::getInstance().selectList());
			break;
		case STAER_SCRIPT:
			if (lodStr =="") {
				::MessageBox(NULL, L"请先启动模拟器", _T("error"), MB_OK);
				break;
			}
			std::vector<string> strList=split(lodStr,"\n");
			std::vector<Dnplayer*> dnplayerList;
			for (unsigned int i = 0; i < strList.size()-1; i++) {
				std::vector<string> dnplayerStr=split(strList[i],",");
				Dnplayer* dnplayer = new Dnplayer();
				dnplayer->index=std::stoi(dnplayerStr[0]);//index 索引
				dnplayer->title=dnplayerStr[1];//title 标题
				dnplayer->rootHandle= std::stoi(dnplayerStr[2]);//顶层窗口句柄
				dnplayer->bindHandle= std::stoi(dnplayerStr[3]);//绑定窗口句柄
				dnplayer->pid= std::stoi(dnplayerStr[5]);//进程PID
				//存入启动对象
				dnplayerList.push_back(dnplayer);
			}
			for (unsigned int i = 0; i < dmList.size();i++) {
				//绑定大漠
				bindWindow(dmList[i], dnplayerList[i]->bindHandle, dnplayerList[i]->index);
			}	
			break;
		}	
		break;
	}
	return 0;
		
}
