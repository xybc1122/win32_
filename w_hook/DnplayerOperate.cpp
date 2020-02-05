#include"DnplayerOperate.h"
#include<StringUtils.h>
#include"RunExe.h"



DnplayerOperate& DnplayerOperate::GetInstance() {
	static DnplayerOperate player;
	return player;
}


wstring DnplayerOperate::SelectList() {
	std::string str =  path +"list2";
	return String2wstring(str);
}




wstring DnplayerOperate::StartDnPlayer(int index) {
	std::string str =" launch --index "+ to_string(index);
	return String2wstring(str);
}



wstring DnplayerOperate::RunApp(int index, string packagename) {
	std::string str ="runapp --index "+to_string(index)+" --packagename "+ packagename;
	return String2wstring(str);
}


Dnplayer* DnplayerOperate::SetPlayerInfo(string str) {
		std::vector<string> dnplayerStr = Split(str, ",");
		Dnplayer* dnplayer = new Dnplayer();
		dnplayer->index = std::stoi(dnplayerStr[0]);//index 索引
		dnplayer->title = dnplayerStr[1];//title 标题
		dnplayer->rootHandle = std::stoi(dnplayerStr[2]);//顶层窗口句柄
		dnplayer->bindHandle = std::stoi(dnplayerStr[3]);//绑定窗口句柄
		dnplayer->pid = std::stoi(dnplayerStr[5]);//进程PID
		return dnplayer;
}