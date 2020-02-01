#pragma once
#include<string>


class Dnplayer {

public :
	//绑定窗口句柄
	int bindHandle= 0;
	//标题
	std::string title= "";
	//索引
	int index= 0;
	//顶层窗口句柄
	int rootHandle= 0;
	//进程pid
	int pid = 0;

	~Dnplayer() {

	}



};