

#pragma once
#include"studentSys.h"

class LogModule;								// ��¼ģ��
class AccountMoudle;						// �û�ģ��
class ScoreModule;							// �ɼ�ģ��
class SelectCourseModule;				// ѡ��ģ��





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
	SysMSG AddUser(User *);			// ��������, �˺ţ�����
	SysMSG DeleteUser(User*);		// ����idɾ��
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
	SysMSG AddCourse(CourseInfo*);								// �����������ʦid,  time
	SysMSG DeleteCourse(CourseInfo*);							// ����γ�idɾ��
	SysMSG AddSelectCourse(SelectCourseInfo *);	  // ����ѧ��id, �γ�id
	SysMSG DeleteSelctCourse(SelectCourseInfo *);	// ����ѧ��id, �γ�id
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
	SysMSG UpdateScore(SelectCourseInfo *sinfo);			// �޸ĳɼ�  ����ѧ��id, �γ�id 
	SysMSG FindScore(SelectCourseInfo *sinfo);				// ���ҳɼ� ����ѧ��id, �γ�id
};




