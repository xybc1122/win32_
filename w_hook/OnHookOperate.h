#pragma once
#include"DmOperate.h"
#include<map>

class OnHookOperate
{
public:
	OnHookOperate(DmOperate* dmOperate);

	~OnHookOperate();

	//��ʼ�һ�
	void StartOnHook();

private:

	DmOperate* dmOperate;
	//ѡ����ͼ����
	BOOL SelectStarMap(std::string img);
	//140���һ�����
	void OnHook140Map();
};

