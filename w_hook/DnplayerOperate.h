#include<string>
using namespace std;
//ģ��������
class DnplayerOperate {	

private:
	DnplayerOperate() {}
public:

	static DnplayerOperate& getInstance();

	string path = "E:\\ld\\dnplayer2\\dnconsole.exe ";


	//��ѯ�б�����
	 wstring selectList();

	//��������
	 wstring startDnPlayer(int index);
	 //����app
	 wstring  runApp(int index,string packagename);

};