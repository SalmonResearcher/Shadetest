#pragma once
#include <fbxsdk.h>
#include<d3d11.h>
#include <DirectXMath.h>
#include "Texture.h"
#include "Transform.h"

using namespace DirectX;

class Fbx;
struct RayCastData;

//Fbx�̃A�j���[�V�����������N���X
class FbxParts
{
private:
	// �{�[���\���́i�֐ߏ��j
	struct  Bone
	{
		XMMATRIX  bindPose;      // �����|�[�Y���̃{�[���ϊ��s��
		XMMATRIX  newPose;       // �A�j���[�V�����ŕω������Ƃ��̃{�[���ϊ��s��
		XMMATRIX  diffPose;      // bindPose �ɑ΂��� nowPose �̕ω���
	};

	// �E�F�C�g�\���́i�{�[���ƒ��_�̊֘A�t���j
	struct Weight
	{
		XMFLOAT3	posOrigin;		// ���X�̒��_���W
		XMFLOAT3	normalOrigin;	// ���X�̖@���x�N�g��
		int* pBoneIndex;		// �֘A����{�[����ID
		float* pBoneWeight;	// �{�[���̏d��
	};

	// �{�[��������
	FbxSkin* pSkinInfo_;		// �X�L�����b�V�����i�X�L�����b�V���A�j���[�V�����̃f�[�^�{�́j
	FbxCluster** ppCluster_;		// �N���X�^���i�֐߂��ƂɊ֘A�t����ꂽ���_���j
	int				numBone_;		// FBX�Ɋ܂܂�Ă���֐߂̐�
	Bone* pBoneArray_;	// �e�֐߂̏��
	Weight* pWeightArray_;	// �E�F�C�g���i���_�̑΂���e�֐߂̉e���x�����j

	void InitSkelton(FbxMesh* pMesh);			//���̏�������

public:
	FbxParts();
	~FbxParts();

	//�`��
	//�����Fworld	���[���h�s��
	void Draw(Transform& transform);

	//�{�[���L��̃��f����`��
//�����Ftransform	�s����
//�����Ftime		�t���[�����i�P�A�j���[�V�������̍��ǂ����j
	void DrawSkinAnime(Transform& transform, FbxTime time);

	//�{�[�������̃��f����`��
	//�����Ftransform	�s����
	//�����Ftime		�t���[�����i�P�A�j���[�V�������̍��ǂ����j
	//�����Fscene		Fbx�t�@�C������ǂݍ��񂾃V�[�����
	void DrawMeshAnime(Transform& transform, FbxTime time, FbxScene* scene);

	//�C�ӂ̃{�[���̈ʒu���擾
	//�����FboneName	�擾�������{�[���̈ʒu
	//�����Fposition	���[���h���W�ł̈ʒu�yout�z
	//�ߒl�F�������true
	bool GetBonePosition(std::string boneName, XMFLOAT3* position);

	//�X�L�����b�V�������擾
	//�ߒl�F�X�L�����b�V�����
	FbxSkin* GetSkinInfo() { return pSkinInfo_; }

	//���C�L���X�g�i���C���΂��ē����蔻��j
	//�����Fdata	�K�v�Ȃ��̂��܂Ƃ߂��f�[�^
	void RayCast(RayCastData* data);

};

