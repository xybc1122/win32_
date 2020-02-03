//大漠操作类
#pragma once
#include"pch.h"
#import "dm.dll" no_namespace 
#include "Dnplayer.h"
#include<string>

class DmOperate {
private:

	//窗口宽度 跟高度
	VARIANT width, height;
	

	//大漠对象
	Idmsoft* dm;

	//窗口绑定对象
	Dnplayer* player;

public:


	Idmsoft* GetDm();

	DmOperate(Idmsoft* dm,Dnplayer* player);


	~DmOperate();
	

	//绑定窗口
	void BindWindow();

	//解除绑定
	void UnWindow();

	//左键
	void LeftClick(int x, int x1, int y, int y1, int sleep);

	//右键
	void RightClick(int x, int x1, int y, int y1, int sleep);

	//按键
	void KeyPress(int key);

	//键盘一直按住
	void KeyDown(int key);

	//键盘释放
	void KeyUp(int key);

	//设置窗口的状态
	void SetWindowState(int flag);

	//找图
	long  FindPic(int x1, double y1, double x2, double y2, std::string picName, std::string deltaColor, double sim, int dir, VARIANT*x, VARIANT*y);

	//获取窗口 宽度跟高度
	void GetClientSize(VARIANT* width, VARIANT* height);


};