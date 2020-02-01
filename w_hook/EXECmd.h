#include<iostream>

/** 
通过CreateProcess 来执行cmd  可以获得返回的str参数
**/
std::string runCmdRet(std::wstring cmd);

/**
执行模拟器
**/
void runCmdEmulator(int size);


/**
启动指定app
**/
void runCmdRunApp(std::wstring cmd);