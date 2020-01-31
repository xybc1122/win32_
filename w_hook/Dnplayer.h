#pragma once
#include<string>


class Dnplayer {

public :
	//绑定窗口句柄
	int bindHandle;
	//标题
	std::string title;
	//索引
	int index;
	//顶层窗口句柄
	int rootHandle;
	//进程pid
	int pid;

	~Dnplayer() {

	}





};