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
	pData->pFbx_ = nullptr;

	//���f���̃��X�g��0���猩��
	for (auto& itr : modelList)
	{
		//���ɊJ�����t�@�C���̏ꍇ
		if (itr->filename_ == fileName) {
			pData->pFbx_ = itr->pFbx_;
			break;
		}
	}

	//�V���Ƀt�@�C�����J��
	if (pData->pFbx_ == nullptr)
	{
		pData->pFbx_ = new Fbx;
		pData->pFbx_->Load(fileName);
	}

	modelList.push_back(pData);
	return( modelList.size() - 1 );
}

//���݂̃A�j���[�V�����̃t���[�����擾
int Model::GetAnimFrame(int hModel)
{
	return (int)modelList[hModel]->nowFrame;
}

XMFLOAT3 Model::GetBonePosition(int hModel, std::string boneName)
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
	modelList[hModel]->pFbx_->Draw(modelList[hModel]->transform_);

	//�A�j���[�V������i�߂�
	modelList[hModel]->nowFrame += modelList[hModel]->animSpeed;

	//�Ō�܂ŃA�j���[�V����������߂�
	if (modelList[hModel]->nowFrame > (float)modelList[hModel]->endFrame)
		modelList[hModel]->nowFrame = (float)modelList[hModel]->startFrame;



	//if (modelList[hModel]->pFbx_)
	//{
	//	modelList[hModel]->pFbx_->Draw(modelList[hModel]->transform_, (int)modelList[hModel]->nowFrame);
	//}
}

void Model::Release()
{
	bool isReffered = false; //�Q�Ƃ���Ă�H
	for (int i=0; i < modelList.size(); i++)
	{
		for (int j = i + 1; j < modelList.size(); j++)
		{
			if (modelList[i]->pFbx_ == modelList[j]->pFbx_)
			{
				isReffered = true;
				break;
			}
		}
		if (isReffered == false)
		{
			SAFE_DELETE(modelList[i]->pFbx_);
		}
		SAFE_DELETE(modelList[i]);
	}
	modelList.clear();
}
