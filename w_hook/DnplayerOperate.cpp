#include"DnplayerOperate.h"
#include <stdio.h>
#include<StringUtils.h>
#include"ThisMian.h"



//void ThreadOnHook(Dnplayer* player) {
//		DmOperate* oper = new DmOperate(DMLIST[player->index], player);
//		oper->BindWindow();
//		oper->LeftClick(932, 15, 26, 15, 1500);
//		oper->LeftClick(855, 15, 36, 15, 1500);
//
//}


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
		dnplayer->index = std::stoi(dnplayerStr[0]);//index ����
		dnplayer->title = dnplayerStr[1];//title ����
		dnplayer->rootHandle = std::stoi(dnplayerStr[2]);//���㴰�ھ��
		dnplayer->bindHandle = std::stoi(dnplayerStr[3]);//�󶨴��ھ��
		dnplayer->pid = std::stoi(dnplayerStr[5]);//����PID
		return dnplayer;
}