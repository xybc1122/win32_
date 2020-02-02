//大漠操作类
#include"pch.h"
#import "dm.dll" no_namespace 
#include "Dnplayer.h"
#include<string>

class DmOperate {
private:

	Idmsoft* dm;

public:

	Idmsoft* GetDm();

	DmOperate(Idmsoft* dm);


	~DmOperate();
	

	//绑定窗口
	void BindWindow(Dnplayer* player);

	//解除绑定
	void UnWindow();

	//左键
	void LeftClick(int x, int x1, int y, int y1, int sleep);

	//右键
	void RightClick(int x, int x1, int y, int y1, int sleep);

	//按键
	void KeyPress(int key,int hwnd);

	//键盘一直按住
	void KeyDown(int key, int hwnd);

	//键盘释放
	void KeyUp(int key, int hwnd);

	//设置窗口的状态
	void SetWindowState(int hwnd, int flag);

	//找图
	long  FindPic(int x1, int y1, int x2, int y2, std::string picName, std::string deltaColor, int sim, int dir, VARIANT*x, VARIANT*y);

	//获取窗口 宽度跟高度
	void GetClientSize(int hwnd, VARIANT* width, VARIANT* height);
};