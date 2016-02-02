
#include"animation.h"


ID3DXEffect *gAnimationEffect;

#define onlyskinmesh 0

char *meshpath = "meshes/soldier/";
HRESULT BoneHierarchy :: CreateFrame(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame) {
	Bone *b = new Bone;

	if(Name) {
		b->Name = new char[strlen(Name)+1];
		strcpy(b->Name, Name);
	}
	D3DXMatrixIdentity(&b->TransformationMatrix);
	D3DXMatrixIdentity(&b->combmat);
	*ppNewFrame = b;
	return S_OK;

}

HRESULT BoneHierarchy::CreateMeshContainer (THIS_ LPCSTR  Name,
																						CONST D3DXMESHDATA		  *pMeshData,
																						CONST D3DXMATERIAL		  *pMaterials,
																						CONST D3DXEFFECTINSTANCE  *pEffectInstances,
																						DWORD                     NumMaterials,
																						CONST DWORD				  *pAdjacency,
																						LPD3DXSKININFO			  pSkinInfo,
																						LPD3DXMESHCONTAINER *ppNewMeshContainer) {
	*ppNewMeshContainer = 0;

	BoneMesh *bonemesh = new BoneMesh;

	// copy mesh
	bonemesh->MeshData.Type = pMeshData->Type;
	bonemesh->OrgMesh = pMeshData->pMesh;
	bonemesh->OrgMesh->AddRef();   // +1

	IDirect3DDevice9 *cdevice;
	pMeshData->pMesh->GetDevice(&cdevice);

	// textures of meshes
	for(int i=0; i<NumMaterials; ++i){
		D3DXMATERIAL mtrl;
		memcpy(&mtrl, &pMaterials[i], sizeof(D3DXMATERIAL));
		bonemesh->Mtrls.push_back(mtrl.MatD3D);

		IDirect3DTexture9 *texture = 0;
		if(mtrl.pTextureFilename) {
			char name[199];
			strcpy(name, meshpath);
			strcat(name, mtrl.pTextureFilename);
			D3DXCreateTextureFromFile(cdevice, name, &texture);
		}
		bonemesh->Textures.push_back(texture);
	}

	// is skinmesh ?
	if(pSkinInfo) {
		bonemesh->pSkinInfo = pSkinInfo;
		pSkinInfo->AddRef(); // +1

		// convert to blend vertex mesh 
		DWORD maxVertInfluences = 0;
		DWORD numBoneComboEntries = 0;
		ID3DXBuffer* boneComboTable = 0;

		pSkinInfo->ConvertToIndexedBlendedMesh(
			pMeshData->pMesh,
			D3DXMESH_MANAGED | D3DXMESH_WRITEONLY,
			35,
			0, // ignore adjacency in
			0, // ignore adjacency out
			0, // ignore face remap
			0, // ignore vertex remap
			&maxVertInfluences,
			&numBoneComboEntries,
			&boneComboTable,
			&bonemesh->MeshData.pMesh);
			boneComboTable->Release();

		// attribute table
		bonemesh->MeshData.pMesh->GetAttributeTable(0, &bonemesh->GroupNum);
		bonemesh->AttributeTable = new D3DXATTRIBUTERANGE[bonemesh->GroupNum];
		bonemesh->MeshData.pMesh->GetAttributeTable(bonemesh->AttributeTable, 0);

		// create bone offset matrix 
		int bonenum = pSkinInfo->GetNumBones();
		bonemesh->BoneOffsetMat = new D3DXMATRIX[bonenum];
		bonemesh->CurrentMat = new D3DXMATRIX[bonenum];
		for(int i=0; i< bonenum; ++i)
			bonemesh->BoneOffsetMat[i] = *(bonemesh->pSkinInfo->GetBoneOffsetMatrix(i));
	}
	*ppNewMeshContainer = bonemesh;
	return S_OK;
}

// 让系统调用 删除每个骨头
HRESULT  BoneHierarchy::DestroyFrame(THIS_ LPD3DXFRAME frame) {
	if(!frame) return S_OK;
	DELETEARRAY(frame->Name);
	if(frame->pMeshContainer)
		DestroyMeshContainer(frame->pMeshContainer);
	DestroyFrame(frame->pFrameFirstChild);
	DestroyFrame(frame->pFrameSibling);
	DELETE(frame);
	return S_OK;
}

