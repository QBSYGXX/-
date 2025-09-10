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
	void addPerson();//����˺�
	void showPerson();//�鿴�˺�
	void showComputer();//�鿴������Ϣ
	//���ԤԼ��¼
	void clearFile();	
	void initVector();//��ʼ������
	vector<Student>vStu;
	vector<Teacher>vTea;
	vector<computerRoom>vCom;//��������
	bool checkRepaet(int id, int type);//����ظ�
};