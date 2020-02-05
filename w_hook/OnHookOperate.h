#pragma once
#include"DmOperate.h"
#include<map>

class OnHookOperate
{
public:
	OnHookOperate(DmOperate* dmOperate);

	~OnHookOperate();

	//开始挂机
	void StartOnHook();

private:

	DmOperate* dmOperate;
	//选择星图函数
	BOOL SelectStarMap(std::string img);
	//140级挂机函数
	void OnHook140Map();
};

