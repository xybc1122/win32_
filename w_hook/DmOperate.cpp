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
		::MessageBox(NULL, L"��ʧ��", _T("error"), MB_OK);
		return;
	}
	//����ǰ̨�����ģ�ⷽʽ. 
	this->dm->SetSimMode(1);
	//��궯��ģ����ʵ����,���ƶ��켣,�Լ������ʱ���. 
	this->dm->EnableRealMouse(2, 20, 30);
	//���̶���ģ����ʵ����,�����ʱ���.
	this->dm->EnableRealKeypad(1);
	//���ֿ�
	//this->dm->SetDict(0,"test.txt");
}

//�����
void  DmOperate::UnWindow() {
	if (this->dm->UnBindWindow()==1) {
		::MessageBox(NULL, L"���ɹ�", _T("success"), MB_OK);
		return;
	}
	::MessageBox(NULL, L"���ʧ��", _T("error"), MB_OK);
}


//��ȡ���� ��ȸ��߶�
void DmOperate::GetClientSize(VARIANT* width, VARIANT* height) {

	this->dm->GetClientSize(this->player->bindHandle, width, height);

}

//���
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
	//�ƶ�
	this->dm->MoveTo(x, y);
	//���
	this->dm->LeftClick();

	Sleep(rand() % sleep + 100);

}
//���һֱ��ס
void DmOperate::LeftDown(int x, int x1, int y, int y1, int sleep) {
	x = Range(x, x + x1);
	y = Range(y, y + y1);
	//�ƶ�
	this->dm->MoveTo(x, y);

	//�����ס
	this->dm->LeftDown();

	Sleep(rand() % sleep + 100);
}

void DmOperate::MoveTo(int x, int x1, int y, int y1, int sleep) {

	x = Range(x, x + x1);
	y = Range(y, y + y1);

	//�ƶ�
	this->dm->MoveTo(x, y);

	Sleep(rand() % sleep + 100);

}

//�������
void DmOperate::LeftUp() {
	this->dm->LeftUp();
}


//�Ҽ�
void DmOperate:: RightClick(int x, int x1, int y, int y1,int sleep) {
	//�������ƫ��
	x = Range(x, x+x1);
	y = Range(y, y+y1);

	//�ƶ�
	this->dm->MoveTo(x, y);
	//���
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
	//���ֿ�
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