
#include"StudentApp.h"



UserTable *g_userTable;
CourseTable *g_courseTable;
SelectCourseTable *g_selectCourseTable;

LogModule *logModule;
UserMoudle *userModule;
SelectCourseModule *selectModule;
ScoreModule *scoreModule;

const int RW = 150;
const int RH = 20;

ofstream fout("studentLOG.txt", ios::ate);

map<string, GUIwindow*> GUIma;
GUIwindow *curGUI;
User *curUser;
studentApp g_studentApp;
queue<GUIwindow*> controlToDeleteq;
map<string, int> textboxmap;
vector<StudentInfo*>  StudentToDelete;
vector<TeacherInfo*> TeacherToDelete;
vector<CourseInfo*> CourseToDelete;		


int curframe = 0;



char buttonfile[] = "GUIMedia/button.png";
char textfile[] = "GUIMedia/TEXT.png";


char *pageName[] = {
	"LoginPage",
	"AdminPage",
	"UserManagePage",
	"StudentListPage",
	"TeacherListPage",
	"AddUserPage",
	"DeleteUserPage",
	"CourseManagePage",
	"AddCoursePage",
	"DeleteCoursePage",
	"StudentPage",
	"StudentInfoPage",
	"CourseTablePage",
	"StudentScorePage",
	"SelectCoursePage",
	"SelectedCoursePage",
	"TeacherPage",
	"TeacherInfoPage",
	"TeacherUpdateScorePage",
	"TeacherCourseTablePage"
};


void studentApp::load()
{
	GUIma.clear();
	ifstream gin("GUIinput.txt", ios::in);
	int pageN, buttonN, textN, stextN;
	gin >> pageN;
	int i, j, k;
	for (i = 0; i < pageN; ++i)
	{
		GUIwindow *page;
		string name;
		int x, y, w, h;
		gin >> name >> x >> y >> w >> h;

		page = new GUIwindow(gdevice, x, y, w, h, name);
		GUIma[name] = page;
		gin >> buttonN;
		for (j = 0; j < buttonN; ++j)
		{
			gin >> name >> x >> y >> w >> h;
			page->AddButton(name, x, y, w, h, name, buttonfile, 0);
		}

		gin >> textN;
		for (j = 0; j < textN; ++j)
		{
			gin >> name >> x >> y >> w >> h;
			page->AddText(name, x, y, w, h, textfile);
		}

		gin >> stextN;
		for (j = 0; j < stextN; ++j)
		{
			string tx;
			gin >> name >> tx >> x >> y >> w >> h;
			if (tx == "。。")
				tx = "";
			page->AddStaticText(name, x, y, w, h, tx, textfile);
		}
	}
	gin.close();
}

void studentApp::init()
{
	
	// 初始化数据表
	g_userTable = new UserTable;
	g_courseTable = new CourseTable;
	g_selectCourseTable = new SelectCourseTable;

	// 初始化模块
	logModule = new LogModule(g_userTable);
	userModule = new UserMoudle(g_userTable, g_selectCourseTable);
	selectModule = new SelectCourseModule(g_userTable, g_courseTable, g_selectCourseTable);
	scoreModule = new ScoreModule(g_userTable, g_courseTable, g_selectCourseTable);


	// 载入页面
	load();
	// set not visable
	for (auto i = GUIma.begin(); i != GUIma.end(); ++i) {
		if (i->second)
			i->second->setVis(0);
	}
	GUIma["LoginPage"]->setVis(1);

	// 添加链接
	

	//LinkPage(GUIma["LoginPage"], GUIma["AdminPage"]);
	//LinkPage(GUIma["LoginPage"], GUIma["StudentPage"]);
	//LinkPage(GUIma["LoginPage"], GUIma["TeacherPage"]);

	LinkPage(GUIma["AdminPage"], GUIma["UserManagePage"]);
	LinkPage(GUIma["AdminPage"], GUIma["CourseManagePage"]);

	LinkPage(GUIma["UserManagePage"], GUIma["StudentListPage"]);
	LinkPage(GUIma["UserManagePage"], GUIma["TeacherListPage"]);
	LinkPage(GUIma["UserManagePage"], GUIma["AddUserPage"]);
	LinkPage(GUIma["UserManagePage"], GUIma["DeleteUserPage"]);

	LinkPage(GUIma["CourseManagePage"], GUIma["DeleteCoursePage"]);
	LinkPage(GUIma["CourseManagePage"], GUIma["AddCoursePage"]);

	LinkPage(GUIma["StudentPage"], GUIma["StudentInfoPage"]);
	LinkPage(GUIma["StudentPage"], GUIma["CourseTablePage"]);
	LinkPage(GUIma["StudentPage"], GUIma["StudentScorePage"]);
	LinkPage(GUIma["StudentPage"], GUIma["SelectCoursePage"]);
	LinkPage(GUIma["StudentPage"], GUIma["SelectedCoursePage"]);
	
	LinkPage(GUIma["TeacherPage"], GUIma["TeacherInfoPage"]);
	LinkPage(GUIma["TeacherPage"], GUIma["TeacherUpdateScorePage"]);
	LinkPage(GUIma["TeacherPage"], GUIma["TeacherCourseTablePage"]);


	// 添加函数指针
	GUIma["LoginPage"]->AddEvent(LoginPage);
	GUIma["AdminPage"]->AddEvent(AdminPage);
	GUIma["UserManagePage"]->AddEvent(UserManagePage);
	GUIma["StudentListPage"]->AddEvent(StudentListPage);
	GUIma["TeacherListPage"]->AddEvent(TeacherListPage);
	GUIma["AddUserPage"]->AddEvent(AddUserPage);
	GUIma["DeleteUserPage"]->AddEvent(DeleteUserPage);
	GUIma["CourseManagePage"]->AddEvent(CourseManagePage);
	GUIma["AddCoursePage"]->AddEvent(AddCoursePage);
	GUIma["DeleteCoursePage"]->AddEvent(DeleteCoursePage);
	GUIma["StudentPage"]->AddEvent(StudentPage);
	GUIma["StudentInfoPage"]->AddEvent(StudentInfoPage);
	GUIma["CourseTablePage"]->AddEvent(CourseTablePage);
	GUIma["StudentScorePage"]->AddEvent(StudentScorePage);
	GUIma["SelectCoursePage"]->AddEvent(SelectCoursePage);
	GUIma["SelectedCoursePage"]->AddEvent(SelectedCoursePage);
	GUIma["TeacherPage"]->AddEvent(TeacherPage);
	GUIma["TeacherInfoPage"]->AddEvent(TeacherInfoPage);
	GUIma["TeacherUpdateScorePage"]->AddEvent(TeacherUpdateScorePage);
	GUIma["TeacherCourseTablePage"]->AddEvent(TeacherCourseTablePage);


	// 起始页面 LoginPage
	curGUI = GUIma["LoginPage"];

	clearTextboxOfGUI(curGUI);

	AdminInfo ad;
	ad.m_name = "admin";
	ad.m_account = "admin";
	ad.m_key = "123";
	SysMSG msg = userModule->AddUser(&ad);
		//MOUT(msg.m_text.c_str());



	StudentInfo s;
	s.m_name = "s";
	s.m_key = "123";
	s.m_sex = "男";
	s.m_account = "s";
	s.m_class = "1";
	msg = userModule->AddUser(&s);
	//MOUT(msg.m_text.c_str());

	TeacherInfo t;
	t.m_name = "t";
	t.m_key = "123";
	t.m_account = "t";
	t.m_sex = "男";
	msg = userModule->AddUser(&t);
	//MOUT(msg.m_text.c_str());


	CourseInfo ci;
	ci.classTime = "9:00";
	ci.courseName = "math";
	ci.TeacherID = "2";
	ci.TeacherName = "t";
	msg = selectModule->AddCourse(&ci);

	ci.classTime = "9:00";
	ci.courseName = "english";
	ci.TeacherID = "2";
	ci.TeacherName = "t";
	msg = selectModule->AddCourse(&ci);
	//MOUT(msg.m_text.c_str());

	SelectCourseInfo sinfo;
	sinfo.courseID = "0";
	sinfo.studentID = "1";
	selectModule->AddSelectCourse(&sinfo);
}

