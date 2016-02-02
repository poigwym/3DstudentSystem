

#include"SysModule.h"


SelectCourseModule::SelectCourseModule(UserTable *g_userTable, CourseTable *g_courseTable, SelectCourseTable *g_selectCourseTable) :
	g_userTable(g_userTable), g_courseTable(g_courseTable), g_selectCourseTable(g_selectCourseTable)
{
}

SelectCourseModule::~SelectCourseModule()
{
}

SysMSG SelectCourseModule::AddCourse(CourseInfo* cinfo)
{
	// 输入课程名，教师号
	assert(g_courseTable != 0);
	SysMSG msg;

	//check
	if (cinfo->classTime.length() == 0  ||
		cinfo->courseName.length() == 0 || cinfo->TeacherID.length() == 0 )
	{
		msg.m_text = "fomat error";
		return msg;
	}

	// 查找有没这老师
	TeacherInfo t;
	t.m_id = cinfo->TeacherID;
	assert(t.m_type == User_teacher);
	TeacherInfo *teacher;
	if ((teacher = (TeacherInfo*)g_userTable->FindUser(&t)) == NULL)
	{
		msg.ok = 0;
		msg.m_text = "no this teacher ";
		return msg;
	} 
	cinfo->TeacherName = teacher->m_name;
	msg = g_courseTable->AddCourse(cinfo);
	if (msg.ok == 0)
		return msg;
	
	cinfo = g_courseTable->FindCourse(cinfo);
	// 添加课程到老师课表
	return teacher->AddCorse(cinfo);
}

SysMSG SelectCourseModule::DeleteCourse(CourseInfo* cinfo)
{
	SysMSG msg;
	msg = g_courseTable->DeleteCourse(cinfo);
	if (msg.ok == 0)
		return msg;
	// 从选课表删除选课信息
	g_selectCourseTable->DeleteInfoOfCourse(cinfo);
	// 从学生课表删除选课信息
	StudentTable *stb = g_userTable->getStudentTable();
	for (auto i = stb->begin(); i != stb->end(); ++i)
		i->second->getKebiao()->DeleteCourse(cinfo);

	// 从教师课表删除课程信息
	TeacherTable *tb = g_userTable->getTeacherTable();
	for (auto i = tb->begin(); i != tb->end(); ++i)
		i->second->getKebiao()->DeleteCourse(cinfo);

	msg.ok = 1;
	msg.m_text = "delete course success";
	return msg;
}

SysMSG SelectCourseModule::AddSelectCourse(SelectCourseInfo * sinfo)
{
	SysMSG msg;

	StudentInfo sd, *student;
	assert(sd.m_type == User_student);
	sd.m_id = sinfo->studentID;
	if((student = (StudentInfo*)g_userTable->FindUser(&sd)) == 0) {
		msg.m_text = "no user";
		return msg;
	} 

	CourseInfo cinfo, *course;
	cinfo.courseID = sinfo->courseID;
	if (!(course = g_courseTable->FindCourse(&cinfo))) {
		msg.m_text = "no course";
		return msg;
	}
	sinfo->studentName = student->m_name;
	sinfo->courseName = course->courseName;
	sinfo->score = -1;
	msg = g_selectCourseTable->AddInfo(sinfo);
	if (msg.ok == 0)
		return msg;

	// 添加课程到学生课表
	return  student->AddCourse(course);
}

SysMSG SelectCourseModule::DeleteSelctCourse(SelectCourseInfo *sinfo)
{
	SysMSG msg;
	msg = g_selectCourseTable->DeleteInfo(sinfo);

	// 从学生课表删除
	StudentInfo sd;
	sd.m_id = sinfo->studentID;
	StudentInfo* user = (StudentInfo*)g_userTable->FindUser(&sd);
	if (user)
	{
		CourseInfo c;
		c.courseID = sinfo->courseID;
		user->getKebiao()->DeleteCourse(&c);
	}

	return msg;
}


SelectCourseTable* SelectCourseModule::getSelectCourseTable()
{
	assert(g_selectCourseTable != 0);
	return g_selectCourseTable;
}