#pragma once


#include"d3dutil.h"
#include"drawgraph.h"
#include"Mesh.h"
#include"camera.h"


// input gobal
extern float g_skillspeed;
extern Camera* camera;


// gobal 
extern LPDIRECT3DDEVICE9 gdevice;
extern LPDIRECT3DTEXTURE9 skilltexture;



struct Chars;

struct SkillMesh 
{
	SkillMesh() {
	}
};

struct SkillTracer
{
	Chars *caster;
	D3DXVECTOR3 m_dir, m_pos;
	float speed;
	float validDis;


	SkillMesh *m_skillmesh;


	void Render() 
	{
		D3DXMATRIX world, scale, rot;
		D3DXMatrixTranslation(&world, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixScaling(&scale,0.5,0.5,0.5);

		// billiboard
		D3DXMatrixIdentity(&rot);
		D3DXMATRIX viewmat = camera->GetView();
		rot._11 = viewmat._11, rot._13 = viewmat._13;
		rot._31 = viewmat._31, rot._33 = viewmat._33;
		D3DXMatrixInverse(&rot, 0, &rot);

		//world = rot * scale * world;
		world =  scale * rot * world;
		gdevice->SetTransform(D3DTS_WORLD, &world);
		drawTexture(skilltexture);
	}
};


struct SkillController
{
	std::vector<SkillTracer*> m_skills;
	typedef std::vector<SkillTracer*>::iterator Sit;

	SkillController() { }
	~SkillController() {
		for(Sit it = m_skills.begin(); it != m_skills.end(); ++it)
			DELETE(*it);
	}

	void AddSkill(SkillTracer *s);
	void Update(float dt);
	void Render();

};