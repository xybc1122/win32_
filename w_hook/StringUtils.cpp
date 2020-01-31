#include<iostream>
#include <vector>
using namespace std;



vector<string> split(string str, string pattern)
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