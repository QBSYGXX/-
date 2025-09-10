#include"teacher.h"
#include"globalfile.h"
#include"orderFile.h"
#include<iostream>
#include<vector>
Teacher::Teacher(){}

Teacher::Teacher(const int& empid, const string& name, const string& pwd):m_EmpId(empid)
{
	this->m_name = name;
	this->m_Pwd = pwd;
}
void Teacher::vailOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "待审核的预约记录如下：" << endl;
	vector<int>v;
	int index = 0;
	for (int i = 0; i < of.m_size; i++)
	{
			if (of.m_orderData[i]["status"] == "1")
			{
				v.push_back(i);
				cout << ++index << ". ";
				cout << "预约日期：周" << of.m_orderData[i]["date"] << " ";
				cout << "时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
				cout << "学号：" << of.m_orderData[i]["stuId"] << " ";
				cout << "姓名：" << of.m_orderData[i]["stuName"] << " ";
				cout << "机房：" << of.m_orderData[i]["roomId"] << " ";
				string status = "状态：";//0取消的预约 1审核中 2已预约 -1预约失败
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "审核中";
				}
				cout << status << endl;
			}
	}
	cout << "请输入审核的预约记录，0代表返回" << endl;
	int select = 0;
	int ret = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}

			else
			{
				cout << "请输入审核结果" << endl;
				cout << "1、通过" << endl;
				cout << "2、不通过" << endl;
				cin >> ret;
				if (ret == 1)
				{
					of.m_orderData[v[select - 1]]["status"] = "2";
				}
				else
				{
					of.m_orderData[v[select - 1]]["status"] = "-1";
				}
				of.updateOrder();
				cout << "审核完毕！" << endl;
				break;
			}
		}
		cout << "输入错误，请重新输入" << endl;
	}
	system("pause");
	system("cls");
}
void Teacher::showAllOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_size; i++)
	{
		cout << i + 1 << "、";
		cout << "预约日期：周" << of.m_orderData[i]["date"] << " ";
		cout << "时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
		cout << "学号：" << of.m_orderData[i]["stuId"] << " ";
		cout << "姓名：" << of.m_orderData[i]["stuName"] << " ";
		cout << "机房：" << of.m_orderData[i]["roomId"] << " ";
		string status = "状态：";//0取消的预约 1审核中 2已预约 -1预约失败
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "已预约";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "预约失败";
		}
		else
		{
			status += "取消预约";
		}
		cout << status << endl;

	}
	system("pause");
	system("cls");
}
void Teacher::operMenu()
{
	cout << "欢迎教师：" << this->m_name << endl;
	cout << "\t\t--------------------------\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t|        1.查看所有预约  |\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t|        2.审核预约      |\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t|        0.注销登录      |\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t--------------------------\n";
	cout << "请输入您的选择：";
}