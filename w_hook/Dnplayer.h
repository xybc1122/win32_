#pragma once
#include<string>


class Dnplayer {

public :
	//�󶨴��ھ��
	int bindHandle= 0;
	//����
	std::string title= "";
	//����
	int index= 0;
	//���㴰�ھ��
	int rootHandle= 0;
	//����pid
	int pid = 0;

	~Dnplayer() {

	}



};