#include "Model.h"
#include "Direct3D.h"

namespace Model {

	//ロードしたモデルデータの一覧
	std::vector<ModelData*> modelList;
}

int Model::Load(std::string fileName)
{
	ModelData* pData = new ModelData;
	pData->filename_ = fileName;
	pData->pfbx_ = nullptr;

	//モデルのリストを0から見て
	for (auto& itr : modelList)
	{
		//既に開いたファイルの場合
		if (itr->filename_ == fileName) {
			pData->pfbx_ = itr->pfbx_;
			break;
		}
	}

	//新たにファイルを開く
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
	//モデル番号はmodelListのインデックス
	modelList[hModel]->transform_ = transform;
}
void Model::Draw(int hModel) {
	//モデル番号はmodelListのインデックス
	modelList[hModel]->pfbx_->Draw(modelList[hModel]->transform_);
}

void Model::Release()
{
	bool isReffered = false; //参照されてる？
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
