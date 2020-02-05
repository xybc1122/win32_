#include "WinUtils.h"
#include <TlHelp32.h>
#include <ShellAPI.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <atlstr.h>
DWORD FindPid(const char* name) {
	//1��������
	HANDLE  hsnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hsnapshot == INVALID_HANDLE_VALUE)
	{
		std::cout << "��������ʧ��" << std::endl;
		return 0;
	}

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);

	int flag = Process32First(hsnapshot, &pe);

	while (flag != 0)
	{	
		USES_CONVERSION;
		char* szExeFile = CW2A(pe.szExeFile);//ת����Ĭ��
		if (strcmp(szExeFile, name) == 0)
		{
			return pe.th32ProcessID;
		}
		flag = Process32Next(hsnapshot, &pe);
	}

	CloseHandle(hsnapshot);

	return 0;


}


BOOL LoadDll(DWORD dwProcessId, const char* pathName) {
	//1 ��ȡ���̾��
	HANDLE  hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
	if (hProcess == NULL) {
		return false;
	}
	//2����Dll ·�����ֳ���,������0��β�ĳ���
	size_t stLen = strlen(pathName) + 1;
	//3 ��Ŀ����̷����ڴ�
	LPVOID lpAllocAddr = VirtualAllocEx(hProcess, NULL, stLen, MEM_COMMIT, PAGE_READWRITE);
	if (lpAllocAddr == NULL) {
		std::cout << "lpAllocAddr error" << std::endl;
		CloseHandle(hProcess);
		return false;
	}
	//4 д���ڴ�
	BOOL isFlg = WriteProcessMemory(hProcess, lpAllocAddr, pathName, stLen, NULL);

	if (!isFlg) {
		std::cout << "WriteProcessMemory error" << std::endl;
		CloseHandle(hProcess);
		return false;
	}
	//5 ��ȡKernel32.dll ģ���ַ
	HMODULE hMoDule = GetModuleHandleA("Kernel32.dll");
	if (hMoDule == NULL) {
		std::cout << "hMoDule error" << std::endl;
		CloseHandle(hProcess);
		return false;
	}
	//6 ��� LoadLibrary�ĵ�ַ
	DWORD dwLoadAddr = (DWORD)GetProcAddress(hMoDule, "LoadLibraryA");
	if (dwLoadAddr == NULL) {
		CloseHandle(hProcess);
		return false;
	}
	//7����Զ���߳� ע��Dll
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)dwLoadAddr, lpAllocAddr, 0, NULL);
	if (hThread == NULL) {
		std::cout << "hThread error" << std::endl;
		CloseHandle(hProcess);
		return false;
	}
	CloseHandle(hThread);

	return true;

}