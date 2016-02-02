

#include"studentSys.h"

int CourseTable::MAXCOURSEID = 0;


CourseTable::CourseTable()
{
	m_courseTable = new vector<CourseInfo*>();
}

CourseTable::~CourseTable()
{
	for(auto i=m_courseTable->begin(); i!=m_courseTable->end(); ++i)
		if (*i)
			delete *i;
	delete m_courseTable;
}

SysMSG CourseTable::AddCourse(CourseInfo *cinfo)
{
	SysMSG msg;
	if (cinfo->courseName.length() == 0 || cinfo->TeacherID.length() == 0 ||
		cinfo->classTime.length() == 0)
	{
		msg.m_text = "format error";
		return msg;
	}

	for (auto i = m_courseTable->begin(); i != m_courseTable->end(); ++i)
	{
		if (cinfo->courseName == (*i)->courseName &&
			cinfo->TeacherID == (*i)->TeacherID &&
			cinfo->classTime == (*i)->classTime)
		{
			msg.m_text = "exist course";
			return msg;
		}
	}

	CourseInfo *c = new CourseInfo;
	c->courseID = tostring(MAXCOURSEID);  MAXCOURSEID++;
	c->courseName = cinfo->courseName;
	c->TeacherID = cinfo->TeacherID;
	c->TeacherName = cinfo->TeacherName;
	c->classTime = cinfo->classTime;
	m_courseTable->push_back(c);
	msg.ok = 1;
	msg.m_text = "add course success";
	return msg;
}

SysMSG CourseTable::DeleteCourse(CourseInfo *cinfo)
{
	assert(m_courseTable != 0);
	SysMSG msg;
	msg.m_text = "no course";
	for (auto i = m_courseTable->begin(); i != m_courseTable->end(); )
	{
		if (cinfo->courseID == (*i)->courseID)
		{
			if (*i){
				delete *i;
				i = m_courseTable->erase(i);
			}
			msg.ok = 1;
			msg.m_text = "delete course success";
			return msg;
		}
		else
			++i;
	}
	return msg;
}

CourseInfo* CourseTable::FindCourse(CourseInfo *cinfo)
{
	assert(m_courseTable != 0);
	CourseInfo  *res = 0;
	SysMSG msg;
	msg.m_text = "no course";
	for (auto i = m_courseTable->begin(); i != m_courseTable->end(); ++i)
		if (cinfo->courseID == (*i)->courseID || cinfo->courseName == (*i)->courseName)
			return *i;
	return res;
}



vector<CourseInfo*> * CourseTable::getCourseTable()
{
	assert(m_courseTable != 0);
	return m_courseTable;
}


void CourseTable::print()
{
	//fout << "------------------course table ------------------- " << endl;
	//fout << "tid - tname - cid - cname - time " << endl;
	//for (auto i = m_courseTable->begin(); i != m_courseTable->end(); ++i)
	//{
	//	CourseInfo *c = *i;
	//	fout << c->TeacherID << ' ' << c->TeacherName << ' ' << c->courseID << ' ' << c->courseName << ' '
	//		<< c->classTime << endl;
	//}
}
