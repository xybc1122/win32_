#include"DmOperate.h"
#include"Dnplayer.h"
#include"RunExe.h"
#include"DnplayerOperate.h"
#include"ExeCmd.h"
#include"StringUtils.h"


#define Range(min,max)min+rand()%(max-min+1)



DmOperate::DmOperate(Idmsoft* dm, Dnplayer* player){
		this->dm= dm;
		this->player = player;
		GetClientSize(&this->width, &this->height);
}


Idmsoft* DmOperate::GetDm() {
	return this->dm;
}


DmOperate::~DmOperate() {


}


void DmOperate::BindWindow() {

	long bindResult = this->dm->BindWindowEx(this->player->bindHandle, "dx.graphic.opengl", "windows", "windows", "", 0);
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
	//this->dm->SetDict(0,"test.txt");
}

//解除绑定
void  DmOperate::UnWindow() {
	if (this->dm->UnBindWindow()==1) {
		::MessageBox(NULL, L"解绑成功", _T("success"), MB_OK);
		return;
	}
	::MessageBox(NULL, L"解绑失败", _T("error"), MB_OK);
}


//获取窗口 宽度跟高度
void DmOperate::GetClientSize(VARIANT* width, VARIANT* height) {

	this->dm->GetClientSize(this->player->bindHandle, width, height);

}

//左键
void DmOperate::LeftClick(VARIANT x, int x1, VARIANT y, int y1, int sleep) {

	LClick(_ttoi((LPCTSTR)(_bstr_t)x), x1, _ttoi((LPCTSTR)(_bstr_t)y), y1, sleep);

}
void DmOperate::LeftClick(int x,int x1,int y ,int y1, int sleep) {
	LClick(x, x1, y, y1, sleep);
}
void DmOperate::LeftClick(double x, int x1, double y, int y1, int sleep) {
	int width = _ttoi((LPCTSTR)(_bstr_t)this->width);
	int height = _ttoi((LPCTSTR)(_bstr_t)this->height);

	LClick((int)(width * x), x1, (int)(height * y), y1, sleep);
}

void DmOperate::LClick(int x, int x1, int y, int y1, int sleep) {
	x = Range(x, x + x1);
	y = Range(y, y + y1);
	//移动
	this->dm->MoveTo(x, y);
	//左击
	this->dm->LeftClick();

	Sleep(rand() % sleep + 100);

}
//左键一直按住
void DmOperate::LeftDown(int x, int x1, int y, int y1, int sleep) {
	x = Range(x, x + x1);
	y = Range(y, y + y1);
	//移动
	this->dm->MoveTo(x, y);

	//左击按住
	this->dm->LeftDown();

	Sleep(rand() % sleep + 100);
}

void DmOperate::MoveTo(int x, int x1, int y, int y1, int sleep) {

	x = Range(x, x + x1);
	y = Range(y, y + y1);

	//移动
	this->dm->MoveTo(x, y);

	Sleep(rand() % sleep + 100);

}

//左键弹起
void DmOperate::LeftUp() {
	this->dm->LeftUp();
}


//右键
void DmOperate:: RightClick(int x, int x1, int y, int y1,int sleep) {
	//加上随机偏移
	x = Range(x, x+x1);
	y = Range(y, y+y1);

	//移动
	this->dm->MoveTo(x, y);
	//左击
	this->dm->RightClick();

	Sleep(rand()% sleep+100);
}



void DmOperate::RightDown() {

	this->dm->RightDown();
	
	RightUp();
}

void DmOperate::RightUp() {

	this->dm->RightUp();


}

void DmOperate::KeyPress(int key) {
	SetWindowState(12);
	this->dm->KeyPress(key);
}

void DmOperate::KeyDown(int key) {
	SetWindowState(12);
	this->dm->KeyDown(key);
}

void DmOperate::KeyUp(int key) {
	SetWindowState(12);
	this->dm->KeyUp(key);
}


void DmOperate::SetWindowState(int flag) {

	this->dm->SetWindowState(this->player->bindHandle,flag);

}

long  DmOperate::FindPic(double x1, double y1, double x2, double y2, std::string picName, std::string deltaColor, double sim, int dir, VARIANT* x, VARIANT* y) {
		int width = _ttoi((LPCTSTR)(_bstr_t)this->width);
		int height = _ttoi((LPCTSTR)(_bstr_t)this->height);
	return this->dm->FindPic((int)(width * x1), (int)(height *y1), (int)(width * x2), (int)(height * y2), picName.c_str(), deltaColor.c_str(), sim, dir, x, y);
	
}
	//找字库
	map<string,int> DmOperate::FindStrFastEx(int x1, double y1, double x2, double y2, std::string colorFormat, std::string color,double sim) {
	int width = _ttoi((LPCTSTR)(_bstr_t)this->width);
	int height = _ttoi((LPCTSTR)(_bstr_t)this->height);
	string  strFast=(char*)this->dm->FindStrFastEx(x1, (int)(height * y1), (int)(width * x2), (int)(height * y2), colorFormat.c_str(), color.c_str(), sim);
	map<std::string, int> strFastMap;
	if (strFast!="") {
		vector<string> strFastList = Split(strFast, "|");
		vector<string> strFastV=Split(strFastList[0], ",");
		strFastMap.insert(std::pair<std::string, int>("index", std::stoi(strFastV[0])));
		strFastMap.insert(std::pair<std::string, int>("x", std::stoi(strFastV[1])));
		strFastMap.insert(std::pair<std::string, int>("y", std::stoi(strFastV[2])));
		return strFastMap;
	}
	return strFastMap;
}