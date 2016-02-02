
#pragma once
#include"studentSys.h"
#include"gui.h"
#include"Gobals.h"
#include"SysModule.h"

//#define BUG
#define MOUT(x) MessageBox(0, x, 0, 0)

extern map<string, GUIwindow*> GUIma;


// gobal��
extern UserTable *g_userTable;
extern CourseTable *g_courseTable;
extern SelectCourseTable *g_selectCourseTable;

//gobalģ��
extern LogModule *logModule;
extern UserMoudle *userModule;
extern SelectCourseModule *selectModule;
extern ScoreModule *scoreModule;

extern User* curUser;    // ��ǰ����

extern ofstream fout;

extern queue<GUIwindow*> controlToDeleteq;	  // Ҫɾ����ʱ�ؼ���GUI���ڶ���
extern map<string, int> textboxmap;						// ��̬���ص�textbox���±꣬ ���ڶ�̬ɾ��textbox

extern vector<StudentInfo*>  StudentToDelete; // ��Ų���Ҫɾ����ѧ��
extern vector<TeacherInfo*> TeacherToDelete;
extern vector<CourseInfo*> CourseToDelete;		// ���Ҫɾ���Ŀγ�

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
