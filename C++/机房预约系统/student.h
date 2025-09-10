#pragma once
#include"identity.h"
#include<string>
#include<vector>
#include"computerRoom.h"
class Student:public Identity
{
public:
	Student();
	Student(const int& id,const string& name,const string& pwd);
	virtual void operMenu()override;//菜单界面
	void applyOeder();//申请预约
	void showMyOrder();//查看我的预约
	void showAllOrder();//查看所有预约
	void cancelOrder();//取消预约
	int m_id;
	vector<computerRoom>vCom;//机房容器
};