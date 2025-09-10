#include<iostream>
#include"globalfile.h"
#include"identity.h"
#include"student.h"
#include"teacher.h"
#include"manager.h"
#include<fstream>
#include<string>
using namespace std;
//教师菜单
void teacherMenu(Identity* teacher)
{
	while (true)
	{
		teacher->operMenu();
		Teacher* tea = (Teacher*)teacher;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			//查看所有预约
			tea->showAllOrder();
		}
		else if (select == 2)
		{
			//审核预约
			tea->vailOrder();
		}
		else
		{
			delete teacher;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
//学生菜单
void studentMenu(Identity*& student)
{
	while (true)
	{
		//学生菜单
		student->operMenu();

		Student* stu = (Student*)student;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			stu->applyOeder();//申请预约
		}
		else if (select == 2)
		{
			stu->showMyOrder();
		}
		else if (select == 3)
		{
			stu->showAllOrder();//查看所有预约
		}
		else if (select == 4)
		{
			stu->cancelOrder();//取消预约
		}
		else
		{
			delete student;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
//进入管理员子菜单界面
void managerMenu(Identity*& manager)
{
	while (true)
	{
		manager->operMenu();
		//将父类指针强制转为子类指针，调用子类里其他接口
		Manager* man = (Manager*)manager;
		int select = 0;
		//接受用户选项
		cin >> select;
		if (select == 1)//添加账号
		{
			cout << "添加账号" << endl;
			man->addPerson();
		}
		else if (select == 2)//查看账号
		{
			cout << "查看账号" << endl;
			man->showPerson();
		}
		else if (select == 3)//查看机房
		{
			cout << "查看机房" << endl;
			man->showComputer();
		}
		else if (select == 4)//清空预约
		{
			cout << "清空预约" << endl;
			man->clearFile();
		}
		else
		{
			//注销模块
			delete manager;//销毁掉堆区对象
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
//登录功能
void LoginIn(const string& filename, int type)
{
	Identity* person = nullptr;
	ifstream ifs;
	ifs.open(filename, ios::in);
	//文件不存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		system("pause");
		system("cls");
		return;
	}
	int id = 0;
	string name;
	string pwd;
	if (type == 1)
	{
		cout << "输入学号：" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "输入职工号：" << endl;
		cin >> id;
	}
	cout << "输入用户名：" << endl;
	cin >> name;
	cout << "输入密码：" << endl;
	cin >> pwd;
	if (type == 1)
	{
		//学生登录认证
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "学生验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				//进入学生身份子菜单
				studentMenu(person);
				return;
			}
		}
	}
	else if(type == 2)
	{
		//教师登录认证
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "教师验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//进入教师身份子菜单
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//管理员登录认证
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd)
		{
			if (name == fName && pwd == fPwd)
			{
				cout << "验证登录成功！" << endl;
				//登录成功后，按任意键进入管理员界面
				system("pause");
				system("cls");
				//创建管理员对象
				person = new Manager(name, pwd);
				managerMenu(person);
				return;
			}
		}
	}
	cout << "验证登陆失败！" << endl;
	system("pause");
	system("cls");
	return;
}
int main()
{
	while (true)
	{
		cout << "======================= 欢迎来到机房预约系统 ======================" << endl;
		cout << endl << "请输入您的身份：" << endl;
		cout << "\t\t--------------------------\n";
		cout << "\t\t|                        |\n";
		cout << "\t\t|        1.学生          |\n";
		cout << "\t\t|                        |\n";
		cout << "\t\t|        2.老师          |\n";
		cout << "\t\t|                        |\n";
		cout << "\t\t|        3.管理员        |\n";
		cout << "\t\t|                        |\n";
		cout << "\t\t|        0.退  出        |\n";
		cout << "\t\t|                        |\n";
		cout << "\t\t--------------------------\n";
		cout << "请输入您的选择：";
		int select;
		cin >> select;
		switch (select)
		{
		case 1://学生
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2://老师
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3://管理员
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0://退出系统
		{
			cout << "欢迎下一次使用" << endl;
			system("pause");
			return 0;
			break;
		}
		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}