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
	// 记录容器 key ----记录的条数 value ----具体记录的键值对信息
	map<int, map<string, string>>m_orderData;
	//预约记录条数
	int m_size;
};
