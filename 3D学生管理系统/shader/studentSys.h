


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

typedef map<string, AdminInfo*>	   AdminTable;							// 管理员表,  账号-user
typedef map<string, StudentInfo*> StudentTable;					// 学生表， 放所有学生  id-user
typedef map<string, TeacherInfo*> TeacherTable;					// 教师表， 方所有学生	id-user
class CourseInfo;																				// 课程信息
class SelectCourseInfo;																	// 单个选课信息
class UserTable;																				// 用户表
class CourseTable;																			// 课程表
class SelectCourseTable;																// 选课表
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

// 学生信息
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

// 老师信息
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

// 课程信息
class CourseInfo
{
public:
	string courseID, courseName, TeacherName, TeacherID;
	string classTime;
};

// 选课信息
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



// ------------------- 各种表 -----------------------


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
	SysMSG AddUser(User *user);					// 输入姓名，账号，密码  学生sex,class 老师sex
	SysMSG DeleteUser(User  *user);			// 输入id
	SysMSG QueryUser(User *user);				
	User* CheckAccount(User *user);		// 登录  输入账号，密码，用户类型
	User* FindUser(User *user);					// 输入用户类型，id或姓名

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
	SysMSG AddCourse(CourseInfo *);					// 输入课程名，老师id, 上课时间
	SysMSG DeleteCourse(CourseInfo *);			// 输入课程id
	CourseInfo* FindCourse(CourseInfo *);		// 输入课程id 或课程号
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
	SysMSG AddInfo(SelectCourseInfo *);							// 输入学生id, 课程id
	SysMSG DeleteInfo(SelectCourseInfo *);					// 输入学生id, 课程id
	SysMSG DeleteInfoOfStudent(StudentInfo *);			// 输入学生id
	SysMSG DeleteInfoOfCourse(CourseInfo*);					// 输入课程Id
	SelectCourseInfo* FinfSelectInfo(SelectCourseInfo*);		// 输入学生Id，课程id
	vector<SelectCourseInfo*> * getSelectCourseTable();
};

class  Kebiao
{
private:
	vector<CourseInfo*> *m_kebiao;
public:
	Kebiao();
	~Kebiao();
	SysMSG AddCourse(CourseInfo*);						// 输入整个课程信息
	SysMSG DeleteCourse(CourseInfo*);					// 输入课程Id
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