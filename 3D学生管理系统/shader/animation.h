#pragma once

#include"d3dutil.h"


extern ID3DXEffect *gAnimationEffect;
extern LPDIRECT3DDEVICE9 gdevice;


struct Bone : public D3DXFRAME {
	D3DXMATRIX combmat;															// 骨头的世界矩阵
	Bone() { memset(this, 0, sizeof(*this)); }
};


struct BoneMesh : public  D3DXMESHCONTAINER {
	ID3DXMesh *OrgMesh;
	std::vector<D3DMATERIAL9> Mtrls;
	std::vector<IDirect3DTexture9*> Textures;

	DWORD GroupNum;																	// groups num;
	D3DXATTRIBUTERANGE *AttributeTable;							
	D3DXMATRIX **CombMat;														// 指向bone的combmat
	D3DXMATRIX *BoneOffsetMat;											// 权重矩阵。。
	D3DXMATRIX *CurrentMat;													// 网格顶点的世界矩阵
	BoneMesh() { memset(this, 0, sizeof(*this)); }
};


class BoneHierarchy : public ID3DXAllocateHierarchy {
public:
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);
	STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR  Name,
																	CONST D3DXMESHDATA		  *pMeshData,
																	CONST D3DXMATERIAL		  *pMaterials,
																	CONST D3DXEFFECTINSTANCE  *pEffectInstances,
																	DWORD                     NumMaterials,
																	CONST DWORD				  *pAdjacency,
																	LPD3DXSKININFO			  pSkinInfo,
																	LPD3DXMESHCONTAINER *ppNewMeshContainer);
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME frame);
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER frame);
	
};


struct SkinMesh {
	Bone *m_boneroot;
	ID3DXAnimationController *player;

	SkinMesh(LPCSTR filename);
	~SkinMesh();

	void SetupMatrixPtr(Bone *bone, Bone *root);
	void UpdateMatrix(Bone *b, D3DXMATRIX *mat);
	void RenderBone(Bone *bone);

	// set pos and dir
	void Move(float x, float y, float z);
	void Move(D3DXMATRIX world);
	void Render() { RenderBone(m_boneroot); } 


	// 轨道动画
	int GetAnimId(const std::string &name);
	void extractAnim(std::vector<std::string> &motionName); // extract names of animation
	void InsMotion(const std::string &name);								// insert a motion with name
	void EnableTrack(int track, bool v);
	void SetTrackWeight(int track, float w);
	void SetTrackSpeed(int track, float speed);
	void Reset();
	ID3DXAnimationController* ClonePlayer();								// 
	void Setpose(D3DXMATRIX *mat, float tick);
	void Display(float dt);																	// play animation
};