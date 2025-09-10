#include"manager.h"
#include<fstream>
#include"identity.h"
#include"globalfile.h"
#include"student.h"
#include"teacher.h"
#include<algorithm>
void printStudent(const Student& s)
{
	cout << "学号：" << s.m_id << " " << "姓名：" << s.m_name << " " << "密码：" << s.m_Pwd << endl;
}
void printTeacher(const Teacher& t)
{
	cout << "职工号：" << t.m_EmpId << " " << "姓名：" << t.m_name << " " << "密码：" << t.m_Pwd << endl;
}
Manager::Manager(){}
Manager::Manager(const string& name, const string& pwd)
{
	this->m_name = name;
	this->m_Pwd = pwd;
	//初始化容器
	this->initVector();
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
void Manager::addPerson()
{
	cout << "请输入添加账号的类型" << endl;
	cout << "1、添加学生" << endl;
	cout << "2、添加老师" << endl;
	string filename;
	string tip;
	ofstream ofs;
	int select = 0;
	string errorTip;//重复错误提示
	cin >> select;
	if (select == 1)
	{
		filename = STUDENT_FILE;
		tip = "请输入学号：";
		errorTip = "学号重复，请重新输入";
	}
	else
	{
		filename = TEACHER_FILE;
		tip = "请输入职工编号：";
		errorTip = "职工号重复，请重新输入";
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
		if (ret)//有重复
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}
	cout << "请输入姓名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> pwd;
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功" << endl;
	system("pause");
	system("cls");
	ofs.close();
	this->initVector();//调用初始化容器接口，从新获取文件中的数据
}
void Manager::showPerson()
{
	cout << "请选择查看内容：" << endl;
	cout << "1、查看所有学生" << endl;
	cout << "2、查看所有老师" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		cout << "所有学生信息如下：" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else if (select == 2)
	{
		cout << "所有教师信息如下：" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}

void Manager::showComputer()
{
	cout << "机房信息如下：" << endl;
	for (vector<computerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "机房编号：" << it->m_Comid << "机房最大容量：" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}

void Manager::clearFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);//清空预约记录
	ofs.close();
	cout << "清空成功！" << endl;
	system("pause");
	system("cls");
}
void Manager::initVector()
{
	//读取学生文件中信息
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}
	vStu.clear();
	vTea.clear();
	Student s;
	while (ifs >> s.m_id && ifs >> s.m_name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	cout << "当前学生数量为：" << vStu.size() << endl;
	ifs.close();//学生初始化
	ifs.open(TEACHER_FILE, ios::in);
	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_name && ifs >> t.m_Pwd )
	{
		vTea.push_back(t);
	}
	cout << "当前教师数量为：" << vTea.size() << endl;
	ifs.close();//教师初始化
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
	cout << "欢迎管理员：" << this->m_name << endl;
	cout << "\t\t--------------------------\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t|        1.添加账号      |\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t|        2.查看账号      |\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t|        3.查看机房      |\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t|        4.清空预约      |\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t|        0.注销登录      |\n";
	cout << "\t\t|                        |\n";
	cout << "\t\t--------------------------\n";
	cout << "请输入您的选择：";
}