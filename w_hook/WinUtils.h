#pragma once
#include<windows.h>
#include<iostream>
//��ȡ����pid
DWORD FindPid(const char* name);
//����dll
BOOL LoadDll(DWORD dwProcessId, const char* pathName);