void studentApp::update()
{

		hasnew = 0;
		curGUI->OnUpdate();
		if (hasnew)
		{
			hasdelete = 0;
			pm = 0;
		}
}



void studentApp::render()
{

	// output
	curGUI->OnRender();

	// render后
	// 清空临时控件
	// 隔帧清理控件 
	if(pm) 
	{
		while (!controlToDeleteq.empty())
		{
			GUIwindow *g = controlToDeleteq.front();
			controlToDeleteq.pop();
			vector<GUIcontrol*> *c = &g->m_controls;
			for (auto i = c->begin(); i != c->end();)
			{
				if ((*i)->m_name.find("tmp") != string::npos)
				{
					delete *i;
					i = c->erase(i);
				}
				else
					++i;
			}
		}
		hasdelete = 1;
	}

}

void studentApp::clear()
{

	DELETE(g_userTable);
	DELETE(g_courseTable);
	DELETE(g_selectCourseTable);

	DELETE(logModule);
	DELETE(userModule);
	DELETE(selectModule);
	DELETE(scoreModule);

	// clear GUI树
	DELETE(GUIma["LoginPage"]);
	DELETE(GUIma["AdminPage"]);
	DELETE(GUIma["StudentPage"]);
	DELETE(GUIma["TeacherPage"]);

}



void LinkPage(GUIwindow *u, GUIwindow *v)
{
	assert(u != 0 && v != 0);
	u->AddChildGUI(v);
}

void clearTextboxOfGUI(GUIwindow * gui)
{
	vector<GUIcontrol*> *cons = &gui->m_controls;
	for (auto i = cons->begin(); i != cons->end(); ++i)
	{
		if ((*i)->m_type == Ctext)
		{
			GUItext* textbox = dynamic_cast<GUItext*>(*i);
			textbox->SetText("");
		}
	}
}


void LoginPage(GUIwindow *gui)
{
	assert(gui != 0);
	//LoginPage  0 0 800 600
	//	4
	//	学生  400 50 150 50
	//	管理员	  600 50 150 50
	//	教师    800 50 150 50
	//	ok		  400 170 150 50
	//	2
	//	account 50 110 300 20
	//	key   50 170 300 20
	//	2
	//	usertype  。。  50 50  300 20
	//	tag   登录   400 10  150 30

	GUIbutton *Student = (GUIbutton*)gui->FindControl("学生", Cbutton);
	GUIbutton *Teacher = (GUIbutton*)gui->FindControl("教师", Cbutton);
	GUIbutton *admin = (GUIbutton*)gui->FindControl("管理员", Cbutton);
	GUIbutton *ok = (GUIbutton*)gui->FindControl("ok", Cbutton);
	assert(Student != 0 && Teacher != 0 && admin != 0);

	GUItext *account = (GUItext*) gui->FindControl("account", Ctext);
	GUItext *key = (GUItext*) gui->FindControl("LoginKey", Ctext);
	assert(account != 0 && key != 0);

	GUIstaticText *usertype = (GUIstaticText*)gui->FindControl("usertype", Cstext);
	if(Student->isClick())
		usertype->SetText("学生");
	if (Teacher->isClick())
		usertype->SetText("教师");
	if (admin->isClick())
		usertype->SetText("管理员");

	assert(usertype != 0);
	if (ok->isClick())
	{
		string t_type = usertype->GetText();
		string t_account = account->GetText();
		string t_key = key->GetText();
		if (t_type.length() > 0) {
			User tuser;
			tuser.m_account = t_account;
			tuser.m_key = t_key;
			if (t_type == "管理员")
				tuser.m_type = User_admin;
			else if (t_type == "学生")
				tuser.m_type = User_student;
			else if (t_type == "教师")
				tuser.m_type = User_teacher;
			User *u = logModule->Login(&tuser);
			bool ok = (u != 0);
			if (ok)
				MOUT("login success");
#ifdef BUG
#endif 

#ifdef BUG
			ok = 1;
#endif
			if (ok)
			{
				curUser = u;
				curGUI->setVis(false);

				switch (tuser.m_type)  {
					case User_admin:   curGUI = GUIma["AdminPage"];  break;
					case User_student: curGUI = GUIma["StudentPage"]; break;
					case User_teacher: curGUI = GUIma["TeacherPage"]; break;
				}
				curGUI->setVis(true);
			} 
		}
		
	}
}
void AdminPage(GUIwindow *gui)
{
	/*AdminPage 0 0 800 600
		4
		个人信息 10 30 150  40
		用户管理 10 93 150 40
		课程管理 10 150 150 40
		退出     10 195 150 40
		0
		1
		username  欢迎使用 20 5 200 20*/
	/*UserManagePage;
	CourseManagePage;*/
	GUIbutton *personal = (GUIbutton*) gui->FindControl("个人信息", Cbutton);
	GUIbutton *userMange = (GUIbutton*) gui->FindControl("用户管理", Cbutton);
	GUIbutton *courseMange= (GUIbutton*)gui->FindControl("课程管理", Cbutton);
	GUIbutton *logout = (GUIbutton*)gui->FindControl("退出", Cbutton);

	if ((personal->isClick() || userMange->isClick() || courseMange->isClick() ||
		logout->isClick()))
	{
		vector<GUIwindow*> *child = gui->GetAllChildGUI();
		for (auto i = child->begin(); i != child->end(); ++i)
		if (*i)
			(*i)->setVis(0);
	}

	if (personal->isClick())
	{
		// 加载子页面
	} 

	if (userMange->isClick())
	{
		// 加载子页面
		GUIwindow *c = gui->FindChildGUI("UserManagePage");
		assert(c != 0);
		c->setVis(1);
	}

	if (courseMange->isClick())
	{
		// 加载子页面
		GUIwindow *c = gui->FindChildGUI("CourseManagePage");
		assert(c != 0);
		c->setVis(1);
	}

	if (logout->isClick())
	{
		curGUI->setVis(0);
		curGUI = GUIma["LoginPage"];
		curGUI->setVis(1);

		clearTextboxOfGUI(curGUI);
	}
}

