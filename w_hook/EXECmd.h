#pragma once
#include<iostream>

/** 
通过CreateProcess 来执行cmd  可以获得返回的str参数
**/
std::string RunCmdRet(std::wstring cmd);

/**
执行模拟器
**/
void RunCmdEmulator(int size);


/**
启动指定app
**/
void RunCmdRunApp(std::wstring cmd);