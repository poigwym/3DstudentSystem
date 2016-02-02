

#pragma once
#include"studentSys.h"

class LogModule;								// 登录模块
class AccountMoudle;						// 用户模块
class ScoreModule;							// 成绩模块
class SelectCourseModule;				// 选课模块





class LogModule
{
private:
	UserTable *g_userTable;
public:
	LogModule(UserTable *g_userTable);
	~LogModule();
	User* Login(User *);
	SysMSG Logout(User *);
};


class UserMoudle
{
private:
	UserTable *g_userTable;
	SelectCourseTable *g_selectCourseTable;
public:
	UserMoudle(UserTable *g_userTable, SelectCourseTable *g_selectCourseTable);
	~UserMoudle();
	SysMSG AddUser(User *);			// 输入姓名, 账号，密码
	SysMSG DeleteUser(User*);		// 输入id删除
	User* FindUser(User *);
	UserTable* getUserTable();	
};


class SelectCourseModule
{
private:
	UserTable *g_userTable;
	CourseTable *g_courseTable;
	SelectCourseTable *g_selectCourseTable;
public:
	SelectCourseModule(UserTable *g_userTable, CourseTable *g_courseTable, SelectCourseTable *g_selectCourseTable);
	~SelectCourseModule();
	SysMSG AddCourse(CourseInfo*);								// 输入课名，老师id,  time
	SysMSG DeleteCourse(CourseInfo*);							// 输入课程id删除
	SysMSG AddSelectCourse(SelectCourseInfo *);	  // 输入学生id, 课程id
	SysMSG DeleteSelctCourse(SelectCourseInfo *);	// 输入学生id, 课程id
	SelectCourseTable* getSelectCourseTable();
};

class ScoreModule
{
private:
	UserTable *g_userTable;
	SelectCourseTable *g_selectCourseTable;
	CourseTable *g_courseTable;
public:
	ScoreModule(UserTable *g_userTable, CourseTable *g_courseTable, SelectCourseTable *g_selectCourseTable);
	~ScoreModule();

	SelectCourseTable *getScoreTable();	
	SysMSG UpdateScore(SelectCourseInfo *sinfo);			// 修改成绩  输入学生id, 课程id 
	SysMSG FindScore(SelectCourseInfo *sinfo);				// 查找成绩 输入学生id, 课程id
};




