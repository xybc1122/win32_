#pragma once
#include<string>
#include"Dnplayer.h"
#include<vector>

using namespace std;
//模拟器对象
class DnplayerOperate {	

private:
	DnplayerOperate() {}

public:
	string path = "E:\\ld\\dnplayer2\\dnconsole.exe ";

	static DnplayerOperate& GetInstance();
	
	//设置模拟器信息
	Dnplayer* SetPlayerInfo(string str);

	//查询列表命令
	 wstring SelectList();

	//启动命令
	 wstring StartDnPlayer(int index);

	 //启动app
	 wstring  RunApp(int index,string packagename);

};