void UserManagePage(GUIwindow *gui)
{
	/*UserManagePage 250 10 1000 680
		4
		学生表 270 50 150 40
		教师表 270 100 150 40
		添加用户 270 170 150 40
		删除用户 270 230 150 40
		0
		1
		tag 用户管理 320 10 200 20*/
	GUIbutton *student = (GUIbutton*)gui->FindControl("学生表", Cbutton);
	GUIbutton *teacher = (GUIbutton*)gui->FindControl("教师表", Cbutton);
	GUIbutton *add = (GUIbutton*)gui->FindControl("添加用户", Cbutton);
	GUIbutton *remove = (GUIbutton*)gui->FindControl("删除用户", Cbutton);

	if (student->isClick() || teacher->isClick() ||
		add->isClick() || remove->isClick())
	{
		// 清空子页面
		vector<GUIwindow*> *child = gui->GetAllChildGUI();
		for (auto i = child->begin(); i != child->end(); ++i)
		if (*i)
			(*i)->setVis(0);
	}

	if (student->isClick())
	{
		// 加载学生表页面
		GUIwindow *c = gui->FindChildGUI("StudentListPage");
		assert(c != 0);
		c->setVis(1);
	} 

	if (teacher->isClick())
	{
		// 加载 教师表 页面
		GUIwindow *c = gui->FindChildGUI("TeacherListPage");
		assert(c != 0);
		c->setVis(1);
	}

	if (add->isClick())
	{
		// 加载 添加用户 页面 
		GUIwindow *c = gui->FindChildGUI("AddUserPage");
		assert(c != 0);
		c->setVis(1);
		clearTextboxOfGUI(c);
	} 

	if (remove->isClick())
	{
		// 加载 删除用户页面
		GUIwindow *c = gui->FindChildGUI("DeleteUserPage");
		assert(c != 0);
		c->setVis(1);
		clearTextboxOfGUI(c);
	}

}
void StudentListPage(GUIwindow *gui)
{

	//StudentListPage 550 10 600 700
	//	0
	//	0
	//	1
	//	tag 学生表 680 22 200 20

	if (hasdelete) {
		hasnew = 1;

		StudentTable *st = userModule->getUserTable()->getStudentTable();
		vector<GUIcontrol*> *controls = &gui->m_controls;
		int offsety = 50, offsexx = 0;
		gui->AddStaticText("tmp", gui->m_x, gui->m_y + offsety, RW, RH, "姓名", textfile);
		gui->AddStaticText("tmp", gui->m_x + RW + 11, gui->m_y + offsety, RW, RH, "id", textfile);
		gui->AddStaticText("tmp", gui->m_x + 2 * RW + 11, gui->m_y + offsety, RW, RH, "班别", textfile);
		offsety += RH * 2;
		int c = 0;
		for (auto i = st->begin(); i != st->end(); ++i, ++c)
		{
			string controlname = string("tmp") + tostring(c);
			gui->AddStaticText(controlname, gui->m_x, gui->m_y + offsety, RW, RH, i->second->m_name, textfile);
			gui->AddStaticText(controlname, gui->m_x + RW + 11, gui->m_y + offsety, RW, RH, i->second->m_id, textfile);
			gui->AddStaticText(controlname, gui->m_x + 2 * RW + 11, gui->m_y + offsety, RW, RH, i->second->m_class, textfile);
			offsety += RH;
			++c;
		}
		controlToDeleteq.push(gui);
	}
}

void TeacherListPage(GUIwindow *gui)
{
	if (hasdelete) {
		hasnew = 1;
		TeacherTable *st = userModule->getUserTable()->getTeacherTable();
		vector<GUIcontrol*> *controls = &gui->m_controls;
		int offsety = 50, offsexx = 0;
		gui->AddStaticText("tmp", gui->m_x, gui->m_y + offsety, RW, RH, "姓名", textfile);
		gui->AddStaticText("tmp", gui->m_x + RW + 11, gui->m_y + offsety, RW, RH, "id", textfile);
		offsety += RH * 2;
		int c = 0;
		for (auto i = st->begin(); i != st->end(); ++i, ++c)
		{
			string controlID = string("tmp") + tostring(c);
			gui->AddStaticText(controlID, gui->m_x, gui->m_y + offsety, RW, RH, i->second->m_name, textfile);
			gui->AddStaticText(controlID, gui->m_x + RW + 11, gui->m_y + offsety, RW, RH, i->second->m_id, textfile);
			offsety += RH;
			++c;
		}
		controlToDeleteq.push(gui);
	}
}
void AddUserPage(GUIwindow *gui)
{
	/*AddUserPage  500 0 700 700
		5
		男 900 220 80 30
		女 1000 220 80 30
		学生 900 70 80 30
		教师 1000 70 80 30
		OK  800 280 100 30
		4
		account  700 135 150 15
		key 700 160 150 15
		name 700 190 150 15
		class 700 260 150 15
		9
		type 。。 700 70 150 15
		sex 。。 700 220 150 15
		班别 班别 600 260 70 15
		tag 性别 600 220 70 15
		tag 姓名 600 190 70 15
		tag 账号  600 135 70 15
		tag 密码 600 160 70 15
		tag 添加用户 700 10 150 15
		tag 类型  600 70 70 15*/



	GUIbutton *student = (GUIbutton*)gui->FindControl("学生", Cbutton);
	GUIbutton *teacher = (GUIbutton*)gui->FindControl("教师", Cbutton);
	GUIbutton *boy = (GUIbutton*)gui->FindControl("男", Cbutton);
	GUIbutton *girl = (GUIbutton*)gui->FindControl("女", Cbutton);
	GUIbutton *ok = (GUIbutton*)gui->FindControl("OK", Cbutton);

	GUItext *name = (GUItext*)gui->FindControl("name", Ctext);
	GUItext *account = (GUItext*)gui->FindControl("account", Ctext);
	GUItext *key = (GUItext*)gui->FindControl("key", Ctext);
	GUItext *c = (GUItext*)gui->FindControl("class", Ctext);

	GUIstaticText *type = (GUIstaticText*)gui->FindControl("type", Cstext);
	GUIstaticText *sex = (GUIstaticText*)gui->FindControl("sex", Cstext);
	GUIstaticText *tagclass = (GUIstaticText*)gui->FindControl("班别", Cstext);
	assert(tagclass != 0);
	if (student->isClick())
	{
		type->SetText("学生");
		c->setVis(1);
		tagclass->setVis(1);
	} 
	if (teacher->isClick())
	{
		type->SetText("教师");
		c->setVis(0);
		tagclass->setVis(0);
	}

	if (boy->isClick())
		sex->SetText("男");
	if (girl->isClick())
		sex->SetText("女");

	if (ok->isClick()) {
		string stype = type->GetText();
		string sname = name->GetText();
		string saccount = account->GetText();
		string skey = key->GetText();
		string ssex = sex->GetText();

		if (stype.length() > 0 && sname.length() > 0 &&
			saccount.length() > 0 && skey.length() > 0 && ssex.length() > 0)
		{
			SysMSG msg;
			if (stype == "学生")
			{
				StudentInfo sd;
				sd.m_class = c->GetText();
				if (sd.m_class.length() > 0)  {
					sd.m_type = User_student;
					sd.m_sex = ssex;
					sd.m_name = sname;
					sd.m_account = saccount;
					sd.m_key = skey;
					msg = userModule->AddUser(&sd);
				}
			}

			else if (stype == "教师")
			{
				TeacherInfo t;
				t.m_type = User_teacher;
				t.m_account = saccount;
				t.m_key = skey;
				t.m_name = sname;
				t.m_sex = ssex;
				msg = userModule->AddUser(&t);
			}
			MOUT(msg.m_text.c_str());

		}

	}
}

