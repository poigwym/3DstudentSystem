
#include"gui.h"


int GUIwindow::AddText(std::string name, int x, int y, int w, int h, char *bg)
{
	GUItext *c = new GUItext(device, w, h, name);
	c->m_type = Ctext;
	c->setX(x);
	c->setY(y);
	if(bg)
		c->SetBounding(bg);
	m_controls.push_back(c);
	return m_controls.size() - 1;
}

int GUIwindow::AddStaticText(std::string name, int x, int y, int w, int h, std::string tx, char *bg)
{
	GUIstaticText *c = new GUIstaticText(device, w, h, name);
	c->m_type = Cstext;
	c->setX(x);
	c->setY(y);
	c->SetText(tx);
	if (bg)
		c->SetBounding(bg);

	m_controls.push_back(c);
	return m_controls.size() - 1;
}


int GUIwindow::AddButton(std::string name, int x, int y, int w, int h, std::string tx, char *up, char *down)
{
	GUIbutton *b = new GUIbutton(device, w, h, name, tx);
	b->setX(x);
	b->setY(y);
	b->m_type = Cbutton;
	if (up)
		b->setBounding(up);
	m_controls.push_back(b);
	return m_controls.size() - 1;
}

void GUIwindow::AddChildGUI(GUIwindow *p)
{
	m_GUIchild.push_back(p);
}

GUIwindow * GUIwindow::FindChildGUI(std::string name)
{
	for (int i = 0; i<m_GUIchild.size();++i) 
	if (m_GUIchild[i]->m_name == name)
		return m_GUIchild[i];
	return 0;
}


GUIcontrol* GUIwindow::FindControl(std::string name, ControlType t)
{
	for (int i = 0; i < m_controls.size(); ++i)
	{
		if (m_controls[i]->m_type == t && m_controls[i]->m_name == name)
			return m_controls[i];
	} 
	return 0;
}

void GUIwindow::DeleteControl(int id)
{
	if (id < 0 || id >= m_controls.size())  return;
	m_controls.erase(m_controls.begin() + id);
}



void GUIwindow::ProcessMSG(UINT imsg, WPARAM wparam, LPARAM lparam)
{
	if (m_vis == false) return;



	bool mouseDown = 0;
	switch (imsg)
	{
		case WM_MOUSEMOVE:
		{
											 mouseX = LOWORD(lparam);
											 mouseY = HIWORD(lparam);
		}
		break;
		case WM_LBUTTONDOWN: 
			mouseDown = 1;
			break;
		case WM_LBUTTONUP: 
			mouseDown = 0;
			break;
		case WM_KEYDOWN:
			//ProcessKey(wparam, lparam);
			break;
		case WM_CHAR:
			ProcessKey(wparam, lparam);
				break;
		case WM_KEYUP:
			break;
		default:
			break;
	}
	ProcessMouse(mouseX, mouseY, mouseDown);


	// process child
	for (int i = 0; i < m_GUIchild.size(); ++i)
		m_GUIchild[i]->ProcessMSG(imsg, wparam, lparam);
}



void GUIwindow::ProcessKey(WPARAM wparam, LPARAM lparam)
{
	if (m_focusID + 1)
	{
		m_controls[m_focusID]->ProcessKey(wparam, lparam);
	}
}

void GUIwindow::ProcessMouse(int x, int y, bool isdown)
{
	// 如果点击鼠标，focus必须重置
	if (isdown)
		m_focusID = -1;


	for (int i = 0; i < m_controls.size(); ++i)
	{
		GUIcontrol *c = m_controls[i];
		if (c->m_type == Ctext) 
		{ 
			if (isdown)
			{
				c->m_focus = 0;					// 点击才重新判断
				if (c->m_x <= x &&  x <= c->m_x + c->GetWidth() &&
					c->m_y <= y && y <= c->m_y + c->GetHeight())
				{
					c->m_focus = 1;
					m_focusID = i;
					m_controls[m_focusID]->ProcessMouse(x, y, isdown);
				}
			}
		}
		else if(c->m_type == Cbutton)
		{
			GUIbutton *b = dynamic_cast<GUIbutton*>(c);
			b->m_focus = 0;
			b->m_isClick = 0;
			if (b->m_x <= x &&  x <= b->m_x + b->GetWidth() &&
				b->m_y <= y && y <= b->m_y + b->GetHeight())
			{
				b->m_focus = 1;
				if (isdown) {
					m_focusID = i;
					m_controls[m_focusID]->ProcessMouse(x, y, isdown);
				}
				// else if
			}
		}
	}
}



GUIcontrol* GUIwindow::GetControl(int id)
{
	if (id < 0 || id >= m_controls.size()) return 0;
	return m_controls[id];
}



void GUIwindow::AddEvent(EventPtr p)
{
	m_events.push_back(p);
}


void GUIwindow::setVis(bool v)
{
	m_vis = v;
	if (!v)
	{
		for (int i = 0; i < m_GUIchild.size(); ++i)
			m_GUIchild[i]->setVis(v);
	}
}





void GUIwindow::OnUpdate()
{
	if (m_vis == false) return;


	for (int i = 0; i < m_events.size(); ++i)
		m_events[i](this);

	// update child
	for (int i = 0; i < m_GUIchild.size(); ++i)
		m_GUIchild[i]->OnUpdate();
}


void GUIwindow::OnRender()
{
	if (m_vis == false) return;

	for (int i = 0; i < m_controls.size(); ++i)
		m_controls[i]->OnRender();

	// render child
	for (int i = 0; i < m_GUIchild.size(); ++i)
		m_GUIchild[i]->OnRender();
}





GUIwindow::~GUIwindow(){
	for (auto i = m_controls.begin(); i != m_controls.end(); ++i) {
		if(*i)
			delete *i;
	}
	if (pFont)  { pFont->Release(); pFont = 0; }

	for(auto i = m_GUIchild.begin(); i != m_GUIchild.end(); ++i) 
	if (*i)
		delete *i;
}


