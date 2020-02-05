//大漠操作类
#pragma once
#import "dm.dll" no_namespace
#include"pch.h"
#include "Dnplayer.h"
#include<string>
#include <map>
#include<ctime>
#include<ctime>

class DmOperate {
private:

	//窗口宽度 跟高度
	VARIANT width, height;
	

	//大漠对象
	Idmsoft* dm;

	//窗口绑定对象
	Dnplayer* player;
	//最终点击方法
	void LClick(int x, int x1, int y, int y1, int sleep);

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
	
	//左键
	void LeftClick(VARIANT x, int x1, VARIANT y, int y1, int sleep);

	//左键
	void LeftClick(double x, int x1, double y, int y1, int sleep);

	//左键一直按住 使用滑动
	void LeftDown(int x, int x1, int y, int y1, int sleep);

	//移动
	void MoveTo(int x, int x1, int y, int y1, int sleep);

	//左键弹起
	void LeftUp();

	//右键
	void RightClick(int x, int x1, int y, int y1, int sleep);

	//右键一直按住
	void RightDown();

	//右键弹起
	void RightUp();

	//按键
	void KeyPress(int key);

	//键盘一直按住
	void KeyDown(int key);

	//键盘释放
	void KeyUp(int key);

	//设置窗口的状态
	void SetWindowState(int flag);

	//找图
	long  FindPic(double x1, double y1, double x2, double y2, std::string picName, std::string deltaColor, double sim, int dir, VARIANT*x, VARIANT*y);
	//找字库
	std::map<std::string, int> FindStrFastEx(int x1, double y1, double x2, double y2, std::string colorFormat, std::string color, double sim);
	
	//获取窗口 宽度跟高度
	void GetClientSize(VARIANT* width, VARIANT* height);


};