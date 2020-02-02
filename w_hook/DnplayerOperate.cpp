#include"DnplayerOperate.h"
#include <stdio.h>
#include<StringUtils.h>
#include"DmOperate.h"
#include"ThisMian.h"
#include"ExeCmd.h"


DnplayerOperate& DnplayerOperate::GetInstance() {
	static DnplayerOperate player;
	return player;
}

void DnplayerOperate::PlayerOperate() {

	vector<Dnplayer*> playerList=SetPlayerInfo();
	for (unsigned int i = 0; i < DMLIST.size();i++) {
		Dnplayer* player =playerList[i];
		//启动cmd
		//启动ssr
		RunCmdRunApp(DnplayerOperate::GetInstance().RunApp(player->index, "in.zhaoj.shadowsocksr"));
		Sleep(2000);
		DmOperate* oper = new DmOperate(DMLIST[i]);
		oper->BindWindow(player);
		//窗口宽度 跟高度
		VARIANT vwidth,vheight;
		oper->GetClientSize(player->bindHandle, &vwidth, &vheight);
		VARIANT vx, vy;
		for (int i = 0; i < 20; i++) {
			int width = _ttoi((LPCTSTR)(_bstr_t)vwidth);
			int height = _ttoi((LPCTSTR)(_bstr_t)vheight);

			if (oper->FindPic(0, (int)height*0.1, (int)width * 0.8, (int)height * 0.3, "text1.bmp", "ffffff-666666", 0.9, 0, &vx, &vy)){
				int x = _ttoi((LPCTSTR)(_bstr_t)vx);
				int y = _ttoi((LPCTSTR)(_bstr_t)vy);
				oper->LeftClick(x, 10, y, 5, 1000);
				break;
			};
			Sleep(500);
		}
	}

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


vector<Dnplayer*> DnplayerOperate::SetPlayerInfo() {

	std::vector<string> strList = Split(LODSTR, "\n");
	std::vector<Dnplayer*> dnplayerList;
	for (unsigned int i = 0; i < strList.size() - 1; i++) {
		std::vector<string> dnplayerStr = Split(strList[i], ",");
		Dnplayer* dnplayer = new Dnplayer();
		dnplayer->index = std::stoi(dnplayerStr[0]);//index 索引
		dnplayer->title = dnplayerStr[1];//title 标题
		dnplayer->rootHandle = std::stoi(dnplayerStr[2]);//顶层窗口句柄
		dnplayer->bindHandle = std::stoi(dnplayerStr[3]);//绑定窗口句柄
		dnplayer->pid = std::stoi(dnplayerStr[5]);//进程PID
		//存入启动对象
		dnplayerList.push_back(dnplayer);
	}
	return dnplayerList;
}