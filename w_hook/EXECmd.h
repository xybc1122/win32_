#include<iostream>

/** 
ͨ��CreateProcess ��ִ��cmd  ���Ի�÷��ص�str����
**/
std::string runCmdRet(std::wstring cmd);

/**
ͨ��ShellExecute ִ��cmd���� û�з���ֵ 
resultStr:�ָ�str �����ж�ִ�д���
path:·�� 
cmd:���� 
**/
void runCmd(int size, std::wstring path, std::wstring cmd);