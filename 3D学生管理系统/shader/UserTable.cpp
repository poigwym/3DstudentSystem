

#include"studentSys.h"

int UserTable::MAXID = 0;

UserTable::UserTable()
{
	m_adminTable = new AdminTable;
	m_studentTable = new StudentTable;
	m_teacherTable = new TeacherTable;
}

UserTable::~UserTable()
{
	for(auto i=m_adminTable->begin(); i != m_adminTable->end(); ++i) 
		if (i->second)
			delete i->second;
	for (auto i = m_studentTable->begin(); i != m_studentTable->end(); ++i)
		if (i->second)
			delete i->second;
	for (auto i = m_teacherTable->begin(); i != m_teacherTable->end(); ++i)
		if (i->second)
			delete i->second;

	delete m_adminTable;
	delete m_studentTable;
	delete m_teacherTable;
}

AdminTable* UserTable::getAdminTable()
{
	assert(m_adminTable != 0);
	return m_adminTable;
}


StudentTable*  UserTable::getStudentTable()
{
	assert(m_studentTable != 0);
	return m_studentTable;
}

TeacherTable*  UserTable::getTeacherTable()
{
	assert(m_teacherTable != 0);
	return m_teacherTable;
}

SysMSG  UserTable::AddUser(User *user)
{
	assert(m_adminTable != 0 && m_studentTable != 0 && m_teacherTable != 0);
	SysMSG msg;
	msg.ok = 0;
	msg.m_text = "format error";

	// check ...
	if (user->m_account.length() == 0 || user->m_key.length() == 0) {
		return msg;
	}

	switch (user->m_type)
	{
		case User_admin:
		{
				AdminInfo *u = dynamic_cast<AdminInfo*>(user);
				if (u->m_name.length() == 0)
					return msg;
				assert(u != 0);
				AdminInfo *ad = new AdminInfo(u->m_name);
				for (auto i = m_adminTable->begin(); i != m_adminTable->end(); ++i)
				{
					if (u->m_account == i->second->m_account)
					{
						msg.m_text = "exist account";
						return msg;
					}
				}


				ad->m_id = tostring(MAXID);
				ad->m_account = u->m_account;
				ad->m_key = u->m_key;
				m_adminTable->insert(make_pair(ad->m_id, ad));
				msg.m_text = "add admin success";
				break;
		}
		case User_student:
		{
				StudentInfo *u = dynamic_cast<StudentInfo*>(user);
				assert(u != 0);
				for (auto i = m_studentTable->begin(); i != m_studentTable->end(); ++i)
				{
					if (u->m_account == i->second->m_account)
					{
						msg.m_text = "exist account";
						return msg;
					}
				}
				if (u->m_name.length() == 0 || u->m_sex.length() == 0 ||
					u->m_class.length() == 0)
					return msg;
				StudentInfo *s = new StudentInfo(u->m_name, u->m_sex, u->m_class);
				s->m_id = tostring(MAXID);
				s->m_account = u->m_account;
				s->m_key = u->m_key;
				m_studentTable->insert(make_pair(s->m_id, s));
				msg.m_text = "add student success";
				break;
		}
		case User_teacher:
		{
			TeacherInfo *u = dynamic_cast<TeacherInfo*>(user);
			assert(u != 0);
			for (auto i = m_teacherTable->begin(); i != m_teacherTable->end(); ++i)
			{
				if (u->m_account == i->second->m_account)
				{
					msg.m_text = "exist account";
					return msg;
				}
			}
			if (u->m_name.length() == 0 || u->m_sex.length() == 0 )
				return msg;
			TeacherInfo *t = new TeacherInfo(u->m_name,  u->m_sex);
			t->m_id = tostring(MAXID);
			t->m_account = u->m_account;
			t->m_key = u->m_key;
			m_teacherTable->insert(make_pair(t->m_id, t));
			msg.m_text = "add teacher success";
			break;
		}
		default: {
			return msg;
		}
	}
	MAXID++; 
	msg.ok = 1;
	return msg;
}