void DeleteUserPage(GUIwindow *gui)
{
	/*DeleteUserPage  500 10 700 700
		3
		学生 810 80 80 30
		教师 950 80 80 30
		查找 700 240 80 30
		2
		user 680 150 300 20
		id   680 190 300 20
		6
		tag 删除用户 680 20 120 15
		tag 类型 600 90 60 15
		type 。。 680 90 100 15
		tag 姓名 600 150 60 15
		tag id  600 190 60 15
		tag 查找结果 670 360 120 15*/

	GUIbutton *tstudent= (GUIbutton*)gui->FindControl("学生", Cbutton);
	GUIbutton *tteacher= (GUIbutton*)gui->FindControl("教师", Cbutton);
	GUIstaticText *type = (GUIstaticText*)gui->FindControl("type", Cstext);
	if (tstudent->isClick())
		type->SetText("学生");

	if (tteacher->isClick())
		type->SetText("教师");
	GUIbutton *find= (GUIbutton*)gui->FindControl("查找", Cbutton);



	if (find->isClick())
	{
		StudentToDelete.clear();
		TeacherToDelete.clear();
		GUItext *username = (GUItext*)gui->FindControl("user", Ctext);
		GUItext *userid= (GUItext*)gui->FindControl("id", Ctext);
		string sid = userid->GetText();
		string stype = type->GetText();
		if (stype.length() > 0) {
			if (sid.length() > 0)
			{
				if (stype == "学生")
				{
					StudentInfo s;
					s.m_id = sid;
					s.m_type = User_student;
					StudentInfo *res = dynamic_cast<StudentInfo*>(userModule->FindUser(&s));
					if (res) StudentToDelete.push_back(res);
				} 
				else if (stype == "教师")
				{
					TeacherInfo s;
					s.m_id = sid;
					s.m_type = User_teacher;
					TeacherInfo *res = dynamic_cast<TeacherInfo*>(userModule->FindUser(&s));
					if (res) TeacherToDelete.push_back(res);
				}
			}
			else
			{
				string sname = username->GetText();
				if (sname.length())
				{
					if (stype == "学生")
					{
						StudentTable *stb = g_userTable->getStudentTable();
						for(auto i = stb->begin(); i != stb->end(); ++i)
							if (i->second->m_name == sname)
								StudentToDelete.push_back(i->second);
					}
					else if (stype == "教师")
					{
						TeacherTable *ttb = g_userTable->getTeacherTable();
						for (auto i = ttb->begin(); i != ttb->end(); ++i)
						if (i->second->m_name == sname)
							TeacherToDelete.push_back(i->second);
					}
				}
			}
		}
	}


	// ------------------查找结果 --------------------------------
	if (hasdelete)
	{
		hasnew = 1;
		controlToDeleteq.push(gui);

		int offsety = 380, offsetx = 600;
		gui->AddStaticText("tmp", offsetx, offsety, 120, 15, "id", textfile);
		gui->AddStaticText("tmp", offsetx + 130, offsety, 120, 15, "姓名", textfile);
		gui->AddStaticText("tmp", offsetx + 260, offsety, 120, 15, "班别", textfile);
		offsety += 20;
		gui->AddStaticText("tmp", offsetx, offsety, 120, 15, "学生", textfile);
		offsety += 20;
		int c = 1;
		for (int i = 0; i < StudentToDelete.size(); ++i)
		{
			string controlname = tostring(c) + "tmp";
			StudentInfo *s = dynamic_cast<StudentInfo*>(StudentToDelete[i]);
			gui->AddStaticText(controlname, offsetx, offsety, 120, 15, s->m_id, textfile);
			gui->AddStaticText(controlname, offsetx + 130, offsety, 120, 15, s->m_name, textfile);
			gui->AddStaticText(controlname, offsetx + 260, offsety, 120, 15, s->m_class, textfile);
			gui->AddButton(controlname, offsetx + 390, offsety, 80, 15, "删除", buttonfile, 0);
			offsety += 20;
			++c;
		}
		gui->AddStaticText("tmp", offsetx, offsety, 120, 15, "教师", textfile);
		offsety += 20;
		for (int i = 0; i < TeacherToDelete.size(); ++i)
		{
			string controlname = tostring(c) + "tmp";
			TeacherInfo *s = dynamic_cast<TeacherInfo*>(TeacherToDelete[i]);
			gui->AddStaticText(controlname, offsetx, offsety, 120, 15, s->m_id, textfile);
			gui->AddStaticText(controlname, offsetx + 130, offsety, 120, 15, s->m_name, textfile);
			gui->AddButton(controlname, offsetx + 260, offsety, 80, 30, "删除", buttonfile, 0);
			offsety += 20;
			++c;
		}

	}

	// 删除
	vector<GUIcontrol*> *cons = &gui->m_controls;
	for (auto i = cons->begin(); i != cons->end(); ++i)
	{
		if ((*i)->m_type == Cbutton)
		{
			GUIbutton *de = dynamic_cast<GUIbutton*>(*i);
			assert(de != 0);

			if (de->m_buttonText == "删除" && de->isClick())
			{
				int flag = 0;  // 删除学生
				for (auto j = cons->begin(); j != cons->end(); ++j)
				{
					if ((*j)->m_type != Cstext)
						continue;
					GUIstaticText *did= dynamic_cast<GUIstaticText*>(*j);
					if (did->GetText() == "教师") flag = 1;   //删除教师

					// 和"删除"同名的静态文本
					if (i - j && did->m_name == de->m_name)
					{
						string tid = did->GetText();
						if (flag == 0) {
							for (auto k = StudentToDelete.begin(); k != StudentToDelete.end();)
								if (tid == (*k)->m_id) {
									k = StudentToDelete.erase(k);
									break;
								}
								else ++k;
							StudentInfo s;
							s.m_type = User_student;
							s.m_id = tid;
							SysMSG msg = userModule->DeleteUser(&s);
						}
						else if (flag == 1)
						{
							
							for (auto k = TeacherToDelete.begin(); k != TeacherToDelete.end(); )
								if (tid == (*k)->m_id) {
									k=TeacherToDelete.erase(k);
									break;
								}
								else ++k;

							TeacherInfo s;
							s.m_type = User_teacher;
							s.m_id = tid;
							userModule->DeleteUser(&s);
						}
						break;
					}
				}
			}
		}
	}


}

void CourseManagePage(GUIwindow *gui)
{

	//CourseManagePage 300 10 1100 700
	//	2
	//	课程表  350 100 150  30
	//	添加课程 350 140 150 30
	//	0
	//	1
	//	tag 课程管理 500 15  120 15
	/*LinkPage(GUIma["CourseManagePage"], GUIma["DeleteCoursePage"]);
	LinkPage(GUIma["CourseManagePage"], GUIma["AddCoursePage"]); */

	GUIbutton *addcourse= (GUIbutton*)gui->FindControl("添加课程", Cbutton);
	GUIbutton *coursetable = (GUIbutton*)gui->FindControl("课程表", Cbutton);

	if (coursetable->isClick() || addcourse->isClick())
	{
		// 清空子页面
		vector<GUIwindow*> *child = gui->GetAllChildGUI();
		for (auto i = child->begin(); i != child->end(); ++i)
		if (*i)
			(*i)->setVis(0);
	}



	if (addcourse->isClick())
	{
		// 加载 添加课程页表
		GUIwindow *c = gui->FindChildGUI("AddCoursePage");
		assert(c != 0);
		c->setVis(1);
		clearTextboxOfGUI(c);

	}
	if (coursetable->isClick())
	{
		// 加载 课程列表 并删除课程
		GUIwindow *c = gui->FindChildGUI("DeleteCoursePage");
		assert(c != 0);
		c->setVis(1);
		clearTextboxOfGUI(c);

	}

}

void AddCoursePage(GUIwindow *gui)
{

	/*AddCoursePage 330 10 800 700
		1
		添加   750 240  100 40
		3
		coursename  820 90 200 15
		teacherid 820 140  200 15
	  classtime  820 180 200 15
		4
		tag 添加课程 750 20 120 15
		tag 课程名 710 90 90 15
		tag 老师号 710 140 90 15
	  tag 时间   710 180 90 15*/


	GUIbutton *add = (GUIbutton*)gui->FindControl("添加", Cbutton);
	GUItext *coursename = (GUItext*)gui->FindControl("coursename", Ctext);
	GUItext *teacherid = (GUItext*)gui->FindControl("teacherid", Ctext);
	GUItext *ctime = (GUItext*)gui->FindControl("classtime", Ctext);

	if (add->isClick())
	{
		string name = coursename->GetText();
		string tid = teacherid->GetText();
		string ct = ctime->GetText();
		if (name.length() > 0 && tid.length() > 0 && ct.length() > 0)
		{
			CourseInfo c;
			c.courseName = name;
			c.TeacherID = tid;
			c.classTime = ct;
			SysMSG msg = selectModule->AddCourse(&c);
#ifdef BUG
			MOUT(msg.m_text.c_str());
#endif
		}
	}



}

