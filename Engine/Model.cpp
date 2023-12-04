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
	pData->pFbx_ = nullptr;

	//モデルのリストを0から見て
	for (auto& itr : modelList)
	{
		//既に開いたファイルの場合
		if (itr->filename_ == fileName) {
			pData->pFbx_ = itr->pFbx_;
			break;
		}
	}

	//新たにファイルを開く
	if (pData->pFbx_ == nullptr)
	{
		pData->pFbx_ = new Fbx;
		pData->pFbx_->Load(fileName);
	}

	modelList.push_back(pData);
	return( modelList.size() - 1 );
}

//現在のアニメーションのフレームを取得
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
	//モデル番号はmodelListのインデックス
	modelList[hModel]->transform_ = transform;
}

void Model::Draw(int hModel) {
	//モデル番号はmodelListのインデックス
	modelList[hModel]->pFbx_->Draw(modelList[hModel]->transform_);

	//アニメーションを進める
	modelList[hModel]->nowFrame += modelList[hModel]->animSpeed;

	//最後までアニメーションしたら戻す
	if (modelList[hModel]->nowFrame > (float)modelList[hModel]->endFrame)
		modelList[hModel]->nowFrame = (float)modelList[hModel]->startFrame;



	//if (modelList[hModel]->pFbx_)
	//{
	//	modelList[hModel]->pFbx_->Draw(modelList[hModel]->transform_, (int)modelList[hModel]->nowFrame);
	//}
}

void Model::Release()
{
	bool isReffered = false; //参照されてる？
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
