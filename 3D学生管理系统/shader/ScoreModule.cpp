
#include"SysModule.h"

ScoreModule::ScoreModule(UserTable *g_userTable, CourseTable *g_courseTable, 
	SelectCourseTable *g_selectCourseTable) : g_userTable(g_userTable), 
	g_courseTable(g_courseTable), g_selectCourseTable(g_selectCourseTable)
{


} 

ScoreModule::~ScoreModule()
{

}

SelectCourseTable *ScoreModule::getScoreTable()
{
	return g_selectCourseTable;
}

SysMSG ScoreModule::UpdateScore(SelectCourseInfo *sinfo)
{
	SysMSG msg;
	msg.m_text = "no selectInfo";
	SelectCourseInfo *tmp = g_selectCourseTable->FinfSelectInfo(sinfo);
	if (!tmp) return msg;

	tmp->score = sinfo->score;
	msg.ok = 1;
	msg.m_text = "update score success";
	return msg;
}


SysMSG ScoreModule::FindScore(SelectCourseInfo *sinfo)
{
	SysMSG msg;
	msg.m_text = "no selectInfo";
	SelectCourseInfo *tmp = g_selectCourseTable->FinfSelectInfo(sinfo);
	if (!tmp) 
		return msg;

	msg.ok = 1;
	char score[22];
	sprintf(score, "%.2f", tmp->score);
	msg.m_text = score;
	return msg;
}
