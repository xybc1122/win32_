#include<windows.h>
//��ȡ����pid
DWORD getPid(const char* name);
//����dll
BOOL loadDll(DWORD dwProcessId, const char* pathName);