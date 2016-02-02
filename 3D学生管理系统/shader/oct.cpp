
#include"oct.h"

extern LPDIRECT3DDEVICE9 gdevice;


extern ID3DXMesh *box;


int OCT::dx[8] = { 1,-1,-1,1,1,-1,-1,1 };
int OCT::dy[8] = { 1,1,1,1,-1,-1,-1,-1 };
int OCT::dz[8] = { 1,1,-1,-1,1,1,-1,-1 };


bool OCT::ispushdown(const D3DXVECTOR3 &subpos, const D3DXVECTOR3 &subbox, BHV *v)
{
	// curren box local space
	D3DXVECTOR3 o = v->m_pos - subpos;
	D3DXVECTOR3 max_pos = o + v->m_box;
	D3DXVECTOR3 min_pos = o - v->m_box;
	if(max_pos.x > subbox.x || max_pos.y > subbox.y || max_pos.z > subbox.z ||
		 min_pos.x < -subbox.x || min_pos.y < -subbox.y || min_pos.z < -subbox.z )
			return 0;
	return 1;
}


void OCT::Ins(BHV *v)
{
	m_objs.push_back(v);
	// pushdown
	if(m_objs.size() <= m_maxn || m_lv == 0 || m_maxn < 3)
		return;
	
	// look which quater to push
	for(int j=0;j<m_objs.size();++j)
	{
		for(int i=0;i<8;++i) 
		{
			D3DXVECTOR3 subpos = m_pos + D3DXVECTOR3(0.5f*m_box.x*dx[i], 0.5f*m_box.y*dy[i], 0.5f*m_box.z*dz[i]);
			D3DXVECTOR3 subbox = m_box/2;
			if(ispushdown(subpos, subbox, m_objs[j])) {
				if(!m_ch[i]) 
					m_ch[i] = new OCT(subpos, subbox, m_lv-1, m_maxn/2);
				m_ch[i]->Ins(m_objs[j]);
			}
		}
	}
	m_objs.clear();

}

void OCT::outputframework()
{
	D3DXMATRIX world;
	D3DXMatrixTranslation(&world, 0,0,0);
	gdevice->SetTransform(D3DTS_WORLD, &world);
	int i,j,n=m_corner.size();
	for(i=0;i<n;++i)
		for(j=i+1;j<n;++j) {
			float len=D3DXVec3Length(&(m_corner[i]-m_corner[j]));
			if(len == 2*m_box.x || len == 2*m_box.y || len == 2*m_box.z)
				drawline(m_corner[i], m_corner[j]);
		}

	for(i=0;i<8;++i) 
		if(m_ch[i]) 
			m_ch[i]->outputframework();
}

void OCT::outputobj() 
{
	// note here 
	// the father box's objs have been clear
	for(int i=0;i<m_objs.size();++i) 
		m_objs[i]->render();
	for(int i=0;i<8;++i) 
		if(m_ch[i])
			m_ch[i]->outputobj();
}


void OCT::debugbuild()
{
	if(m_lv == 0 || m_maxn < 3) return;
	for(int i=0;i<8;++i) {
		D3DXVECTOR3 subpos = m_pos + D3DXVECTOR3(0.5f*m_box.x*dx[i], 0.5f*m_box.y*dy[i], 0.5f*m_box.z*dz[i]);
		D3DXVECTOR3 subbox = m_box / 2;
		if(!m_ch[i]) 
			m_ch[i] = new OCT(subpos, subbox, m_lv - 1, m_maxn / 2);
		m_ch[i]->debugbuild();
	}
}
void OCT::debugoutput() 
{
	D3DXMATRIX world, scale;

	// output framework
	D3DXMatrixTranslation(&world, 0, 0, 0);
	gdevice->SetTransform(D3DTS_WORLD, &world);
	int i, j, n = m_corner.size();
	for (i = 0;i<n;++i)
		for (j = i + 1;j<n;++j) {
			float len = D3DXVec3Length(&(m_corner[i] - m_corner[j]));
			if (len == 2 * m_box.x || len == 2 * m_box.y || len == 2 * m_box.z)
				drawline(m_corner[i], m_corner[j]);
		}

	// output point
	drawbox(m_pos, D3DXVECTOR3(0.1,0.1,0.1));

	// child
	for(int i=0;i<8;++i) 
		if(m_ch[i])
			m_ch[i]->debugoutput();
}

