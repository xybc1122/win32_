#include"LodThread.h"
#include"RunExe.h"

void Run(OnHookOperate* oper);


DWORD WINAPI ThreadProc(LPVOID lpParamter)
{
	OnHookOperate* oper =(OnHookOperate*)lpParamter;
	Run(oper);
	return 0;
}

void Run(OnHookOperate* oper) {

	oper->StartOnHook();

}


void LodThread(OnHookOperate* oper) {
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, oper, 0, NULL);
	HTHREAD.push_back(hThread);
}
