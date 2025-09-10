#pragma once
#include<iostream>
#include<string>
using namespace std;
//身份抽象类
class Identity
{
public:
	//操作菜单
	virtual void operMenu() = 0;
	Identity():m_name(""), m_Pwd("") {}
	string m_name;
	string m_Pwd;//密码
};