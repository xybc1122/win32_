#pragma once
#include "resource.h"
#include<vector>
#include<string>
#include"DmOperate.h"
#import "dm.dll" no_namespace 

//加载模拟器列表信息
extern std::vector<std::string> LODSTRLIST;

//设置雷电属性list
extern std::vector<DmOperate*> DMOPERATELIST;


//全局线程句柄
extern std::vector<HANDLE> HTHREAD;