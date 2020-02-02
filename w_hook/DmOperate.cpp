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
	//this->dm->SetDict(0,"");
}

//�����
void  DmOperate::UnWindow() {
	this->dm->UnBindWindow();
}


//��ȡ���� ��ȸ��߶�
void DmOperate::GetClientSize(int hwnd, VARIANT* width, VARIANT* height) {

	this->dm->GetClientSize(hwnd, width, height);

}

//���
void DmOperate::LeftClick(int x,int x1,int y ,int y1, int sleep) {
	srand((int)time(0));	
	//ƫ��
	x = rand() % x1 + 1;

	y = rand() % y1 + 1;
	//�ƶ�
	this->dm->MoveTo(x, y);
	//���
	this->dm->LeftClick();

	Sleep(rand() % sleep + 100);
}

//�Ҽ�
void DmOperate:: RightClick(int x, int x1, int y, int y1,int sleep) {
	srand((int)time(0));
	//ƫ��
	x = rand() % x1 + 1;

	y = rand() % y1 + 1;
	//�ƶ�
	this->dm->MoveTo(x, y);
	//���
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