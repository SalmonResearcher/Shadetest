#pragma once
//�K�v�ȃC���N���[�h������
#include <string>
#include <vector>
#include "fbx.h"

namespace Model
{
	struct ModelData
	{
		//�t�@�C����
		std::string filename_;

		//���[�h�������f���̃A�h���X
		Fbx* pfbx_;

		//�ړ��s��
		Transform transform_;

		//�A�j���[�V�����̃��[�g
	};

	/// <summary>
	/// ���f���ǂݍ���
	/// </summary>
	/// <param name="fileName">�t�@�C����</param>
	/// <returns>���f���f�[�^�Ɋ��蓖�Ă�ꂽ�ԍ�</returns>
	int Load(std::string fileName);

	/// <summary>
	/// �A�j���[�V�����̃t���[�������Z�b�g
	/// </summary>
	/// <param name="handle">�ݒ肵�������f���ԍ�</param>
	/// <param name="startFrame">�J�n�t���[��</param>
	/// <param name="endFrame">�I���t���[��</param>
	/// <param name="animSpeed">�A�j���[�V�������x</param>
	void SetAnimFrame(int handle, int startFrame, int endFrame, float animSpeed);

	/// <summary>
	/// ���݂̃A�j���[�V�����̃t���[�����擾
	/// </summary>
	/// <param name="handle">�A�j���[�V�����̃t���[�����擾���������f���ԍ�</param>
	/// <returns>�A�j���[�V�����̌��݂̃t���[��</returns>
	int GetAnimFrame(int handle);

	/// <summary>
	/// �C�ӂ̃{�[���̈ʒu���擾
	/// </summary>
	/// <param name="handle">���ׂ������f���ԍ�</param>
	/// <param name="boneName">�{�[���̈ʒu</param>
	/// <returns>�{�[���̈ʒu�i���[���h���W�j</returns>
	XMFLOAT3 GetBonePosition(int handle, std::string boneName);

	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);
	void Release();
}

