
#include"studentSys.h"


Kebiao::Kebiao()
{
	m_kebiao = new vector<CourseInfo*>();
}

Kebiao::~Kebiao()
{
	for(auto i=m_kebiao->begin(); i != m_kebiao->end(); ++i) 
	if (*i)
		delete *i;
	delete m_kebiao;
}

SysMSG Kebiao::AddCourse(CourseInfo* cinfo)
{
	SysMSG msg;
	if (cinfo->courseID.length() == 0 || cinfo->courseName.length() == 0 ||
		cinfo->classTime.length() == 0 || cinfo->TeacherID.length() == 0 ||
		cinfo->TeacherName.length() == 0)
	{
		msg.m_text = "format error";
		return msg;
	}
	msg.m_text = "exist select course";

	for (auto i = m_kebiao->begin(); i != m_kebiao->end(); ++i)
	{
		assert(*i != 0);
		if (cinfo->courseID == (*i)->courseID)
			return msg;
	} 
	CourseInfo *c = new CourseInfo;
	*c = *cinfo;
	m_kebiao->push_back(c);
	msg.ok = 1;
	msg.m_text = "add course success";
	return msg;
}

SysMSG Kebiao::DeleteCourse(CourseInfo* cinfo)
{
	SysMSG msg;
	if (cinfo->courseID.length() == 0)
	{
		msg.m_text = "format error";
		return msg;
	}
	msg.m_text = "have not select the course";
	for (auto i = m_kebiao->begin(); i != m_kebiao->end(); )
	{
		assert(*i != 0);
		if (cinfo->courseID == (*i)->courseID)
		{
			if(*i) delete *i;
			i = m_kebiao->erase(i);
			msg.m_text = msgOK;
			msg.ok = 1;
			return msg;
		}
		else
			++i;
	}
	return msg;
}

vector<CourseInfo*> * Kebiao::getKebiao()
{
	return m_kebiao;
}

void Kebiao::print()
{
	/*fout << "---kebiao----" << endl;
	for (auto i = m_kebiao->begin(); i != m_kebiao->end(); ++i)
	{
		CourseInfo *c = (*i);
		fout << c->TeacherID << ' ' << c->TeacherName << ' ' << c->courseID << ' ' << c->courseName <<
			' ' << c->classTime << ' ' << endl;
	}*/

}
