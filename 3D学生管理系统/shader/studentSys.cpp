#include"studentSys.h"


StudentInfo::StudentInfo() {
	m_type = User_student;
	m_kebiao = new Kebiao;
}

StudentInfo::StudentInfo(string name, string sex, string c) : m_name(name), m_sex(sex), m_class(c) {
	m_type = User_student;
	m_kebiao = new Kebiao;
}

StudentInfo::~StudentInfo(){
	delete m_kebiao;
}

bool StudentInfo::isLegal() {
	return User::isLegal() && m_name.length() > 0 && m_id.length() > 0 &&
		(m_sex == "Å®" || m_sex == "ÄÐ") && m_class.length() > 0;
}

SysMSG StudentInfo::AddCourse(CourseInfo *cinfo)
{
	return m_kebiao->AddCourse(cinfo);
}





TeacherInfo::TeacherInfo() {
	m_type = User_teacher;
	m_kebiao = new Kebiao;
}

TeacherInfo::TeacherInfo(string name,string sex) : m_name(name), m_sex(sex) {
	m_type = User_teacher;
	m_kebiao = new Kebiao;
}
TeacherInfo::~TeacherInfo() { delete m_kebiao; }

 bool TeacherInfo::isLegal() {
	return User::isLegal() && m_name.length() > 0 && m_id.length() > 0 &&
		(m_sex == "ÄÐ" || m_sex == "Å®");
}

SysMSG TeacherInfo::AddCorse(CourseInfo *cinfo)
{
	return m_kebiao->AddCourse(cinfo);
}
