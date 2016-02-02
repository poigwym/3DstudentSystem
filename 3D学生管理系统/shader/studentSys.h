


#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<stack>
#include<cmath>
#include<iomanip>
#include<set>
#include<map>
#include<utility>
#include<fstream>
#include<cassert>

using namespace std;

//extern ofstream fout;




enum UserType
{
	User_admin,
	User_student,
	User_teacher
};

class User;					
class StudentInfo;
class TeacherInfo;
class AdminInfo;

typedef map<string, AdminInfo*>	   AdminTable;							// ����Ա��,  �˺�-user
typedef map<string, StudentInfo*> StudentTable;					// ѧ���� ������ѧ��  id-user
typedef map<string, TeacherInfo*> TeacherTable;					// ��ʦ�� ������ѧ��	id-user
class CourseInfo;																				// �γ���Ϣ
class SelectCourseInfo;																	// ����ѡ����Ϣ
class UserTable;																				// �û���
class CourseTable;																			// �γ̱�
class SelectCourseTable;																// ѡ�α�
class Kebiao;


const string msgER = "error";
const string msgOK = "ok";

class SysMSG {
public:
	bool ok;
	string m_text;
	SysMSG() {
		ok = 0;
		m_text = "";
	}
};

class User
{
public :
	UserType m_type;
	string m_account;
	string m_key;
	User() {
	}
	virtual bool isLegal() {
		return (m_type == User_admin || m_type == User_student || m_type == User_teacher) &&
			m_account.length() > 0 && m_key.length() > 0;
	}
	virtual ~User() {}
};


class AdminInfo : public User
{
public:
	string m_name, m_id;
	AdminInfo() { m_type = User_admin; }
	AdminInfo(string name) : m_name(name) {
		m_type = User_admin;
	}
	virtual bool isLegal() {
		return User::isLegal() && m_name.length() > 0 && m_id.length() > 0;
	}
	~AdminInfo() {} 
};

// ѧ����Ϣ
class StudentInfo : public User
{
public:
	string m_name, m_id, m_sex, m_class;
	Kebiao *m_kebiao;
	StudentInfo();
	StudentInfo(string name, string sex, string c);
	~StudentInfo();
	virtual bool isLegal();
	Kebiao* getKebiao() { return m_kebiao; }
	SysMSG AddCourse(CourseInfo *);
};

// ��ʦ��Ϣ
class TeacherInfo : public User
{
public:
	string m_name, m_id, m_sex;
	Kebiao *m_kebiao;
	TeacherInfo();
	TeacherInfo(string name, string sex);
	~TeacherInfo();
	virtual bool isLegal();
	Kebiao* getKebiao() { return m_kebiao; }
	SysMSG AddCorse(CourseInfo *);
};

// �γ���Ϣ
class CourseInfo
{
public:
	string courseID, courseName, TeacherName, TeacherID;
	string classTime;
};

// ѡ����Ϣ
class SelectCourseInfo
{
public:
	SelectCourseInfo() {} 
	SelectCourseInfo(string studentID, string studentName, string courseID, string courseName) :
		studentID(studentID), studentName(studentName), courseID(courseID), courseName(courseName)
	{
		score = -1;
	}
	string studentID, studentName, courseID, courseName;
	float score;
};



// ------------------- ���ֱ� -----------------------


class UserTable
{
private:
	AdminTable *m_adminTable;
	StudentTable *m_studentTable;
	TeacherTable *m_teacherTable;

	static int MAXID;

public:
	UserTable();
	~UserTable();
	AdminTable* getAdminTable();
	StudentTable* getStudentTable();
	TeacherTable* getTeacherTable();
	SysMSG AddUser(User *user);					// �����������˺ţ�����  ѧ��sex,class ��ʦsex
	SysMSG DeleteUser(User  *user);			// ����id
	SysMSG QueryUser(User *user);				
	User* CheckAccount(User *user);		// ��¼  �����˺ţ����룬�û�����
	User* FindUser(User *user);					// �����û����ͣ�id������

	// debug
	void print();
};

class CourseTable
{
private:
	static int MAXCOURSEID;
	vector<CourseInfo*> *m_courseTable;
public:
	CourseTable();
	~CourseTable();
	SysMSG AddCourse(CourseInfo *);					// ����γ�������ʦid, �Ͽ�ʱ��
	SysMSG DeleteCourse(CourseInfo *);			// ����γ�id
	CourseInfo* FindCourse(CourseInfo *);		// ����γ�id ��γ̺�
	vector<CourseInfo*> * getCourseTable();	

	// debug
	void print();
};

class SelectCourseTable
{
private:
	vector<SelectCourseInfo*> *m_selectCourseTable;
public:
	SelectCourseTable();
	~SelectCourseTable();
	SysMSG AddInfo(SelectCourseInfo *);							// ����ѧ��id, �γ�id
	SysMSG DeleteInfo(SelectCourseInfo *);					// ����ѧ��id, �γ�id
	SysMSG DeleteInfoOfStudent(StudentInfo *);			// ����ѧ��id
	SysMSG DeleteInfoOfCourse(CourseInfo*);					// ����γ�Id
	SelectCourseInfo* FinfSelectInfo(SelectCourseInfo*);		// ����ѧ��Id���γ�id
	vector<SelectCourseInfo*> * getSelectCourseTable();
};

class  Kebiao
{
private:
	vector<CourseInfo*> *m_kebiao;
public:
	Kebiao();
	~Kebiao();
	SysMSG AddCourse(CourseInfo*);						// ���������γ���Ϣ
	SysMSG DeleteCourse(CourseInfo*);					// ����γ�Id
	vector<CourseInfo*> * getKebiao();
	
	// print
	void print();
};



inline string tostring(long long num)
{
	char tmp[22];
	sprintf(tmp, "%lld", num);
	return string(tmp);
}