void DeleteCoursePage(GUIwindow *gui)
{
	/*DeleteCoursePage 450 10 700 700
		1
		查找   800 100   120 30
		2
		coursename 850 35 300 15
		courseid   850 50 300 15
		3
		tag 删除课程 750  15 120 15
		tag 课程名 700 35 120 15
		tag 课程号 700 50 120 15*/

	// ------------查找-------------------


	GUIbutton *find = (GUIbutton*)gui->FindControl("查找", Cbutton);

	if (find->isClick())
	{
		CourseToDelete.clear();
		GUItext *coursename = (GUItext*)gui->FindControl("coursename", Ctext);
		GUItext *courseid = (GUItext*)gui->FindControl("courseid", Ctext);
		string sid = courseid->GetText();
		string sname= coursename->GetText();
		if (sid.length() > 0)
		{
			CourseInfo c;
			c.courseID = sid;
			CourseInfo *res = g_courseTable->FindCourse(&c);
			if (res) CourseToDelete.push_back(res);
		} 
		else if (sname.length() > 0)
		{
			vector<CourseInfo*> *ctb = g_courseTable->getCourseTable();
			for(auto i = ctb->begin(); i != ctb->end(); ++i) 
			if ((*i)->courseName == "sname")
				CourseToDelete.push_back(*i);
		}
	}



	// ------------------查找结果 --------------------------------
	if (hasdelete)
	{
		hasnew = 1;
		controlToDeleteq.push(gui);

		int offsety = 150, offsetx = 700;
		gui->AddStaticText("tmp", offsetx, offsety, 120, 15, "id", textfile);
		gui->AddStaticText("tmp", offsetx + 130, offsety, 120, 15, "课名", textfile);
		offsety += 20;
		gui->AddStaticText("tmp", offsetx, offsety, 120, 15, "查找结果", textfile);
		offsety += 20;
		int c = 1;
		for (int i = 0; i < CourseToDelete.size(); ++i)
		{
			string controlname = tostring(c) + "tmp";
			CourseInfo *s = CourseToDelete[i];
			gui->AddStaticText(controlname, offsetx, offsety, 120, 15, s->courseID, textfile);
			gui->AddStaticText(controlname, offsetx + 130, offsety, 120, 15, s->courseName, textfile);
			gui->AddButton(controlname, offsetx + 260, offsety, 80, 15, "删除", buttonfile, 0);
			offsety += 20;
			++c;
		}
	}

	// ---------------------------删除 --------------------------------
	vector<GUIcontrol*> *cons = &gui->m_controls;
	for (auto i = cons->begin(); i != cons->end(); ++i)
	{
		if ((*i)->m_type == Cbutton)
		{
			GUIbutton *de = dynamic_cast<GUIbutton*>(*i);
			assert(de != 0);

			if (de->m_buttonText == "删除" && de->isClick())
			{
				for (auto j = cons->begin(); j != cons->end(); ++j)
				{
					if ((*j)->m_type != Cstext)
						continue;
					GUIstaticText *did = dynamic_cast<GUIstaticText*>(*j);

					// 和"删除"同名的静态文本
					if (i - j && did->m_name == de->m_name)
					{
						string tid = did->GetText();
						for (auto k = CourseToDelete.begin(); k != CourseToDelete.end();)
						if ((*k)->courseID == tid)
							k = CourseToDelete.erase(k);
						else
							++k;

						CourseInfo c;
						c.courseID = tid;
						SysMSG msg = selectModule->DeleteCourse(&c);
						MOUT(msg.m_text.c_str());
						break;
					}
				}
			}
		}
	}
}

