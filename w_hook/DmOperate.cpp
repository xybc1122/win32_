#include"DmOperate.h"
#include<ctime>
#include"Dnplayer.h"
#include<vector>
#include"ThisMian.h"
#include"DnplayerOperate.h"
#include"ExeCmd.h"
#define Range(min,max)min+rand()%(max-min+1)
//void ThreadOper(Dnplayer* player);


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
	//this->dm->SetDict(0,"");
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
void DmOperate::LeftClick(int x,int x1,int y ,int y1, int sleep) {
	x = Range(x, x+x1);
	y = Range(y, y+y1);
	//�ƶ�
	this->dm->MoveTo(x, y);
	//���
	this->dm->LeftClick();

	Sleep(rand() % sleep + 100);
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

long  DmOperate::FindPic(int x1, double y1, double x2, double y2, std::string picName, std::string deltaColor, double sim, int dir, VARIANT* x, VARIANT* y) {
		int width = _ttoi((LPCTSTR)(_bstr_t)this->width);
		int height = _ttoi((LPCTSTR)(_bstr_t)this->height);
	return this->dm->FindPic(x1, (int)(height *y1), (int)(width * x2), (int)(height * y2), picName.c_str(), deltaColor.c_str(), sim, dir, x, y);
	


}



//DWORD WINAPI ThreadProc(LPVOID lpParamter)
//{
//	Dnplayer* player = (Dnplayer*)lpParamter;
//	ThreadOper(player);
//	return 0;
//}


//void ThreadOper(Dnplayer* player) {
//
//	DmOperate* oper = new DmOperate(DMLIST[player->index], player);
//	oper->BindWindow();
//	//����ssr
//	RunCmdRunApp(DnplayerOperate::GetInstance().RunApp(player->index, "in.zhaoj.shadowsocksr"));
//	Sleep(5000);
//	VARIANT vx, vy;
//	for (int i = 0; i < 10; i++) {
//		long ret = oper->FindPic(0, 0.1, 1.0, 0.3, "text1.bmp", "000000", 0.9, 0, &vx, &vy);
//		if (ret != -1) {
//			int x = _ttoi((LPCTSTR)(_bstr_t)vx);
//			int y = _ttoi((LPCTSTR)(_bstr_t)vy);
//			oper->LeftClick(x, 30, y, 20, 1500);
//			oper->KeyPress(112);
//			return;
//		};
//		Sleep(500);
//	}
//	::MessageBox(NULL, L"ssr��ť����ʧ��", _T("error"), MB_OK);
//}

//void DmOperate::PlayerOperate() {
//	//�����������
//	srand((unsigned)time(0));
//	/*std::vector<Dnplayer*> playerList = DnplayerOperate::GetInstance().SetPlayerInfo();
//	for (unsigned int i = 0; i < DMLIST.size(); i++) {
//		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, playerList[i], 0, NULL);
//	}*/
//
//}