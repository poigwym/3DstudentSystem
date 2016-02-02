

#pragma once



// ״̬��
enum StateType {
	CSstand = 0,
	CSwalk, 
	CSattack,
	CSdie ,
	CSbeated,
	CSevade,
	CSfindEnemy
};
const int Nstate = 7;



struct Chars;
class CharsState;
class StateMgr
{
	friend class CharsState;
private:
	CharsState *m_curstate;
	CharsState *m_state[Nstate];
public:
	Chars *cs;											// ��ɫ

	StateMgr(Chars *cs);
	~StateMgr();
	CharsState* getState(int id) { return m_state[id]; }
	CharsState* getCurstate() { return m_curstate; }
	void setState(int id) { m_curstate = m_state[id]; }
	void update(float dt);
};


class CharsState
{
protected:
	StateMgr *mgr;
	StateType m_type;
public:
	CharsState(StateMgr *mgr) : mgr(mgr) {}
	virtual ~CharsState() {}
	virtual void update(float dt) {}
	StateType getType() { return m_type; }

	// ״̬ת������
	bool ToStand();
	bool ToEvade();
	bool ToBeated();
	bool ToWalk();
	bool ToFindEnermy();
	bool ToAttack();
};


// ------------------------ ��ɫ״̬  ------------------------------
// stand
class CharsStand : public CharsState
{ 
public:
	CharsStand(StateMgr *mgr) : CharsState(mgr) { m_type = CSstand;  }
	~CharsStand() {}
	virtual void  update(float dt);
};

// walk
class CharsWalk : public CharsState
{
public:
	CharsWalk(StateMgr *mgr) : CharsState(mgr) { m_type = CSwalk; }
	~CharsWalk() {}
	virtual void update(float dt);
};

// �ر�
class CharsEvade : public CharsState
{
public:
	CharsEvade(StateMgr *mgr) : CharsState(mgr) { m_type = CSevade;  }
	~CharsEvade() {}
	virtual void update(float dt);
};

// ����
class CharsBeated : public CharsState
{
	int curframe;
public:
	CharsBeated(StateMgr *mgr) : CharsState(mgr), curframe(1){ m_type = CSbeated; }
	~CharsBeated() {}
	virtual void update(float dt);
};

// �ѵ�

class CharsFindEnermy : public CharsState
{
public:
	CharsFindEnermy(StateMgr *mgr) : CharsState(mgr) { m_type = CSfindEnemy; }
	~CharsFindEnermy() {}
	virtual void update(float dt);
};



class CharsAttack : public CharsState
{
	int restframe;
public:
	CharsAttack(StateMgr *mgr) : CharsState(mgr), restframe(3) { m_type = CSattack; }
	~CharsAttack() {}
	virtual void update(float dt);
};
