#pragma once
#include<iostream>
#include<string>
using namespace std;
//��ݳ�����
class Identity
{
public:
	//�����˵�
	virtual void operMenu() = 0;
	Identity():m_name(""), m_Pwd("") {}
	string m_name;
	string m_Pwd;//����
};