void StudentPage(GUIwindow *gui)
{
	//  shit
	//StudentPage 0 0 1200 900
	//	6
	//	个人信息 20 30 150 40
	//	查看课表 20 75 150 40
	//	查看成绩 20 120 150 40
	//	选课     20 165 150 40
	//	已选课程 20 210 150 40
	//	退出     20 255 150 40
	//	0
	//	1
	//	tag 欢迎使用 20 10 120 15
	/*LinkPage(GUIma["StudentPage"], GUIma["StudentInfoPage"]);
	LinkPage(GUIma["StudentPage"], GUIma["CourseTablePage"]);
	LinkPage(GUIma["StudentPage"], GUIma["StudentScorePage"]);
	LinkPage(GUIma["StudentPage"], GUIma["SelectCoursePage"]);
	LinkPage(GUIma["StudentPage"], GUIma["SelectedCoursePage"]);*/



	GUIbutton *person = (GUIbutton*)gui->FindControl("个人信息", Cbutton);
	GUIbutton *coursetable = (GUIbutton*)gui->FindControl("查看课表", Cbutton);
	GUIbutton *score = (GUIbutton*)gui->FindControl("查看成绩", Cbutton);
	GUIbutton *selctcourse = (GUIbutton*)gui->FindControl("选课", Cbutton);
	GUIbutton *selectedcourse = (GUIbutton*)gui->FindControl("已选课程", Cbutton);
	GUIbutton *logout = (GUIbutton*)gui->FindControl("退出", Cbutton);

	if (person->isClick() || coursetable->isClick() ||
		score->isClick() || selctcourse->isClick() ||
		selectedcourse->isClick() || logout->isClick())
	{
		// 清空子页面
		vector<GUIwindow*> *child = gui->GetAllChildGUI();
		for (auto i = child->begin(); i != child->end(); ++i)
		if (*i)
			(*i)->setVis(0);
	}


	if(person->isClick())
	{
		// 加载 添加课程页表
		GUIwindow *c = gui->FindChildGUI("StudentInfoPage");
		assert(c != 0);
		c->setVis(1);
	}
	if (coursetable->isClick())
	{
		// 加载 添加课程页表
		GUIwindow *c = gui->FindChildGUI("CourseTablePage");
		assert(c != 0);
		c->setVis(1);
	}

	if (score->isClick())
	{
		// 加载 添加课程页表
		GUIwindow *c = gui->FindChildGUI("StudentScorePage");
		assert(c != 0);
		c->setVis(1);
	}

	if (selctcourse->isClick())
	{
		// 加载 添加课程页表
		GUIwindow *c = gui->FindChildGUI("SelectCoursePage");
		assert(c != 0);
		c->setVis(1);
	}

	if (selectedcourse->isClick())
	{
		// 加载 添加课程页表
		GUIwindow *c = gui->FindChildGUI("SelectedCoursePage");
		assert(c != 0);
		c->setVis(1);
	}

	if (logout->isClick())
	{
		curGUI->setVis(0);
		curGUI = GUIma["LoginPage"];
		assert(curGUI != 0);
		curGUI->setVis(true);
		clearTextboxOfGUI(curGUI);
	}

	// 添加控件到子页面
	// 选课页面： 所有课程，添加选课按钮



	//SelectCoursePage 250 10 900 700
	//	0
	//	0
	//	1
	//	tag  选课  400 20 120 15
	if (hasdelete)
	{
		hasnew = 1;
		vector<CourseInfo*> *ctb = g_courseTable->getCourseTable();
		GUIwindow *selectPage = GUIma["SelectCoursePage"];
		int offsetx = 0, offsety = 45;
		int c = 0;
		// 课程Id - 课程名 - 老师名 -上课时间
		selectPage->AddStaticText("tmp", selectPage->m_x, gui->m_y + offsety, RW, RH, "课程号", textfile);
		selectPage->AddStaticText("tmp", selectPage->m_x + RW, gui->m_y + offsety, RW, RH, "课程名", textfile);
		selectPage->AddStaticText("tmp", selectPage->m_x + 2 * RW, gui->m_y + offsety, RW, RH, "老师名", textfile);
		selectPage->AddStaticText("tmp", selectPage->m_x + 3 * RW, gui->m_y + offsety, RW, RH, "上课时间", textfile);
		offsety += 2 * RH;
		for (auto i = ctb->begin(); i != ctb->end(); ++i)
		{
			CourseInfo *cs = *i;
			string controlname = string("tmp") + tostring(c);
			selectPage->AddStaticText(controlname, selectPage->m_x, gui->m_y + offsety, RW, RH, cs->courseID, textfile);
			selectPage->AddStaticText(controlname, selectPage->m_x + RW, gui->m_y + offsety, RW, RH, cs->courseName, textfile);
			selectPage->AddStaticText(controlname, selectPage->m_x + 2 * RW, gui->m_y + offsety, RW, RH, cs->TeacherName, textfile);
			selectPage->AddStaticText(controlname, selectPage->m_x + 3 * RW, gui->m_y + offsety, RW, RH, cs->classTime, textfile);
			//"添加"按钮
			selectPage->AddButton(controlname, selectPage->m_x + 4 * RW, gui->m_y + offsety, RW, RH, "添加", buttonfile, 0);
			offsety += RH;
			c++;
		}
		controlToDeleteq.push(selectPage);
	}

	// shit2
	// 已选课程页面： 所有已选课程， 删除选课按钮
	//CourseTablePage 250 10 900 700
	//	0
	//	0
	//	1
	//	tag  课表  400 20 120 15
	if (hasdelete)
	{
		hasnew = 1;

		GUIwindow *selectPage = GUIma["SelectedCoursePage"];
		StudentInfo *s = dynamic_cast<StudentInfo*> (curUser);
		assert(s != 0);
		int offsety = 30;
		// 课程名 - 课程id - 教师名 - 教师id
		selectPage->AddStaticText("tmp", selectPage->m_x, selectPage->m_y + offsety, RW, RH, "课程id", textfile);
		selectPage->AddStaticText("tmp", selectPage->m_x + RW + 11, selectPage->m_y + offsety, RW, RH, "课程名", textfile);
		selectPage->AddStaticText("tmp", selectPage->m_x + 2 * RW + 11, selectPage->m_y + offsety, RW, RH, "教师名", textfile);
		selectPage->AddStaticText("tmp", selectPage->m_x + 3 * RW + 11, selectPage->m_y + offsety, RW, RH, "教师id", textfile);
		selectPage->AddStaticText("tmp", selectPage->m_x + 4 * RW + 11, selectPage->m_y + offsety, RW, RH, "时间", textfile);
		offsety += RH * 2;

		vector<CourseInfo*> *k = s->getKebiao()->getKebiao();
		int c = 0;
		for (auto i = k->begin(); i != k->end(); ++i)
		{
			string controlname = string("tmp") + tostring(c);
			selectPage->AddStaticText(controlname, selectPage->m_x, selectPage->m_y + offsety, RW, RH, (*i)->courseID, textfile);
			selectPage->AddStaticText(controlname, selectPage->m_x + RW + 11, selectPage->m_y + offsety, RW, RH, (*i)->courseName, textfile);
			selectPage->AddStaticText(controlname, selectPage->m_x + 2 * RW + 11, selectPage->m_y + offsety, RW, RH, (*i)->TeacherName, textfile);
			selectPage->AddStaticText(controlname, selectPage->m_x + 3 * RW + 11, selectPage->m_y + offsety, RW, RH, (*i)->TeacherID, textfile);
			selectPage->AddStaticText(controlname, selectPage->m_x + 4 * RW + 11, selectPage->m_y + offsety, RW, RH, (*i)->classTime, textfile);
			// "删除"按钮
			selectPage->AddButton(controlname, selectPage->m_x + 5 * RW + 11, selectPage->m_y + offsety, RW, RH, "删除", buttonfile, 0);
			offsety += RH;
			++c;
		}
		controlToDeleteq.push(selectPage);
	}
}

void StudentInfoPage(GUIwindow *gui)
{
	/*StudentInfoPage 250 10 900 700
		0
		0
		1
		tag  个人信息 400 20 120 15*/

	if (hasdelete) 
	{
		hasnew = 1;
		StudentInfo *s = dynamic_cast<StudentInfo*> (curUser);
		assert(s != 0);
		int offsety = 30;
		// 班别 姓名  id,  性别
		gui->AddStaticText("tmp", gui->m_x, gui->m_y + offsety, RW, RH, "班别", textfile);
		gui->AddStaticText("tmp", gui->m_x + RW + 11, gui->m_y + offsety, RW, RH, "姓名", textfile);
		gui->AddStaticText("tmp", gui->m_x + 2 * RW + 11, gui->m_y + offsety, RW, RH, "id", textfile);
		gui->AddStaticText("tmp", gui->m_x + 3 * RW + 11, gui->m_y + offsety, RW, RH, "性别", textfile);
		offsety += RH * 2;

		gui->AddStaticText("tmp", gui->m_x, gui->m_y + offsety, RW, RH, s->m_class, textfile);
		gui->AddStaticText("tmp", gui->m_x + RW + 11, gui->m_y + offsety, RW, RH, s->m_name, textfile);
		gui->AddStaticText("tmp", gui->m_x + 2 * RW + 11, gui->m_y + offsety, RW, RH, s->m_id, textfile);
		gui->AddStaticText("tmp", gui->m_x + 3 * RW + 11, gui->m_y + offsety, RW, RH, s->m_sex, textfile);

		controlToDeleteq.push(gui);
	}

}

void CourseTablePage(GUIwindow *gui)
{
	//CourseTablePage 250 10 900 700
	//	0
	//	0
	//	1
	//	tag  课表  400 20 120 15



	if (hasdelete)
	{
		hasnew = 1;
		StudentInfo *s = dynamic_cast<StudentInfo*> (curUser);
		assert(s != 0);
		int offsety = 30;
		// 课程名 - 课程id - 教师名 - 教师id
		gui->AddStaticText("tmp", gui->m_x, gui->m_y + offsety, RW, RH, "课程名", textfile);
		gui->AddStaticText("tmp", gui->m_x + RW + 11, gui->m_y + offsety, RW, RH, "课程id", textfile);
		gui->AddStaticText("tmp", gui->m_x + 2 * RW + 11, gui->m_y + offsety, RW, RH, "教师名", textfile);
		gui->AddStaticText("tmp", gui->m_x + 3 * RW + 11, gui->m_y + offsety, RW, RH, "教师id", textfile);
		gui->AddStaticText("tmp", gui->m_x + 4 * RW + 11, gui->m_y + offsety, RW, RH, "时间", textfile);
		offsety += RH * 2;

		vector<CourseInfo*> *k = s->getKebiao()->getKebiao();
		int c = 0;
		for (auto i = k->begin(); i != k->end(); ++i)
		{
			string controlname = string("tmp") + tostring(c);
			gui->AddStaticText("tmp", gui->m_x, gui->m_y + offsety, RW, RH, (*i)->courseName, textfile);
			gui->AddStaticText("tmp", gui->m_x + RW + 11, gui->m_y + offsety, RW, RH, (*i)->courseID, textfile);
			gui->AddStaticText("tmp", gui->m_x + 2 * RW + 11, gui->m_y + offsety, RW, RH, (*i)->TeacherName, textfile);
			gui->AddStaticText("tmp", gui->m_x + 3 * RW + 11, gui->m_y + offsety, RW, RH, (*i)->TeacherID, textfile);
			gui->AddStaticText("tmp", gui->m_x + 4 * RW + 11, gui->m_y + offsety, RW, RH, (*i)->classTime, textfile);
			offsety += RH;
			++c;
		}
		controlToDeleteq.push(gui);
	}

}

