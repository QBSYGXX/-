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
	virtual void operMenu()override;//�˵�����
	void applyOeder();//����ԤԼ
	void showMyOrder();//�鿴�ҵ�ԤԼ
	void showAllOrder();//�鿴����ԤԼ
	void cancelOrder();//ȡ��ԤԼ
	int m_id;
	vector<computerRoom>vCom;//��������
};