#pragma once
#include<windows.h>
#include<iostream>
//��ȡ����pid
DWORD findPid(const char* name);
//����dll
BOOL loadDll(DWORD dwProcessId, const char* pathName);