void StudentScorePage(GUIwindow *gui)
{

	if (hasdelete) 
	{
		hasnew = 1;
		StudentInfo *s = dynamic_cast<StudentInfo*> (curUser);
		assert(s != 0);
		int offsety = 30;
		// 课程名 - 课程id - 教师名 - 教师id - 成绩
		gui->AddStaticText("tmp", gui->m_x, gui->m_y + offsety, RW, RH, "课程名", textfile);
		gui->AddStaticText("tmp", gui->m_x + RW + 11, gui->m_y + offsety, RW, RH, "课程id", textfile);
		gui->AddStaticText("tmp", gui->m_x + 2 * RW + 11, gui->m_y + offsety, RW, RH, "成绩", textfile);
		offsety += RH * 2;

		// selectCourseTable
		StudentInfo *sd = dynamic_cast<StudentInfo*>(curUser);
		assert(sd != 0);
		vector<SelectCourseInfo*> *stb = g_selectCourseTable->getSelectCourseTable();
		for (auto i = stb->begin(); i != stb->end(); ++i)
		{
			SelectCourseInfo *sinfo = (*i);
			if (sinfo->studentID == sd->m_id)
			{
				string controlname = "tmp";
				gui->AddStaticText(controlname, gui->m_x, gui->m_y + offsety, RW, RH, sinfo->courseName, textfile);
				gui->AddStaticText(controlname, gui->m_x + RW + 11, gui->m_y + offsety, RW, RH,sinfo->courseID, textfile);
				string score;
				char score1[11];
				sprintf(score1, "%.2f", sinfo->score);
				score = score1;
				gui->AddStaticText(controlname, gui->m_x + 2 * RW + 11, gui->m_y + offsety, RW, RH, score, textfile);
				offsety += RH;
			}
		}
	
		controlToDeleteq.push(gui);
	}

}

void SelectCoursePage(GUIwindow *gui)
{
	// fuck
	// 添加课程， 控件已在上层页面加载到这个页面
	vector<GUIcontrol*> *cons = &gui->m_controls;
	for (auto i = cons->begin(); i != cons->end(); ++i)
	{
		if ((*i)->m_type == Cbutton)
		{
			GUIbutton *de = dynamic_cast<GUIbutton*>(*i);
			assert(de != 0);

			if (de->m_buttonText == "添加" && de->isClick())
			{
				SelectCourseInfo sinfo;
				sinfo.studentID = dynamic_cast<StudentInfo*>(curUser)->m_id;
				int c = 0;
				for (auto j = cons->begin(); j != cons->end(); ++j)
				{
					if ((*j)->m_type != Cstext)
						continue;
					GUIstaticText *courseid= dynamic_cast<GUIstaticText*>(*j);
					// 和"添加"同名的静态文本
					if (i - j && courseid->m_name == de->m_name)
					{
						sinfo.courseID = courseid->GetText();
						SysMSG msg = selectModule->AddSelectCourse(&sinfo);
						MOUT(msg.m_text.c_str());
						return;
						break;
					}
				}
			}
		}
	}
}

void SelectedCoursePage(GUIwindow *gui)
{
	// fuck2
	// 添加课程， 控件已在上层页面加载到这个页面
	vector<GUIcontrol*> *cons = &gui->m_controls;
	for (auto i = cons->begin(); i != cons->end(); ++i)
	{
		if ((*i)->m_type == Cbutton)
		{
			GUIbutton *de = dynamic_cast<GUIbutton*>(*i);
			assert(de != 0);

			if (de->m_buttonText == "删除" && de->isClick())
			{
				SelectCourseInfo sinfo;
				sinfo.studentID = dynamic_cast<StudentInfo*>(curUser)->m_id;
				for (auto j = cons->begin(); j != cons->end(); ++j)
				{
					if ((*j)->m_type != Cstext)
						continue;
					GUIstaticText *courseid = dynamic_cast<GUIstaticText*>(*j);
					// 和"删除"同名的静态文本
					if (i - j && courseid->m_name == de->m_name)
					{
						sinfo.courseID = courseid->GetText();
						SysMSG msg = selectModule->DeleteSelctCourse(&sinfo);
						MOUT(msg.m_text.c_str());
						return;
						break;
					}
				}
			}
		}
	}
}

void TeacherPage(GUIwindow *gui)
{
	/*TeacherPage 0 0 1200 900
	4
	个人信息 20 30 150 40
	查看课表 20 75 150 40
	修改成绩 20 120 150 40
	退出     20 165 150 40
	0
	1
	tag 欢迎使用 20 10 120 15*/
	//LinkPage(GUIma["TeacherPage"], GUIma["TeacherInfoPage"]);
	//LinkPage(GUIma["TeacherPage"], GUIma["TeacherUpdateScorePage"]);
	//LinkPage(GUIma["TeacherPage"], GUIma["TeacherCourseTablePage"]);



	GUIbutton *person = (GUIbutton*)gui->FindControl("个人信息", Cbutton);
	GUIbutton *coursetable = (GUIbutton*)gui->FindControl("查看课表", Cbutton);
	GUIbutton *score = (GUIbutton*)gui->FindControl("修改成绩", Cbutton);
	GUIbutton *logout = (GUIbutton*)gui->FindControl("退出", Cbutton);

	if (person->isClick() || coursetable->isClick() ||
		score->isClick() || logout->isClick())
	{
		// 清空子页面
		vector<GUIwindow*> *child = gui->GetAllChildGUI();
		for (auto i = child->begin(); i != child->end(); ++i)
		if (*i)
			(*i)->setVis(0);
	}


	if (person->isClick())
	{
		// 加载 添加课程页表
		GUIwindow *c = gui->FindChildGUI("TeacherInfoPage");
		assert(c != 0);
		c->setVis(1);
	}
	if (coursetable->isClick())
	{
		// 加载  添加课程页表
		GUIwindow *c = gui->FindChildGUI("TeacherCourseTablePage");
		assert(c != 0);
		c->setVis(1);
	}

	if (score->isClick())
	{
		// 加载 修改成绩页面
		GUIwindow *c = gui->FindChildGUI("TeacherUpdateScorePage");
		assert(c != 0);
		c->setVis(1);
	}
	if (logout->isClick())
	{
		curGUI->setVis(0);
		curGUI = GUIma["LoginPage"];
		assert(curGUI != 0);
		curGUI->setVis(true);
		clearTextboxOfGUI(curGUI);
	}


	// fuck3
	// 加载修改成绩控件到子页面
	/*
	TeacherUpdateScorePage 250 10 900 700
	0
	0
	1
	tag  修改成绩   400 20 120 15*/


	if (hasdelete)
	{
		hasnew = 1;
		GUIwindow *updatescore = GUIma["TeacherUpdateScorePage"];

		TeacherInfo *teacher = dynamic_cast<TeacherInfo*> (curUser);

		vector<CourseInfo*> *ctb = g_courseTable->getCourseTable();
		vector<SelectCourseInfo*> *stb = g_selectCourseTable->getSelectCourseTable();
		int offsety = 30;
		// 学号 - 姓名 - 课程名 - 成绩
		string controlname = "tmp";
		updatescore->AddStaticText(controlname, updatescore->m_x, updatescore->m_y + offsety, RW, RH, "学号", textfile);
		updatescore->AddStaticText(controlname, updatescore->m_x + RW + 11, updatescore->m_y + offsety, RW, RH, "姓名", textfile);
		updatescore->AddStaticText(controlname, updatescore->m_x + 2 * RW + 11, updatescore->m_y + offsety, RW, RH, "课程名", textfile);
		updatescore->AddStaticText(controlname, updatescore->m_x + 3 * RW + 11, updatescore->m_y + offsety, RW, RH, "成绩", textfile);
		offsety += RH;


		int c = 0;
		for (auto i = ctb->begin(); i != ctb->end(); ++i)
		{
			CourseInfo *cinfo = (*i);
			if (cinfo->TeacherID != teacher->m_id)  continue;
			for (auto j = stb->begin(); j != stb->end(); ++j)
			{
				SelectCourseInfo *sinfo = (*j);
				if (sinfo->courseID == cinfo->courseID)
				{
					controlname = tostring(c) + string("tmp");
					updatescore->AddStaticText(controlname, updatescore->m_x, updatescore->m_y + offsety, RW, RH, sinfo->studentID, textfile);
					updatescore->AddStaticText(controlname, updatescore->m_x + RW + 11, updatescore->m_y + offsety, RW, RH, sinfo->studentName, textfile);
					updatescore->AddStaticText(controlname, updatescore->m_x + 2 * RW + 11, updatescore->m_y + offsety, RW, RH, cinfo->courseName, textfile);
					// 静态text， 学生选课没了才删除
					string textboxname = tostring(c);
					if (!textboxmap[textboxname]) 
					{
						int id = updatescore->AddText(textboxname, updatescore->m_x + 3 * RW + 11, updatescore->m_y + offsety, RW, RH, textfile);
						textboxmap[textboxname] = 1;
						// 新建时预置成绩
						GUItext *tmp= (GUItext*)updatescore->FindControl(textboxname, Ctext);
						tmp->SetText(tostring((int)sinfo->score));
					}
					++c;
					offsety += RH;
				}
			}
		}
		controlToDeleteq.push(updatescore);
	}
}

