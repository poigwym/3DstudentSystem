
#include"SysModule.h"



LogModule::LogModule(UserTable *g_userTable) :g_userTable(g_userTable)
{
}

LogModule::~LogModule()
{
}

User *LogModule::Login(User *user)
{
	User *res = 0;
	assert(g_userTable != 0);
	if (user->m_account.length() == 0 || user->m_key.length() == 0 || 
		 !(user->m_type == User_admin || user->m_type == User_student || user->m_type == User_teacher))
	{
		return res;
	}

	return g_userTable->CheckAccount(user);
}

SysMSG LogModule::Logout(User *user)
{
	SysMSG msg;
	msg.ok = 1;
	msg.m_text = "logout success";
	return msg;
}


