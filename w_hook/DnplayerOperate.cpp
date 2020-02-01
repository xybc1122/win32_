#include"DnplayerOperate.h"
#include <stdio.h>
#include<StringUtils.h>



DnplayerOperate& DnplayerOperate::getInstance() {
	static DnplayerOperate player;
	return player;
}


std::wstring DnplayerOperate::selectList() {
	std::string str =  path +"list2";
	return string2wstring(str);
}




std::wstring DnplayerOperate::startDnPlayer(int index) {
	std::string str =" launch --index "+ to_string(index);
	return string2wstring(str);
}



std::wstring DnplayerOperate::runApp(int index, string packagename) {
	std::string str ="runapp --index "+to_string(index)+" --packagename "+ packagename;
	return string2wstring(str);
}