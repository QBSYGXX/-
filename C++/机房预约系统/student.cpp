#include "student.h"
#include"globalfile.h"
#include"computerRoom.h"
#include<fstream>
#include"orderFile.h"
Student::Student(){}

Student::Student(const int& id, const string& name, const string& pwd):m_id(id)
{
	this->m_name = name;
	this->m_Pwd = pwd;
	//获取机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	computerRoom c;
	while (ifs >> c.m_Comid && ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	}
	cout << "当前机房数量为：" << vCom.size() << endl;
	ifs.close();
}


void Student::operMenu()
{
	cout << "欢迎学生代表：" << this->m_name << "登录！" << endl;
	cout << "\t\t--------------------------\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t|        1.申请预约      |\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t|        2.查看我的预约  |\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t|        3.查看所有预约  |\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t|        4.取消预约      |\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t|        0.注销登录      |\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t--------------------------\n";
	cout << "请输入您的选择：";
}

void Student::applyOeder()
{
	cout << "机房开放时间为周一至周五！" << endl;
	cout << "请输入申请预约的时间：" << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;
	int date = 0;
	int interval = 0;
	int room = 0;
	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}
	cout << "请输入申请预约的时间段：" << endl;
	cout << "1、上午" << endl;
	cout << "2、下午" << endl;
	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}
	cout << "请选择机房：" << endl;
	cout << "1号机房容量：" << vCom[0].m_MaxNum << endl;
	cout << "2号机房容量：" << vCom[1].m_MaxNum << endl;
	cout << "3号机房容量：" << vCom[2].m_MaxNum << endl;
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}
	cout << "预约成功！审核中" << endl;
	ofstream ofs(ORDER_FILE, ios::app);
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_id << " ";
	ofs << "stuName:" << this->m_name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;
	ofs.close();
	system("pause");
	system("cls");
}

void Student::showMyOrder()
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
		if (stoi(of.m_orderData[i]["stuId"]) == this->m_id)
		/*if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_id)*///将string转换成int
		{
			cout << "预约日期：周" << of.m_orderData[i]["date"]<<" ";
			cout << "时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午")<<" ";
			cout << "机房：" << of.m_orderData[i]["roomId"]<<" ";
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
	}
	system("pause");
	system("cls");
}

void Student::showAllOrder()
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

void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "审核或预约成功的记录可以取消，请输入取消的记录" << endl;
	vector<int>v;
	int index = 1;
	for (int i = 0; i < of.m_size; i++)
	{
		if (stoi(of.m_orderData[i]["stuId"]) == this->m_id)
		{
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << ". ";
				cout << "预约日期：周" << of.m_orderData[i]["date"] << " ";
				cout << "时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
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
		}
	}
	cout << "请输入取消的记录，0代表返回" << endl;
	int select = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
		}
		else
		{
			of.m_orderData[v[select - 1]]["status"] = "0";
			of.updateOrder();
			cout << "已取消预约" << endl;
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}
	system("pause");
	system("cls");
}




