#include<string>
#include"Dnplayer.h"
#include<vector>

using namespace std;
//ģ��������
class DnplayerOperate {	

private:
	DnplayerOperate() {}

	//����ģ������Ϣ
	vector<Dnplayer*> SetPlayerInfo();
public:
	string path = "E:\\ld\\dnplayer2\\dnconsole.exe ";

	static DnplayerOperate& GetInstance();

	//��������
	 void PlayerOperate();


	//��ѯ�б�����
	 wstring SelectList();

	//��������
	 wstring StartDnPlayer(int index);

	 //����app
	 wstring  RunApp(int index,string packagename);

};