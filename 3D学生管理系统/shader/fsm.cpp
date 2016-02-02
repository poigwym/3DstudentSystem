

#include"fsm.h"


// 0 is null state

extern ofstream Log;
FSMstate::FSMstate(int id) 
{
	m_stateid = id;
}

FSMstate::~FSMstate() {
}

void FSMstate::AddTransform(int input, int tostate) 
{
	m_input.push_back(input);
	m_toState.push_back(tostate);
}

int FSMstate::GetTransform(int inputid)
{
	for(int i=0;i<m_input.size();++i) 
		if(m_input[i] == inputid) 
			return m_toState[i];
	return 0;
}


int FSMstate::GetID() 
{
	return m_stateid;
}



// ------------------ FSM class ----------------
FSMclass::FSMclass() 
{
	ma.clear();
	m_curstate = 0;
}

FSMclass::~FSMclass()
{
	for(STit it = ma.begin(); it!=ma.end(); ++it) 
		DELETE(it->second);
}

void FSMclass::AddState(FSMstate *st) 
{
	if(ma.find(st->GetID()) == ma.end())
	{
		Log<<"ins state "<<st->GetID()<<endl;
		ma[st->GetID()] = st;
	}
}

void FSMclass::DelState(int stateid)
{
	if(ma.find(stateid) != ma.end()) 
		delete ma[stateid];
}

void FSMclass::SetTransform(int in)
{
	if(ma.find(m_curstate) != ma.end()) {
		int nextstate = ma[m_curstate]->GetTransform(in);
		Log <<"trans" << m_curstate <<' '<< nextstate << endl;
		if(nextstate) 
			m_curstate = nextstate;
	}
	else 
		Log << "no this state"<< endl;
}