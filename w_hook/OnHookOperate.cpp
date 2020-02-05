#include"OnHookOperate.h"
#define sellp(x) Sleep(rand() % x + 100);



OnHookOperate::OnHookOperate(DmOperate* dmOperate)
{
	this->dmOperate = dmOperate;
}

OnHookOperate::~OnHookOperate()
{

}

void OnHookOperate::StartOnHook() {
	
	//BOOL selFlg=SelectStarMap("x.bmp");
	//if (!selFlg) {
	//	::MessageBox(NULL, L"寻找挂机列表失败", _T("error"), MB_OK);
	//}
	OnHook140Map();

}




BOOL OnHookOperate::SelectStarMap(std::string img) {

	VARIANT x, y;
	//点击右上角 按钮
	dmOperate->LeftClick(0.94, 10, 0.07, 10, 3000);
	//点击副本
	dmOperate->LeftClick(0.9, 10, 0.1, 10, 3000);
	//点击星图
	dmOperate->LeftClick(0.15, 15, 0.7, 15, 3000);
	BOOL  isFlg = TRUE;
	int index = 0;
	do {
		if (index==10) {
			return FALSE;
		}
		dmOperate->LeftDown(817, 15, 425, 10, 500);
		dmOperate->MoveTo(818, 15, 148, 15, 500);
		dmOperate->LeftUp();
		sellp(4000);
		//找图片
		long  xRet = dmOperate->FindPic(0.55, 0.25, 0.95, 0.8, img, "989898", 1.0, 0, &x, &y);
		if (xRet == 0) {
			//选择星图
			dmOperate->LeftClick(x, 15, y, 15, 3000);
			//点击进入
			dmOperate->LeftClick(0.9, 10, 0.9, 5, 3000);
			//点击确认
			dmOperate->LeftClick(0.6, 10, 0.75, 10, 3000);
			//点击捂手
			dmOperate->LeftClick(0.1, 5, 0.25, 5, 3000);
			//创建队伍
			dmOperate->LeftClick(0.1, 5, 0.3, 5, 3000);
			//点击确认
			dmOperate->LeftClick(0.5, 10, 0.9, 10, 3000);
			isFlg = FALSE;
		}
		sellp(1800);
		index++;
	} while (isFlg);
	return TRUE;
}



void OnHookOperate::OnHook140Map() {
	int index = 0;
	//先按下f
	dmOperate->KeyPress(70);
	sellp(500);
	//然后按下c
	dmOperate->KeyPress(67);
	sellp(500);
	//往右走
	dmOperate->KeyDown(39);
	sellp(500);
	//弹起
	dmOperate->KeyUp(39);
	sellp(500);
	//往下
	dmOperate->KeyDown(40);
	sellp(500);
	//按空格
	dmOperate->KeyPress(32);
	sellp(500);
	//弹起
	dmOperate->KeyUp(40);
	sellp(500);
	while (TRUE) {
		//往左走
		if (index<15) {
			//弹起
			dmOperate->KeyDown(37);
			sellp(2000);
			if (rand() % 4 == 0) {
				dmOperate->KeyPress(32);
			}
			//攻击
			dmOperate->KeyPress(86);
			dmOperate->KeyUp(37);
		}
		else {
			dmOperate->KeyDown(39);
			sellp(2000);
			if (rand() % 6 == 0) {
				dmOperate->KeyPress(32);
			}
			//攻击
			dmOperate->KeyPress(86);
			dmOperate->KeyUp(39);
			if (index >30 ) {
				index = 0;
			}
		}
		index++;
	}
}


