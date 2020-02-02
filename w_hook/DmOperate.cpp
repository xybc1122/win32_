#include"DmOperate.h"
#include<ctime>


DmOperate::DmOperate(Idmsoft* dm){
		this->dm= dm;
}


Idmsoft* DmOperate::GetDm() {
	return this->dm;
}


DmOperate::~DmOperate() {


}


void DmOperate::BindWindow(Dnplayer* player) {

	long bindResult = this->dm->BindWindowEx(player->bindHandle, "dx.graphic.opengl", "windows", "windows", "", 0);
	if (!bindResult) {
		::MessageBox(NULL, L"绑定失败", _T("error"), MB_OK);
		return;
	}
	//设置前台键鼠的模拟方式. 
	this->dm->SetSimMode(1);
	//鼠标动作模拟真实操作,带移动轨迹,以及点击延时随机. 
	this->dm->EnableRealMouse(2, 20, 30);
	//键盘动作模拟真实操作,点击延时随机.
	this->dm->EnableRealKeypad(1);
	//绑定字库
	//this->dm->SetDict(0,"");
}

//解除绑定
void  DmOperate::UnWindow() {
	this->dm->UnBindWindow();
}


//获取窗口 宽度跟高度
void DmOperate::GetClientSize(int hwnd, VARIANT* width, VARIANT* height) {

	this->dm->GetClientSize(hwnd, width, height);

}

//左键
void DmOperate::LeftClick(int x,int x1,int y ,int y1, int sleep) {
	srand((int)time(0));	
	//偏移
	x = rand() % x1 + 1;

	y = rand() % y1 + 1;
	//移动
	this->dm->MoveTo(x, y);
	//左击
	this->dm->LeftClick();

	Sleep(rand() % sleep + 100);
}

//右键
void DmOperate:: RightClick(int x, int x1, int y, int y1,int sleep) {
	srand((int)time(0));
	//偏移
	x = rand() % x1 + 1;

	y = rand() % y1 + 1;
	//移动
	this->dm->MoveTo(x, y);
	//左击
	this->dm->RightClick();

	Sleep(rand()% sleep+100);
}



void DmOperate::KeyPress(int key, int hwnd) {
	SetWindowState(hwnd,12);
	this->dm->KeyPress(key);
}

void DmOperate::KeyDown(int key, int hwnd) {
	SetWindowState(hwnd, 12);
	this->dm->KeyDown(key);
}

void DmOperate::KeyUp(int key, int hwnd) {
	SetWindowState(hwnd, 12);
	this->dm->KeyUp(key);
}


void DmOperate::SetWindowState(int hwnd, int flag) {

	this->dm->SetWindowState(hwnd,flag);

}

long  DmOperate::FindPic(int x1, int y1, int x2, int y2, std::string picName, std::string deltaColor, int sim, int dir, VARIANT* x, VARIANT* y) {


	return this->dm->FindPic(x1, y1, x2, y2, picName.c_str(), deltaColor.c_str(), sim, dir, x, y);
	


}