#pragma once
#include<string>
#include"Dnplayer.h"
#include<vector>

using namespace std;
//ģ��������
class DnplayerOperate {	

private:
	DnplayerOperate() {}

public:
	string path = "E:\\ld\\dnplayer2\\dnconsole.exe ";

	static DnplayerOperate& GetInstance();
	
	//����ģ������Ϣ
	Dnplayer* SetPlayerInfo(string str);

	//��ѯ�б�����
	 wstring SelectList();

	//��������
	 wstring StartDnPlayer(int index);

	 //����app
	 wstring  RunApp(int index,string packagename);

};