#include"InitDm.h"

Idmsoft* InitNewDm();
//��ʼ������dm
Idmsoft* Init() {

	Idmsoft* m_dm = InitNewDm();
	//�״μ���
	if (m_dm != NULL) {
		DWORD dw = m_dm->Reg("13515874497648d23424c2efc806842831995228f4f", "hWiqGife5r");
		if (dw == 1) {
			m_dm->SetPath("E:\\img\\");
			return m_dm;
		}
	}
	return NULL;


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
	if (hdllInst == NULL) {
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




