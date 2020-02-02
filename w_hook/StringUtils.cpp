#include<iostream>
#include <vector>
#include <Windows.h>
using namespace std;



vector<string> Split(string str, string pattern)
{
	string::size_type pos;
	vector<string> list;

	str += pattern;//��չ�ַ����Է������
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
	//��ȡ��������С��������ռ䣬��������С���ַ�����  
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];
	//���ֽڱ���ת���ɿ��ֽڱ���  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';             //����ַ�����β  
	//ɾ��������������ֵ  
	result.append(buffer);
	delete[] buffer;
	return result;
}