SysMSG  UserTable::DeleteUser(User  *user)
{
	SysMSG msg;
	msg.ok = 0;
	msg.m_text = "no user";

	// check ...
	switch (user->m_type)
	{
		case User_admin:
		{
				AdminInfo *ad = dynamic_cast<AdminInfo*> (user);
				assert(ad != 0);
				for (auto i = m_adminTable->begin(); i != m_adminTable->end(); )
				{
					if (i->second->m_id == ad->m_id)
					{
						delete i->second;
						i = m_adminTable->erase(i);
						msg.ok = 1;
						msg.m_text = "delete user success";
						return msg;
					}
					else
						++i;
				}
				break;
		}
		case User_student:
		{
				StudentInfo *s = dynamic_cast<StudentInfo*>(user);
				assert(s != 0);
				for (auto i = m_studentTable->begin(); i != m_studentTable->end(); ) {
					if (i->second->m_id == s->m_id) {
						delete i->second;
						i = m_studentTable->erase(i);
						msg.ok = 1;
						msg.m_text = "delete user success";
						return msg;
					}
					else
						++i;
				}
				break;
		}
		case User_teacher:
		{
				TeacherInfo *t = dynamic_cast<TeacherInfo*>(user);
				assert(t != 0);
				for (auto i = m_teacherTable->begin(); i != m_teacherTable->end();)
				{
					if (i->second->m_id == t->m_id)
					{
						delete i->second;
						i = m_teacherTable->erase(i);
						msg.ok = 1;
						msg.m_text = "delete user success";
						return msg;
					}
					else
						++i;
				}
				break;
		}
		default:
			break;
	}
	return msg;
}

SysMSG  UserTable::QueryUser(User *user)
{
	SysMSG msg;
	msg.m_text = msgER;
	if (user->m_type == User_admin)
	{
		msg.ok = 1;
		msg.m_text = msgOK;
	}
	return msg;
}

User *UserTable::CheckAccount(User *user)
{
	if (user->m_type == User_admin) {
		for (auto i = m_adminTable->begin(); i != m_adminTable->end(); ++i)
		if (i->second->m_account == user->m_account &&
			i->second->m_key == user->m_key)
			return i->second;
	}
	else if (user->m_type == User_student)
	{
		for (auto i = m_studentTable->begin(); i != m_studentTable->end(); ++i)
		if (i->second->m_account == user->m_account &&
			i->second->m_key == user->m_key)
			return i->second;
	}
	else if (user->m_type == User_teacher)
	{
		for (auto i = m_teacherTable->begin(); i != m_teacherTable->end(); ++i)
		if (i->second->m_account == user->m_account &&
			i->second->m_key == user->m_key)
		{
			return i->second;
		}
	} 
	else
	{
	}
	return 0;
}



User*  UserTable::FindUser(User *user)
{
	User *res = 0;
	if (user == 0) return res;
	switch (user->m_type)
	{
		case User_admin:
		{
			AdminInfo *ad = dynamic_cast<AdminInfo*> (user);
			assert(ad != 0);
			res = (*m_adminTable)[ad->m_id];
			if (res) return res;
		}
		break;
		case User_student:
		{
			StudentInfo *s = dynamic_cast<StudentInfo*>(user);
			assert(s != 0);
			res = (*m_studentTable)[s->m_id];
			if (res) return res;
		}
			break;
		case User_teacher:
		{
				TeacherInfo *t = dynamic_cast<TeacherInfo*>(user);
				assert(t != 0);
				res = (*m_teacherTable)[t->m_id];
				if (res) return res;
		}
			break;
		default:
			break;
	}
	return res;
}



void UserTable::print()
{
	/*fout << " ---------------user table ------------- " << endl;
	fout << "admin : id - name" << endl;
	for (auto i = m_adminTable->begin(); i != m_adminTable->end(); ++i)
		fout << i->second->m_id << ' ' << i->second->m_name << endl;
	fout << "-------------------------------------" << endl;
	fout << "student : id - name - " << endl;
	for (auto i = m_studentTable->begin(); i != m_studentTable->end(); ++i)
	{
		fout << "---- user  ";
		StudentInfo *sd = i->second;
		fout << sd->m_name << "-------------" << endl;
		fout << sd->m_id << ' ' << sd->m_name << endl;
		Kebiao *k = sd->getKebiao();
		k->print();
		fout << " ---------------------- " << endl;
	}

	fout << " --------------------------------------" << endl;
	fout << "teacher : id - name - " << endl;
	for (auto i = m_teacherTable->begin(); i != m_teacherTable->end(); ++i)
	{
		TeacherInfo *sd = i->second;
		fout << sd->m_id << ' ' << sd->m_name << endl;
		sd->getKebiao()->print();
	}*/
}