void TeacherInfoPage(GUIwindow *gui)
{

	if (hasdelete) 
	{
		hasnew = 1;
		TeacherInfo *s = dynamic_cast<TeacherInfo*> (curUser);
		assert(s != 0);
		int offsety = 30;
		// 姓名 - id - 性别
		gui->AddStaticText("tmp", gui->m_x, gui->m_y + offsety, RW, RH, "姓名", textfile);
		gui->AddStaticText("tmp", gui->m_x + RW + 11, gui->m_y + offsety, RW, RH, "id", textfile);
		gui->AddStaticText("tmp", gui->m_x + 2 * RW + 11, gui->m_y + offsety, RW, RH, "性别", textfile);
		offsety += RH * 2;

		gui->AddStaticText("tmp", gui->m_x, gui->m_y + offsety, RW, RH, s->m_name, textfile);
		gui->AddStaticText("tmp", gui->m_x + RW + 11, gui->m_y + offsety, RW, RH, s->m_id, textfile);
		gui->AddStaticText("tmp", gui->m_x + 2 * RW + 11, gui->m_y + offsety, RW, RH, s->m_sex, textfile);

		controlToDeleteq.push(gui);
	}


}


void TeacherCourseTablePage(GUIwindow *gui)
{

	if (hasdelete) 
	{
		hasnew = 1;
		TeacherInfo *s = dynamic_cast<TeacherInfo*> (curUser);
		assert(s != 0);
		int offsety = 30;
		// 课程名 - 课程id - 教师名 - 教师id
		gui->AddStaticText("tmp", gui->m_x, gui->m_y + offsety, RW, RH, "课程名", textfile);
		gui->AddStaticText("tmp", gui->m_x + 1 * RW + 11, gui->m_y + offsety, RW, RH, "课程id", textfile);
		gui->AddStaticText("tmp", gui->m_x + 2 * RW + 11, gui->m_y + offsety, RW, RH, "教师名", textfile);
		gui->AddStaticText("tmp", gui->m_x + 3 * RW + 11, gui->m_y + offsety, RW, RH, "教师id", textfile);
		offsety += RH * 2;

		vector<CourseInfo*> *k = s->getKebiao()->getKebiao();
		int c = 0;
		for (auto i = k->begin(); i != k->end(); ++i)
		{
			string controlname = string("tmp") + tostring(c);
			gui->AddStaticText("tmp", gui->m_x, gui->m_y + offsety, RW, RH, (*i)->courseName, textfile);
			gui->AddStaticText("tmp", gui->m_x + 1 * RW + 11, gui->m_y + offsety, RW, RH, (*i)->courseID, textfile);
			gui->AddStaticText("tmp", gui->m_x + 2 * RW + 11, gui->m_y + offsety, RW, RH, (*i)->TeacherName, textfile);
			gui->AddStaticText("tmp", gui->m_x + 3 * RW + 11, gui->m_y + offsety, RW, RH, (*i)->TeacherID, textfile);
			offsety += RH;
			++c;
		}
		controlToDeleteq.push(gui);
	}
}

void TeacherUpdateScorePage(GUIwindow *gui)
{

	//TeacherUpdateScorePage 250 10 900 700
	//	0
	//	0
	//	1
	//	tag  修改成绩   400 20 120 15


	// 删除控件
	int c = 0;
	TeacherInfo *teacher = dynamic_cast<TeacherInfo*> (curUser);
	vector<CourseInfo*> *ctb = g_courseTable->getCourseTable();
	vector<SelectCourseInfo*> *stb = g_selectCourseTable->getSelectCourseTable();

	int studentNum = 0;
	for (auto i = ctb->begin(); i != ctb->end(); ++i)
	{
		CourseInfo *cinfo = (*i);
		if (cinfo->TeacherID != teacher->m_id)  continue;
		for (auto j = stb->begin(); j != stb->end(); ++j)
		{
			SelectCourseInfo *sinfo = (*j);
			if (sinfo->courseID == cinfo->courseID)
				++studentNum;
		}
	}

	vector<GUIcontrol*> *cons = &gui->m_controls;
	for (auto i = cons->begin(); i != cons->end();)
	{
		if ((*i)->m_type == Ctext)
		{
			GUItext *text = dynamic_cast<GUItext*>(*i);
			string cname = text->m_name;
			int num = 0;
			for (int k = 0; k < cname.length() && '0' <= cname[k] && cname[k] <= '9'; ++k)
				num = 10 * num + cname[k] - '0';
			if (num > studentNum) {
				textboxmap[text->m_name] = 0;
				delete *i;
				i = cons->erase(i);
			}
			else
				++i;
		}
		else
			++i;
	}


	// if(click)
	
	// 学号 - 姓名 - 课程名 - 成绩
	c = 0;
	for (auto i = ctb->begin(); i != ctb->end(); ++i)
	{
		CourseInfo *cinfo = (*i);
		if (cinfo->TeacherID != teacher->m_id)  continue;
		for (auto j = stb->begin(); j != stb->end(); ++j)
		{
			SelectCourseInfo *sinfo = (*j);
			if (sinfo->courseID == cinfo->courseID)
			{
				string textname = tostring(c);
				string controlname = tostring(c) + "tmp";
				GUItext *scoretext = (GUItext*)gui->FindControl(textname, Ctext);
				if (scoretext)
				{
					string score = scoretext->GetText();
					int iscore = 0;
					for (int k = 0; k < score.length(); ++k)
						iscore = iscore * 10 + score[k] - '0';
					sinfo->score = iscore;
				}
				++c;
			}
		}
	}

}
