#include<iostream>
#include <vector>
#include <Windows.h>
using namespace std;



vector<string> Split(string str, string pattern)
{
	string::size_type pos;
	vector<string> list;

	str += pattern;//扩展字符串以方便操作
	unsigned int size = str.size();

	for (unsigned int i = 0; i < size; i++) {
		pos = str.find(pattern, i);
		if (pos < size) {
			std::string s = str.substr(i, pos - i);
			list.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return list;
}




wstring String2wstring(string &str)
{
	wstring result;
	//获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];
	//多字节编码转换成宽字节编码  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';             //添加字符串结尾  
	//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}