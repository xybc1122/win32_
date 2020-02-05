#pragma once
#include<windows.h>
#include<iostream>
//获取进程pid
DWORD FindPid(const char* name);
//加载dll
BOOL LoadDll(DWORD dwProcessId, const char* pathName);