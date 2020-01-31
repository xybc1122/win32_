#include "pch.h"
#include "RegDm.h"
#include<iostream>
#include"ThisLoad.h"

Idmsoft* InitNewDm();



Idmsoft* init() {
	Idmsoft* m_dm =InitNewDm();
	 //�״μ���
	 if (m_dm != NULL) {
		 DWORD dw = m_dm->Reg();
		 if (dw == 1) {
			
			 return m_dm;
		 }
	 }
	 return NULL;
}


void bindWindow(Idmsoft* m_dm, int hwnd) {
	long bindResult =m_dm->BindWindow(hwnd, "gdi", "windows", "windows", 0);
	if (!bindResult) {
		::MessageBox(NULL, L"��ʧ��", _T("error"), MB_OK);
			return;
	}
	//����ǰ̨�����ģ�ⷽʽ. 
	m_dm->SetSimMode(1);
	//��궯��ģ����ʵ����,���ƶ��켣,�Լ������ʱ���. 
	m_dm->EnableRealMouse(2, 20, 30);
	//���̶���ģ����ʵ����,�����ʱ���.
	m_dm->EnableRealKeypad(1);

}



//�����µĴ�Į����
Idmsoft* InitNewDm()
{
	Idmsoft* m_dm = NULL;
	//COleVariant temp1,temp2;
	bool m_bInit = false;

	//����ֱ�Ӽ���dll�������󣬱������ע���ļ�
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