#import "dm.dll" no_namespace 
#include <iostream>
//初始化加载dm
Idmsoft* init();
//绑定窗口
void bindWindow(Idmsoft* m_dm, int hwnd);