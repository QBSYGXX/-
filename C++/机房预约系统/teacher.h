#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"identity.h"
using namespace std;

class Teacher :public Identity
{
public:
	Teacher();
	Teacher(const int& empid, const string& name, const string& pwd);
	virtual void operMenu()override;
	void showAllOrder();
	void vailOrder();//���ԤԼ
	int m_EmpId;
	
};
