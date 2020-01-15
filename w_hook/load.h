#include<windows.h>
//获取进程pid
DWORD getPid(const char* name);
//加载dll
BOOL loadDll(DWORD dwProcessId, const char* pathName);