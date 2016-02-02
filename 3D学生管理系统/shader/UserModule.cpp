
#include"SysModule.h"

UserMoudle::UserMoudle(UserTable *g_userTable, SelectCourseTable *g_selectCourseTable) : g_userTable(g_userTable), g_selectCourseTable(g_selectCourseTable)
{
}

UserMoudle::~UserMoudle()
{

}

SysMSG UserMoudle::AddUser(User *user)
{
	assert(g_userTable != 0 && g_selectCourseTable != 0);
	return g_userTable->AddUser(user);
}

SysMSG UserMoudle::DeleteUser(User* user)
{
	SysMSG msg;
	msg = g_userTable->DeleteUser(user);
	if (!msg.ok) return msg;
	if(user->m_type == User_student)
		g_selectCourseTable->DeleteInfoOfStudent((StudentInfo*) user);
	return msg;
}

User* UserMoudle::FindUser(User *u)
{
	return g_userTable->FindUser(u);
}


UserTable* UserMoudle::getUserTable()
{
	return g_userTable;
}
