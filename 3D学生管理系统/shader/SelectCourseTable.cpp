


#include"studentSys.h"


SelectCourseTable::SelectCourseTable()
{
	m_selectCourseTable = new vector<SelectCourseInfo*>;
}

SelectCourseTable::~SelectCourseTable()
{

	for(auto i = m_selectCourseTable->begin(); i != m_selectCourseTable->end(); ++i) 
	if (*i)
		delete *i;
	delete m_selectCourseTable;
}

SysMSG SelectCourseTable::AddInfo(SelectCourseInfo *sinfo)
{
	assert(m_selectCourseTable != 0);

	SysMSG msg;
	if (sinfo->studentID.length() == 0 || sinfo->courseID.length() == 0)
	{
		msg.m_text = "format error";
		return msg;
	}
	msg.m_text = msgER;
	for (auto i = m_selectCourseTable->begin(); i != m_selectCourseTable->end(); ++i)
	{
		if (sinfo->studentID == (*i)->studentID &&
			sinfo->courseID == (*i)->courseID)
		{
			msg.m_text = "exist select course";
			return msg;
		}
	} 
	SelectCourseInfo *newinfo = new SelectCourseInfo;
	newinfo->courseID = sinfo->courseID;
	newinfo->courseName = sinfo->courseName;
	newinfo->studentID = sinfo->studentID;
	newinfo->studentName = sinfo->studentName;
	newinfo->score = 0;
	m_selectCourseTable->push_back(newinfo);
	msg.m_text = "select course success";
	msg.ok = 1;
	return msg;
}


SysMSG SelectCourseTable::DeleteInfo(SelectCourseInfo *sinfo)
{
	assert(m_selectCourseTable != 0);

	SysMSG msg;
	if (sinfo->studentID.length() == 0 || sinfo->courseID.length() == 0)
	{
		msg.m_text = "format error";
		return msg;
	}
	msg.m_text = "no this selectCourse ";
	for (auto i = m_selectCourseTable->begin(); i != m_selectCourseTable->end();)
	{
		if (sinfo->studentID == (*i)->studentID &&
			sinfo->courseID == (*i)->courseID)
		{
			delete *i;
			i = m_selectCourseTable->erase(i);
			msg.m_text = "deselect course success";
			msg.ok = 1;
			return msg;
		}
		else
			++i;
	}
	return msg;
}


SysMSG SelectCourseTable::DeleteInfoOfStudent(StudentInfo *user)
{
	SysMSG msg;
	msg.ok = 1;
	msg.m_text = msgOK;
	for (auto i = m_selectCourseTable->begin(); i != m_selectCourseTable->end();)
	{
		if ((*i)->studentID == user->m_id) {
			delete *i;
			i = m_selectCourseTable->erase(i);
		}
		else
			++i;
	}
	return msg;
}

SysMSG SelectCourseTable::DeleteInfoOfCourse(CourseInfo* cinfo)
{
	SysMSG msg;
	msg.ok = 1;
	msg.m_text = msgOK;
	for (auto i = m_selectCourseTable->begin(); i != m_selectCourseTable->end();)
	{
		if ((*i)->courseID == cinfo->courseID)
			i = m_selectCourseTable->erase(i);
		else
			++i;
	}
	return msg;
}

SelectCourseInfo* SelectCourseTable::FinfSelectInfo(SelectCourseInfo* sinfo)
{
	SelectCourseInfo * res = 0;
	for (auto i = m_selectCourseTable->begin(); i != m_selectCourseTable->end(); ++i)
	{
		SelectCourseInfo *t = *i;
		if (t->courseID == sinfo->courseID &&
				t->studentID == sinfo->studentID )
			return t;
	}
	return res;
}



vector<SelectCourseInfo*> * SelectCourseTable::getSelectCourseTable()
{
	assert(m_selectCourseTable != 0);
	return m_selectCourseTable;
}

