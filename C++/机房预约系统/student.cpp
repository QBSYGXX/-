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
	//��ȡ������Ϣ
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	computerRoom c;
	while (ifs >> c.m_Comid && ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	}
	cout << "��ǰ��������Ϊ��" << vCom.size() << endl;
	ifs.close();
}


void Student::operMenu()
{
	cout << "��ӭѧ������" << this->m_name << "��¼��" << endl;
	cout << "\t\t--------------------------\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t|        1.����ԤԼ      |\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t|        2.�鿴�ҵ�ԤԼ  |\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t|        3.�鿴����ԤԼ  |\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t|        4.ȡ��ԤԼ      |\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t|        0.ע����¼      |\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t--------------------------\n";
	cout << "����������ѡ��";
}

void Student::applyOeder()
{
	cout << "��������ʱ��Ϊ��һ�����壡" << endl;
	cout << "����������ԤԼ��ʱ�䣺" << endl;
	cout << "1����һ" << endl;
	cout << "2���ܶ�" << endl;
	cout << "3������" << endl;
	cout << "4������" << endl;
	cout << "5������" << endl;
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
		cout << "������������������" << endl;
	}
	cout << "����������ԤԼ��ʱ��Σ�" << endl;
	cout << "1������" << endl;
	cout << "2������" << endl;
	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "������������������" << endl;
	}
	cout << "��ѡ�������" << endl;
	cout << "1�Ż���������" << vCom[0].m_MaxNum << endl;
	cout << "2�Ż���������" << vCom[1].m_MaxNum << endl;
	cout << "3�Ż���������" << vCom[2].m_MaxNum << endl;
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "������������������" << endl;
	}
	cout << "ԤԼ�ɹ��������" << endl;
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
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_size; i++)
	{
		if (stoi(of.m_orderData[i]["stuId"]) == this->m_id)
		/*if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_id)*///��stringת����int
		{
			cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"]<<" ";
			cout << "ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����")<<" ";
			cout << "������" << of.m_orderData[i]["roomId"]<<" ";
			string status = "״̬��";//0ȡ����ԤԼ 1����� 2��ԤԼ -1ԤԼʧ��
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "�����";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "��ԤԼ";
			}
			else if (of.m_orderData[i]["status"] == "-1")
			{
				status += "ԤԼʧ��";
			}
			else
			{
				status += "ȡ��ԤԼ";
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
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_size; i++)
	{
		cout << i + 1 << "��";
		cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"] << " ";
		cout << "ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����") << " ";
		cout << "ѧ�ţ�" << of.m_orderData[i]["stuId"] << " ";
		cout << "������" << of.m_orderData[i]["stuName"] << " ";
		cout << "������" << of.m_orderData[i]["roomId"] << " ";
		string status = "״̬��";//0ȡ����ԤԼ 1����� 2��ԤԼ -1ԤԼʧ��
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "�����";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "��ԤԼ";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "ԤԼʧ��";
		}
		else
		{
			status += "ȡ��ԤԼ";
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
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "��˻�ԤԼ�ɹ��ļ�¼����ȡ����������ȡ���ļ�¼" << endl;
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
				cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"] << " ";
				cout << "ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����") << " ";
				cout << "������" << of.m_orderData[i]["roomId"] << " ";
				string status = "״̬��";//0ȡ����ԤԼ 1����� 2��ԤԼ -1ԤԼʧ��
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "�����";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "��ԤԼ";
				}
				else if (of.m_orderData[i]["status"] == "-1")
				{
					status += "ԤԼʧ��";
				}
				else
				{
					status += "ȡ��ԤԼ";
				}
				cout << status << endl;
			}
		}
	}
	cout << "������ȡ���ļ�¼��0������" << endl;
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
			cout << "��ȡ��ԤԼ" << endl;
			break;
		}
		cout << "������������������" << endl;
	}
	system("pause");
	system("cls");
}




