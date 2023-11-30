#include "Model.h"
#include "Direct3D.h"

namespace Model {

	//���[�h�������f���f�[�^�̈ꗗ
	std::vector<ModelData*> modelList;
}

int Model::Load(std::string fileName)
{
	ModelData* pData = new ModelData;
	pData->filename_ = fileName;
	pData->pfbx_ = nullptr;

	//���f���̃��X�g��0���猩��
	for (auto& itr : modelList)
	{
		//���ɊJ�����t�@�C���̏ꍇ
		if (itr->filename_ == fileName) {
			pData->pfbx_ = itr->pfbx_;
			break;
		}
	}

	//�V���Ƀt�@�C�����J��
	if (pData->pfbx_ == nullptr)
	{
		pData->pfbx_ = new Fbx;
		pData->pfbx_->Load(fileName);
	}

	modelList.push_back(pData);
	return( modelList.size() - 1 );
}

void Model::SetAnimFrame(int handle, int startFrame, int endFrame, float animSpeed)
{
	modelList[handle].SetAnimFrame()
}

int Model::GetAnimFrame(int handle)
{
	return 0;
}

XMFLOAT3 Model::GetBonePosition(int handle, std::string boneName)
{
	return XMFLOAT3();
}

void Model::SetTransform(int hModel, Transform transform)
{
	//���f���ԍ���modelList�̃C���f�b�N�X
	modelList[hModel]->transform_ = transform;
}
void Model::Draw(int hModel) {
	//���f���ԍ���modelList�̃C���f�b�N�X
	modelList[hModel]->pfbx_->Draw(modelList[hModel]->transform_);
}

void Model::Release()
{
	bool isReffered = false; //�Q�Ƃ���Ă�H
	for (int i=0; i < modelList.size(); i++)
	{
		for (int j = i + 1; j < modelList.size(); j++)
		{
			if (modelList[i]->pfbx_ == modelList[j]->pfbx_)
			{
				isReffered = true;
				break;
			}
		}
		if (isReffered == false)
		{
			SAFE_DELETE(modelList[i]->pfbx_);
		}
		SAFE_DELETE(modelList[i]);
	}
	modelList.clear();
}
