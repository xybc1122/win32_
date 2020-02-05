#pragma once
/* ====================================================
* Description: �ṩCreateProcess()ִ��
* ���ͨ�������ܵ���ȡ�ķ�װ
==================================================== */

#ifndef __CMD_HANDLER_H__
#define __CMD_HANDLER_H__

#include <Windows.h>
#include<vector>
#include <tchar.h>
#include<iostream>
using namespace std;
/* buffer����󳤶� */
#define PIPE_BUFFER_SIZE 1024

/* ������� */
typedef struct _CHCmdParam CHCmdParam;

struct _CHCmdParam
{
	/* ��ʼ��Ϊ sizeof(CommandParam) */
	int iSize;

	/* �ⲿ�������Ҫ��������Ϊ-1, �ṩ���ⲿʹ��
	*/
	int iCommand;

	/* ��ʱʱ�䣬��λ�� */
	int iTimeOut;

	/* ������Ҫִ�е����� */
	TCHAR szCommand[MAX_PATH];

	/* �û����� */
	void* pUserData;
};

class CCmdHandler
{
private:
	BOOL m_bInit;
	STARTUPINFO m_startupInfo;
	PROCESS_INFORMATION m_processInfo;
	SECURITY_ATTRIBUTES m_saOutPipe;
	DWORD m_dwErrorCode;
	HANDLE m_hPipeRead;
	HANDLE m_hPipeWrite;
	CHCmdParam m_CommandParam;
	TCHAR m_szReadBuffer[PIPE_BUFFER_SIZE];
	TCHAR m_szWriteBuffer[PIPE_BUFFER_SIZE];
	HRESULT ExecuteCmdWait();
public:
	char m_szPipeOut[PIPE_BUFFER_SIZE];
	CCmdHandler();
	~CCmdHandler();
	/*
	* ��ʼ���ӿڣ���������ӿ�֮ǰ����
	* �ɹ�����S_OK
	*/
	HRESULT Initalize();
	/*
	* �����ӿ�
	*/
	HRESULT Finish();
	/*
	* ִ������ӿڣ��ӿڵ��óɹ�����S_OK
	* param[in] pCommmandParam: ָ��һ��CHCmdParam��������ṹ��ָ��
	*/
	HRESULT HandleCommand(CHCmdParam* pCommmandParam);
	/*
	* ���ش����룬���ڲ��ӿڵ���ʧ�ܺ����ʲô����
	*/
	DWORD GetErrorCode() { return m_dwErrorCode; }
};

#endif // !__CMD_HANDLER_H__


