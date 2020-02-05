//��Į������
#pragma once
#import "dm.dll" no_namespace
#include"pch.h"
#include "Dnplayer.h"
#include<string>
#include <map>
#include<ctime>
#include<ctime>

class DmOperate {
private:

	//���ڿ�� ���߶�
	VARIANT width, height;
	

	//��Į����
	Idmsoft* dm;

	//���ڰ󶨶���
	Dnplayer* player;
	//���յ������
	void LClick(int x, int x1, int y, int y1, int sleep);

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
	
	//���
	void LeftClick(VARIANT x, int x1, VARIANT y, int y1, int sleep);

	//���
	void LeftClick(double x, int x1, double y, int y1, int sleep);

	//���һֱ��ס ʹ�û���
	void LeftDown(int x, int x1, int y, int y1, int sleep);

	//�ƶ�
	void MoveTo(int x, int x1, int y, int y1, int sleep);

	//�������
	void LeftUp();

	//�Ҽ�
	void RightClick(int x, int x1, int y, int y1, int sleep);

	//�Ҽ�һֱ��ס
	void RightDown();

	//�Ҽ�����
	void RightUp();

	//����
	void KeyPress(int key);

	//����һֱ��ס
	void KeyDown(int key);

	//�����ͷ�
	void KeyUp(int key);

	//���ô��ڵ�״̬
	void SetWindowState(int flag);

	//��ͼ
	long  FindPic(double x1, double y1, double x2, double y2, std::string picName, std::string deltaColor, double sim, int dir, VARIANT*x, VARIANT*y);
	//���ֿ�
	std::map<std::string, int> FindStrFastEx(int x1, double y1, double x2, double y2, std::string colorFormat, std::string color, double sim);
	
	//��ȡ���� ��ȸ��߶�
	void GetClientSize(VARIANT* width, VARIANT* height);


};