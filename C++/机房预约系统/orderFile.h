#pragma once
#include<iostream>
#include<map>
#include"globalfile.h"
#include<string>
using namespace std;
class OrderFile
{
public:
	OrderFile();
	void updateOrder();
	// ��¼���� key ----��¼������ value ----�����¼�ļ�ֵ����Ϣ
	map<int, map<string, string>>m_orderData;
	//ԤԼ��¼����
	int m_size;
};
