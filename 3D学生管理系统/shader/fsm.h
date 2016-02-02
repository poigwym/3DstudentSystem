#pragma once

#include"d3dutil.h"

struct FSMstate
{
	int m_stateid;
	vector<int> m_input, m_toState;

	FSMstate(int id);														// ×´Ì¬Ãû
	~FSMstate();			
	void AddTransform(int input, int tostate);	// ²åÈë×ª»»±ß
	int GetTransform(int input);								// ÊäÈë->ÏÂÒ»×´Ì¬
	int GetID();																
};

struct FSMclass
{
	int m_curstate;
	std::map<int, FSMstate*> ma;
	typedef std::map<int, FSMstate*>::iterator STit;

	FSMclass();
	~FSMclass();

	void AddState(FSMstate *st);								// ²åÈë×´Ì¬
	void DelState(int stateid);									// É¾³ý×´Ì¬
	void SetTransform(int in);									// ×´Ì¬×ª»»
};