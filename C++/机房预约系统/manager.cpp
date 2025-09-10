#include"manager.h"
#include<fstream>
#include"identity.h"
#include"globalfile.h"
#include"student.h"
#include"teacher.h"
#include<algorithm>
void printStudent(const Student& s)
{
	cout << "ѧ�ţ�" << s.m_id << " " << "������" << s.m_name << " " << "���룺" << s.m_Pwd << endl;
}
void printTeacher(const Teacher& t)
{
	cout << "ְ���ţ�" << t.m_EmpId << " " << "������" << t.m_name << " " << "���룺" << t.m_Pwd << endl;
}
Manager::Manager(){}
Manager::Manager(const string& name, const string& pwd)
{
	this->m_name = name;
	this->m_Pwd = pwd;
	//��ʼ������
	this->initVector();
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
void Manager::addPerson()
{
	cout << "����������˺ŵ�����" << endl;
	cout << "1�����ѧ��" << endl;
	cout << "2�������ʦ" << endl;
	string filename;
	string tip;
	ofstream ofs;
	int select = 0;
	string errorTip;//�ظ�������ʾ
	cin >> select;
	if (select == 1)
	{
		filename = STUDENT_FILE;
		tip = "������ѧ�ţ�";
		errorTip = "ѧ���ظ�������������";
	}
	else
	{
		filename = TEACHER_FILE;
		tip = "������ְ����ţ�";
		errorTip = "ְ�����ظ�������������";
	}
	ofs.open(filename, ios::out | ios::app);
	int id;
	string name;
	string pwd;
	cout << tip << endl;
	while (true)
	{
		cin >> id;
		bool ret = this->checkRepaet(id, 1);
		if (ret)//���ظ�
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}
	cout << "������������" << endl;
	cin >> name;
	cout << "���������룺" << endl;
	cin >> pwd;
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "��ӳɹ�" << endl;
	system("pause");
	system("cls");
	ofs.close();
	this->initVector();//���ó�ʼ�������ӿڣ����»�ȡ�ļ��е�����
}
void Manager::showPerson()
{
	cout << "��ѡ��鿴���ݣ�" << endl;
	cout << "1���鿴����ѧ��" << endl;
	cout << "2���鿴������ʦ" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		cout << "����ѧ����Ϣ���£�" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else if (select == 2)
	{
		cout << "���н�ʦ��Ϣ���£�" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}

void Manager::showComputer()
{
	cout << "������Ϣ���£�" << endl;
	for (vector<computerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "������ţ�" << it->m_Comid << "�������������" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}

void Manager::clearFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);//���ԤԼ��¼
	ofs.close();
	cout << "��ճɹ���" << endl;
	system("pause");
	system("cls");
}
void Manager::initVector()
{
	//��ȡѧ���ļ�����Ϣ
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}
	vStu.clear();
	vTea.clear();
	Student s;
	while (ifs >> s.m_id && ifs >> s.m_name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	cout << "��ǰѧ������Ϊ��" << vStu.size() << endl;
	ifs.close();//ѧ����ʼ��
	ifs.open(TEACHER_FILE, ios::in);
	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_name && ifs >> t.m_Pwd )
	{
		vTea.push_back(t);
	}
	cout << "��ǰ��ʦ����Ϊ��" << vTea.size() << endl;
	ifs.close();//��ʦ��ʼ��
}
bool Manager::checkRepaet(int id, int type)
{
	if (type == 1)
	{
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->m_id)
			{
				return true;
			}
		}
	}
	else
	{
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}
		}
	}
	return false;
}
void Manager::operMenu()
{
	cout << "��ӭ����Ա��" << this->m_name << endl;
	cout << "\t\t--------------------------\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t|        1.����˺�      |\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t|        2.�鿴�˺�      |\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t|        3.�鿴����      |\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t|        4.���ԤԼ      |\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t|        0.ע����¼      |\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t--------------------------\n";
	cout << "����������ѡ��";
}