//��Į������
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
	

	//�󶨴���
	void BindWindow(Dnplayer* player);

	//�����
	void UnWindow();

	//���
	void LeftClick(int x, int x1, int y, int y1, int sleep);

	//�Ҽ�
	void RightClick(int x, int x1, int y, int y1, int sleep);

	//����
	void KeyPress(int key,int hwnd);

	//����һֱ��ס
	void KeyDown(int key, int hwnd);

	//�����ͷ�
	void KeyUp(int key, int hwnd);

	//���ô��ڵ�״̬
	void SetWindowState(int hwnd, int flag);

	//��ͼ
	long  FindPic(int x1, int y1, int x2, int y2, std::string picName, std::string deltaColor, int sim, int dir, VARIANT*x, VARIANT*y);

	//��ȡ���� ��ȸ��߶�
	void GetClientSize(int hwnd, VARIANT* width, VARIANT* height);
};