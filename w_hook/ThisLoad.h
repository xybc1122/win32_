#pragma once
#include<windows.h>
#include<iostream>
//获取进程pid
DWORD findPid(const char* name);
//加载dll
BOOL loadDll(DWORD dwProcessId, const char* pathName);