
#pragma once
#include"studentSys.h"
#include"gui.h"
#include"Gobals.h"
#include"SysModule.h"

//#define BUG
#define MOUT(x) MessageBox(0, x, 0, 0)

extern map<string, GUIwindow*> GUIma;


// gobal表
extern UserTable *g_userTable;
extern CourseTable *g_courseTable;
extern SelectCourseTable *g_selectCourseTable;

//gobal模块
extern LogModule *logModule;
extern UserMoudle *userModule;
extern SelectCourseModule *selectModule;
extern ScoreModule *scoreModule;

extern User* curUser;    // 当前界面

extern ofstream fout;

extern queue<GUIwindow*> controlToDeleteq;	  // 要删除临时控件的GUI窗口队列
extern map<string, int> textboxmap;						// 动态加载的textbox的下标， 用于动态删除textbox

extern vector<StudentInfo*>  StudentToDelete; // 存放查找要删除的学生
extern vector<TeacherInfo*> TeacherToDelete;
extern vector<CourseInfo*> CourseToDelete;		// 存放要删除的课程

class studentApp
{
private:
public:

	void load();
	void init();
	void update();
	void render();
	void clear();
	studentApp() {
		//init();
	}
	~studentApp() {
		clear();
	}
};



void LinkPage(GUIwindow *u, GUIwindow *v);
void clearTextboxOfGUI(GUIwindow *);
typedef void (PageFunc)(GUIwindow*);
PageFunc LoginPage;													// 
PageFunc AdminPage;													//
PageFunc UserManagePage;										//
PageFunc StudentListPage;
PageFunc TeacherListPage;
PageFunc AddUserPage;												
PageFunc DeleteUserPage;										
PageFunc CourseManagePage;									//
PageFunc AddCoursePage;
PageFunc DeleteCoursePage;
PageFunc StudentPage;
PageFunc StudentInfoPage;
PageFunc CourseTablePage;
PageFunc StudentScorePage;
PageFunc SelectCoursePage;
PageFunc SelectedCoursePage;
PageFunc TeacherPage;
PageFunc TeacherInfoPage;
PageFunc TeacherUpdateScorePage;
PageFunc TeacherCourseTablePage;
