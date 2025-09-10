#pragma once
#include"identity.h"
#include<vector>
#include<string>
#include"student.h"
#include"teacher.h"
#include"computerRoom.h"
class Manager :public Identity
{
public:
	Manager();
	Manager(const string& name, const string& pwd);
	virtual void operMenu()override;
	void addPerson();//添加账号
	void showPerson();//查看账号
	void showComputer();//查看机房信息
	//清空预约记录
	void clearFile();	
	void initVector();//初始化容器
	vector<Student>vStu;
	vector<Teacher>vTea;
	vector<computerRoom>vCom;//机房容器
	bool checkRepaet(int id, int type);//检测重复
};