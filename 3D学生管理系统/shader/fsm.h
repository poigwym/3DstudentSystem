#pragma once

#include"d3dutil.h"

struct FSMstate
{
	int m_stateid;
	vector<int> m_input, m_toState;

	FSMstate(int id);														// ״̬��
	~FSMstate();			
	void AddTransform(int input, int tostate);	// ����ת����
	int GetTransform(int input);								// ����->��һ״̬
	int GetID();																
};

struct FSMclass
{
	int m_curstate;
	std::map<int, FSMstate*> ma;
	typedef std::map<int, FSMstate*>::iterator STit;

	FSMclass();
	~FSMclass();

	void AddState(FSMstate *st);								// ����״̬
	void DelState(int stateid);									// ɾ��״̬
	void SetTransform(int in);									// ״̬ת��
};