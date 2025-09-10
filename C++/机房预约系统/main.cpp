#include<iostream>
#include"globalfile.h"
#include"identity.h"
#include"student.h"
#include"teacher.h"
#include"manager.h"
#include<fstream>
#include<string>
using namespace std;
//��ʦ�˵�
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
			//�鿴����ԤԼ
			tea->showAllOrder();
		}
		else if (select == 2)
		{
			//���ԤԼ
			tea->vailOrder();
		}
		else
		{
			delete teacher;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
//ѧ���˵�
void studentMenu(Identity*& student)
{
	while (true)
	{
		//ѧ���˵�
		student->operMenu();

		Student* stu = (Student*)student;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			stu->applyOeder();//����ԤԼ
		}
		else if (select == 2)
		{
			stu->showMyOrder();
		}
		else if (select == 3)
		{
			stu->showAllOrder();//�鿴����ԤԼ
		}
		else if (select == 4)
		{
			stu->cancelOrder();//ȡ��ԤԼ
		}
		else
		{
			delete student;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
//�������Ա�Ӳ˵�����
void managerMenu(Identity*& manager)
{
	while (true)
	{
		manager->operMenu();
		//������ָ��ǿ��תΪ����ָ�룬���������������ӿ�
		Manager* man = (Manager*)manager;
		int select = 0;
		//�����û�ѡ��
		cin >> select;
		if (select == 1)//����˺�
		{
			cout << "����˺�" << endl;
			man->addPerson();
		}
		else if (select == 2)//�鿴�˺�
		{
			cout << "�鿴�˺�" << endl;
			man->showPerson();
		}
		else if (select == 3)//�鿴����
		{
			cout << "�鿴����" << endl;
			man->showComputer();
		}
		else if (select == 4)//���ԤԼ
		{
			cout << "���ԤԼ" << endl;
			man->clearFile();
		}
		else
		{
			//ע��ģ��
			delete manager;//���ٵ���������
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
//��¼����
void LoginIn(const string& filename, int type)
{
	Identity* person = nullptr;
	ifstream ifs;
	ifs.open(filename, ios::in);
	//�ļ�������
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
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
		cout << "����ѧ�ţ�" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "����ְ���ţ�" << endl;
		cin >> id;
	}
	cout << "�����û�����" << endl;
	cin >> name;
	cout << "�������룺" << endl;
	cin >> pwd;
	if (type == 1)
	{
		//ѧ����¼��֤
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "ѧ����֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				//����ѧ������Ӳ˵�
				studentMenu(person);
				return;
			}
		}
	}
	else if(type == 2)
	{
		//��ʦ��¼��֤
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "��ʦ��֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//�����ʦ����Ӳ˵�
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//����Ա��¼��֤
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd)
		{
			if (name == fName && pwd == fPwd)
			{
				cout << "��֤��¼�ɹ���" << endl;
				//��¼�ɹ��󣬰�������������Ա����
				system("pause");
				system("cls");
				//��������Ա����
				person = new Manager(name, pwd);
				managerMenu(person);
				return;
			}
		}
	}
	cout << "��֤��½ʧ�ܣ�" << endl;
	system("pause");
	system("cls");
	return;
}
int main()
{
	while (true)
	{
		cout << "======================= ��ӭ��������ԤԼϵͳ ======================" << endl;
		cout << endl << "������������ݣ�" << endl;
		cout << "\t\t--------------------------\n";
		cout << "\t\t|                        |\n";
		cout << "\t\t|        1.ѧ��          |\n";
		cout << "\t\t|                        |\n";
		cout << "\t\t|        2.��ʦ          |\n";
		cout << "\t\t|                        |\n";
		cout << "\t\t|        3.����Ա        |\n";
		cout << "\t\t|                        |\n";
		cout << "\t\t|        0.��  ��        |\n";
		cout << "\t\t|                        |\n";
		cout << "\t\t--------------------------\n";
		cout << "����������ѡ��";
		int select;
		cin >> select;
		switch (select)
		{
		case 1://ѧ��
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2://��ʦ
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3://����Ա
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0://�˳�ϵͳ
		{
			cout << "��ӭ��һ��ʹ��" << endl;
			system("pause");
			return 0;
			break;
		}
		default:
			cout << "��������������ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}