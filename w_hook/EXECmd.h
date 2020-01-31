#include<iostream>

/** 
通过CreateProcess 来执行cmd  可以获得返回的str参数
**/
std::string runCmdRet(std::wstring cmd);

/**
通过ShellExecute 执行cmd命令 没有返回值 
resultStr:分割str 用来判断执行次数
path:路径 
cmd:命令 
**/
void runCmd(int size, std::wstring path, std::wstring cmd);