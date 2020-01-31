#include<windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <ShellAPI.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <atlstr.h>
DWORD findPid(const char* name) {
	//1创建快照
	HANDLE  hsnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hsnapshot == INVALID_HANDLE_VALUE)
	{
		std::cout << "创建快照失败" << std::endl;
		return 0;
	}

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);

	int flag = Process32First(hsnapshot, &pe);

	while (flag != 0)
	{	
		USES_CONVERSION;
		char* szExeFile = CW2A(pe.szExeFile);//转化成默认
		if (strcmp(szExeFile, name) == 0)
		{
			return pe.th32ProcessID;
		}
		flag = Process32Next(hsnapshot, &pe);
	}

	CloseHandle(hsnapshot);

	return 0;


}


BOOL loadDll(DWORD dwProcessId, const char* pathName) {
	//1 获取进程句柄
	HANDLE  hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
	if (hProcess == NULL) {
		return false;
	}
	//2计算Dll 路径名字长度,并加上0结尾的长度
	size_t stLen = strlen(pathName) + 1;
	//3 在目标进程分配内存
	LPVOID lpAllocAddr = VirtualAllocEx(hProcess, NULL, stLen, MEM_COMMIT, PAGE_READWRITE);
	if (lpAllocAddr == NULL) {
		std::cout << "lpAllocAddr error" << std::endl;
		CloseHandle(hProcess);
		return false;
	}
	//4 写入内存
	BOOL isFlg = WriteProcessMemory(hProcess, lpAllocAddr, pathName, stLen, NULL);

	if (!isFlg) {
		std::cout << "WriteProcessMemory error" << std::endl;
		CloseHandle(hProcess);
		return false;
	}
	//5 获取Kernel32.dll 模块地址
	HMODULE hMoDule = GetModuleHandleA("Kernel32.dll");
	if (hMoDule == NULL) {
		std::cout << "hMoDule error" << std::endl;
		CloseHandle(hProcess);
		return false;
	}
	//6 获得 LoadLibrary的地址
	DWORD dwLoadAddr = (DWORD)GetProcAddress(hMoDule, "LoadLibraryA");
	if (dwLoadAddr == NULL) {
		CloseHandle(hProcess);
		return false;
	}
	//7创建远程线程 注入Dll
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)dwLoadAddr, lpAllocAddr, 0, NULL);
	if (hThread == NULL) {
		std::cout << "hThread error" << std::endl;
		CloseHandle(hProcess);
		return false;
	}
	CloseHandle(hThread);

	return true;

}


bool  runProcess(std::wstring strProcessName)
{
	TCHAR tszProcess[64] = { 0 };
	lstrcpy(tszProcess, (LPCWSTR)strProcessName.c_str());
	//启动程序
	SHELLEXECUTEINFO shellInfo;
	memset(&shellInfo, 0, sizeof(SHELLEXECUTEINFO));
	shellInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	shellInfo.fMask = NULL;
	shellInfo.hwnd = NULL;
	shellInfo.lpVerb = NULL;
	shellInfo.lpFile = tszProcess;                      // 执行的程序名(绝对路径)
	shellInfo.lpParameters = NULL;
	shellInfo.lpDirectory = NULL;
	shellInfo.nShow = SW_MINIMIZE;                      //SW_SHOWNORMAL 全屏显示这个程序
	shellInfo.hInstApp = NULL;
	printf("程序自动重启中.... \n");
	ShellExecuteEx(&shellInfo);

	return true;
}