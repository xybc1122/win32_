#include<string>
using namespace std;
//模拟器对象
class DnplayerOperate {	

private:
	DnplayerOperate() {}
public:

	static DnplayerOperate& getInstance();

	string path = "E:\\ld\\dnplayer2\\dnconsole.exe ";


	//查询列表命令
	 wstring selectList();

	//启动命令
	 wstring startDnPlayer(int index);
	 //启动app
	 wstring  runApp(int index,string packagename);

};