// 让系统调用
HRESULT BoneHierarchy::DestroyMeshContainer(THIS_ LPD3DXMESHCONTAINER meshcontainer) {
	UINT iMaterial;
	BoneMesh *bonemesh= (BoneMesh*)meshcontainer;

	DELETE(bonemesh->Name);
	DELETE(bonemesh->pAdjacency);
	DELETE(bonemesh->pMaterials);

	for(int i=0; i<(int)bonemesh->Textures.size();++i) 
		RELEASE(bonemesh->Textures[i]);
	// release all the allocated textures
	DELETEARRAY(bonemesh->CombMat);
	DELETEARRAY(bonemesh->BoneOffsetMat);
	DELETEARRAY(bonemesh->CurrentMat);
	RELEASE(bonemesh->MeshData.pMesh);
	RELEASE(bonemesh->pSkinInfo);
	RELEASE(bonemesh->OrgMesh);
	DELETE(bonemesh);
	return S_OK;
}

// ---------------------skinmesh -------------------------
SkinMesh :: SkinMesh(LPCSTR filename) {

	if(gAnimationEffect == NULL) {
		ID3DXBuffer *errorbuf = 0;
		if (FAILED(D3DXCreateEffectFromFile(gdevice, "BlendVertex.fx",
			0, 0, D3DXSHADER_DEBUG, 0, &gAnimationEffect, &errorbuf)))
		{
			MessageBox(0, (char*)errorbuf->GetBufferPointer(), 0, 0);
			exit(1);
			return;
		}
	}

	BoneHierarchy bonehierarchy ;
	if(FAILED(D3DXLoadMeshHierarchyFromX(filename, D3DXMESH_MANAGED, gdevice, &bonehierarchy, 0, 
		(D3DXFRAME**)&m_boneroot, &player))) 
		MCOUT("load hierarchy fail");
	assert(player!=0);

	SetupMatrixPtr(m_boneroot, m_boneroot);
	D3DXMATRIX I;
	D3DXMatrixIdentity(&I);
	UpdateMatrix(m_boneroot, &I);
}

void SkinMesh::UpdateMatrix(Bone *b, D3DXMATRIX *mat) {
	if (!b) return;
	D3DXMatrixMultiply(&b->combmat, &b->TransformationMatrix, mat);
	UpdateMatrix((Bone*)b->pFrameFirstChild, &b->combmat);
	UpdateMatrix((Bone*)b->pFrameSibling, mat);
}

SkinMesh::~SkinMesh() {
	BoneHierarchy bonehierarchy;
	bonehierarchy.DestroyFrame(m_boneroot);
	RELEASE(player);
}

void SkinMesh::SetupMatrixPtr(Bone *bone, Bone *root) {
	// create combmatPtr in bonemesh
	if(!bone) return;
	if(bone->pMeshContainer) {
		BoneMesh *bonemesh = (BoneMesh*)bone->pMeshContainer;
		if(bonemesh->pSkinInfo) {
			int bonenum = bonemesh->pSkinInfo->GetNumBones();
			bonemesh->CombMat = new D3DXMATRIX*[bonenum];
			for(int i=0; i<bonenum; ++i) {
				Bone *b = (Bone*)D3DXFrameFind(root, bonemesh->pSkinInfo->GetBoneName(i)); // m_boneroot
				if(b) bonemesh->CombMat[i] = &b->combmat;
				else bonemesh->CombMat[i] = 0;
			}
		}
	}
	SetupMatrixPtr((Bone*)bone->pFrameFirstChild, root);
	SetupMatrixPtr((Bone*)bone->pFrameSibling, root);
}

void SkinMesh::Move(float x, float y, float z) {
	D3DXMATRIX world;
	D3DXMatrixTranslation(&world, x, y, z);
	UpdateMatrix(m_boneroot, &world);
}

void SkinMesh::Move(D3DXMATRIX world) {
	UpdateMatrix(m_boneroot, &world);
}




