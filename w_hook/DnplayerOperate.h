#include<string>
#include"Dnplayer.h"
#include<vector>

using namespace std;
//模拟器对象
class DnplayerOperate {	

private:
	DnplayerOperate() {}

	//设置模拟器信息
	vector<Dnplayer*> SetPlayerInfo();
public:
	string path = "E:\\ld\\dnplayer2\\dnconsole.exe ";

	static DnplayerOperate& GetInstance();

	//操作方法
	 void PlayerOperate();


	//查询列表命令
	 wstring SelectList();

	//启动命令
	 wstring StartDnPlayer(int index);

	 //启动app
	 wstring  RunApp(int index,string packagename);

};