//��Į������
#pragma once
#include"pch.h"
#import "dm.dll" no_namespace 
#include "Dnplayer.h"
#include<string>

class DmOperate {
private:

	//���ڿ�� ���߶�
	VARIANT width, height;
	

	//��Į����
	Idmsoft* dm;

	//���ڰ󶨶���
	Dnplayer* player;

public:


	Idmsoft* GetDm();

	DmOperate(Idmsoft* dm,Dnplayer* player);


	~DmOperate();
	

	//�󶨴���
	void BindWindow();

	//�����
	void UnWindow();

	//���
	void LeftClick(int x, int x1, int y, int y1, int sleep);

	//�Ҽ�
	void RightClick(int x, int x1, int y, int y1, int sleep);

	//����
	void KeyPress(int key);

	//����һֱ��ס
	void KeyDown(int key);

	//�����ͷ�
	void KeyUp(int key);

	//���ô��ڵ�״̬
	void SetWindowState(int flag);

	//��ͼ
	long  FindPic(int x1, double y1, double x2, double y2, std::string picName, std::string deltaColor, double sim, int dir, VARIANT*x, VARIANT*y);

	//��ȡ���� ��ȸ��߶�
	void GetClientSize(VARIANT* width, VARIANT* height);


};