void SkinMesh::RenderBone(Bone *bone)
{
	if(!bone) return;
	if(bone->pMeshContainer) 
	{
		BoneMesh *bonemesh = (BoneMesh*) bone->pMeshContainer;
		if(bonemesh->pSkinInfo)
		{
			int bonenum = bonemesh->pSkinInfo->GetNumBones();
			// cal finalmatrix 
			for(int i=0;i<bonenum; ++i) 
				D3DXMatrixMultiply(bonemesh->CurrentMat+i, bonemesh->BoneOffsetMat+i, bonemesh->CombMat[i]);

			D3DXMATRIX world;
			D3DXMatrixIdentity(&world);

			// make matrix palette 
			gAnimationEffect->SetMatrixArray("FinalTransforms", bonemesh->CurrentMat, bonenum);
		
			// use BlendVertex mesh
			// Skinlighting  technique
			for(int i=0; i<bonemesh->GroupNum; ++i) {
				int mtrl = bonemesh->AttributeTable[i].AttribId;
				gAnimationEffect->SetTexture("texDiffuse", bonemesh->Textures[mtrl]);
				gAnimationEffect->SetMatrix("WorldMat", &world);
				gAnimationEffect->SetTechnique("Skinlighting");
				gAnimationEffect->Begin(0, 0);
				gAnimationEffect->BeginPass(0);
				bonemesh->MeshData.pMesh->DrawSubset(mtrl);
				gAnimationEffect->EndPass();
				gAnimationEffect->End();
			}
		}
		// draw static mesh
		else if(!onlyskinmesh) {
			// static mesh position = bone's position
			// use orgmesh
			for(int i=0; i<bonemesh->Textures.size(); ++i) {
				gAnimationEffect->SetMatrix("WorldMat", &bone->combmat);
				gAnimationEffect->SetTexture("texDiffuse", bonemesh->Textures[i]);
				gAnimationEffect->SetTechnique("Lighting");

				gAnimationEffect->Begin(0, 0);
				gAnimationEffect->BeginPass(0);
				bonemesh->OrgMesh->DrawSubset(i);
				gAnimationEffect->EndPass();
				gAnimationEffect->End();
			}
			
		}
	}

	RenderBone((Bone*)bone->pFrameFirstChild);
	RenderBone((Bone*)bone->pFrameSibling);
}

// ------------ animation --------------- 

void SkinMesh::extractAnim(std::vector<std::string> &motionName) {
	int n = player->GetMaxNumAnimationSets();
	for (int i = 0; i<n; ++i) {
		ID3DXAnimationSet *tmp = NULL;
		player->GetAnimationSet(i, &tmp);
		if (tmp) {
			motionName.push_back(tmp->GetName());
			tmp->Release();
		}
	}
}

int SkinMesh::GetAnimId(const std::string &name) {
	int n = player->GetMaxNumAnimationSets();
	for (int i = 0; i<n; ++i) {
		ID3DXAnimationSet *anim = NULL;
		player->GetAnimationSet(i, &anim);
		if (anim) {
			if (!strcmp(anim->GetName(), name.c_str())) return i;
			anim->Release();
		}
	}
	return -1;
}




void SkinMesh::InsMotion(const std::string &name) {
	int n = player->GetMaxNumAnimationSets();
	for (int i = 0; i<n; ++i) {
		ID3DXAnimationSet *anim = NULL;
		player->GetAnimationSet(i, &anim);
		if (anim) {
			if (!strcmp(anim->GetName(), name.c_str()))
				player->SetTrackAnimationSet(0, anim);
			anim->Release();
		}
	}
}


void SkinMesh::EnableTrack(int track, bool v)
{
	player->SetTrackEnable(track, v);
}

void SkinMesh::SetTrackWeight(int track, float w)
{
	player->SetTrackWeight(track, w);
}

void SkinMesh::SetTrackSpeed(int track, float speed)
{
	player->SetTrackSpeed(track, speed);
}

void SkinMesh::Reset()
{
	player->ResetTime();
}


ID3DXAnimationController* SkinMesh::ClonePlayer() {
	ID3DXAnimationController* newAnimController = NULL;
	if (player != NULL) {
		player->CloneAnimationController(player->GetMaxNumAnimationOutputs(),
			player->GetMaxNumAnimationSets(),
			player->GetMaxNumTracks(),
			player->GetMaxNumEvents(),
			&newAnimController);
	}
	return newAnimController;
}

void SkinMesh:: Setpose(D3DXMATRIX *mat, float tick) {

	UpdateMatrix(m_boneroot, mat);
	player->AdvanceTime(tick, 0);
}

void SkinMesh::Display(float dt) {
	player->AdvanceTime(dt, 0);
}
