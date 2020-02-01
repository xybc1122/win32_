#include<stdlib.h>
#include<iostream>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <shellapi.h>
#include "CmdHandler.h"
#include<iostream>
#include<vector>
#include "StringUtils.h"
#include<string>
#include"DnplayerOperate.h"

std::wstring lodPath = string2wstring(DnplayerOperate::getInstance().path);

void exeShellExecute(std::wstring lodPath, std::wstring exeCmd);
std::string runCmdRet(std::wstring cmd) {
	CHCmdParam cmdParam;
	CCmdHandler cmdHandler;
	HRESULT cmdResult = S_OK;

	ZeroMemory(&cmdParam, sizeof(cmdParam));
	cmdParam.iSize = sizeof(CHCmdParam);
	_tcscpy_s(cmdParam.szCommand, cmd.c_str());
	cmdParam.iTimeOut = 3000;

	cmdResult = cmdHandler.Initalize();
	if (cmdResult != S_OK)
	{
		//printf("cmd handler ��ʼ��ʧ��\n");


	}
	cmdResult = cmdHandler.HandleCommand(&cmdParam);
	if (cmdResult != S_OK)
	{
		//printf("cmd handler ִ������ӿڵ���ʧ��\n");

	}
	cmdHandler.Finish();

	return cmdHandler.m_szPipeOut;
}


void runCmdEmulator(int size) {
	for (int i = 0; i < size;i++) {
		//ƴ��cmd ����
		std::wstring exeCmd = DnplayerOperate::getInstance().startDnPlayer(i);
		exeShellExecute(lodPath, exeCmd);
	}

}

/**
����ָ��app
**/
void runCmdRunApp(std::wstring cmd) {
	exeShellExecute(lodPath, cmd);
}



void exeShellExecute(std::wstring lodPath, std::wstring exeCmd) {
	DWORD ret = (DWORD)ShellExecute(NULL, L"open", (LPCWSTR)lodPath.c_str(), exeCmd.c_str(), NULL, SW_HIDE);
	if (ret <= 32) {
		::MessageBox(NULL, L"����ʧ��", L"error", MB_OK);
	}

}


