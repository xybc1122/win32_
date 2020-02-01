#include "pch.h"
#include "RegDm.h"
#include<iostream>
#include"ThisLoad.h"
#include <direct.h>
#include "DnplayerOperate.h"
#include"EXECmd.h"


Idmsoft* InitNewDm();



Idmsoft* init() {
	Idmsoft* m_dm =InitNewDm();
	 //首次加载
	 if (m_dm != NULL) {
		 DWORD dw = m_dm->Reg();
		 if (dw == 1) {

			 m_dm->SetPath("E:\img");
			 return m_dm;
		 }
	 }
	 return NULL;
}


void bindWindow(Idmsoft* m_dm, int hwnd,int index) {
	long bindResult =m_dm->BindWindowEx(hwnd, "dx.graphic.opengl", "windows", "windows","", 0);
	if (!bindResult) {
		::MessageBox(NULL, L"绑定失败", _T("error"), MB_OK);
			return;
	}
	//设置前台键鼠的模拟方式. 
	m_dm->SetSimMode(1);
	//鼠标动作模拟真实操作,带移动轨迹,以及点击延时随机. 
	m_dm->EnableRealMouse(2, 20, 30);
	//键盘动作模拟真实操作,点击延时随机.
	m_dm->EnableRealKeypad(1);
	//启动ssr
	runCmdRunApp(DnplayerOperate::getInstance().runApp(index,"in.zhaoj.shadowsocksr"));


	VARIANT intX, intY;
	long dm_ret =m_dm->FindPic(904, 62, 930, 82, "text1.bmp", "203040", 0.9, 0, &intX, &intY);
	//m_dm->MoveTo(intX, intY);
	//m_dm->LeftClick();

}



//创建新的大漠对象
Idmsoft* InitNewDm()
{
	Idmsoft* m_dm = NULL;
	//COleVariant temp1,temp2;
	bool m_bInit = false;

	//下面直接加载dll创建对象，避免进行注册文件
	typedef HRESULT(__stdcall* pfnGCO) (REFCLSID, REFIID, void**);
	pfnGCO fnGCO = NULL;
	HINSTANCE hdllInst = LoadLibrary(L"dm.dll");
	if (hdllInst==NULL) {
		return NULL;
	}
	fnGCO = (pfnGCO)GetProcAddress(hdllInst, "DllGetClassObject");
	if (fnGCO != NULL)
	{
		IClassFactory* pcf = NULL;
		HRESULT hr = (fnGCO)(__uuidof(dmsoft), IID_IClassFactory, (void**)&pcf);
		if (SUCCEEDED(hr) && (pcf != NULL))
		{
			hr = pcf->CreateInstance(NULL, __uuidof(Idmsoft), (void**)&m_dm);
			if ((SUCCEEDED(hr) && (m_dm != NULL)) == FALSE)
				return NULL;
		}
		pcf->Release();
	}
	return m_dm;
};