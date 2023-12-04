#pragma once
#include <fbxsdk.h>
#include<d3d11.h>
#include <DirectXMath.h>
#include "Texture.h"
#include "Transform.h"

using namespace DirectX;

class Fbx;
struct RayCastData;

//Fbxのアニメーションを扱うクラス
class FbxParts
{
private:
	// ボーン構造体（関節情報）
	struct  Bone
	{
		XMMATRIX  bindPose;      // 初期ポーズ時のボーン変換行列
		XMMATRIX  newPose;       // アニメーションで変化したときのボーン変換行列
		XMMATRIX  diffPose;      // bindPose に対する nowPose の変化量
	};

	// ウェイト構造体（ボーンと頂点の関連付け）
	struct Weight
	{
		XMFLOAT3	posOrigin;		// 元々の頂点座標
		XMFLOAT3	normalOrigin;	// 元々の法線ベクトル
		int* pBoneIndex;		// 関連するボーンのID
		float* pBoneWeight;	// ボーンの重み
	};

	// ボーン制御情報
	FbxSkin* pSkinInfo_;		// スキンメッシュ情報（スキンメッシュアニメーションのデータ本体）
	FbxCluster** ppCluster_;		// クラスタ情報（関節ごとに関連付けられた頂点情報）
	int				numBone_;		// FBXに含まれている関節の数
	Bone* pBoneArray_;	// 各関節の情報
	Weight* pWeightArray_;	// ウェイト情報（頂点の対する各関節の影響度合い）

	void InitSkelton(FbxMesh* pMesh);			//骨の情報を準備

public:
	FbxParts();
	~FbxParts();

	//描画
	//引数：world	ワールド行列
	void Draw(Transform& transform);

	//ボーン有りのモデルを描画
//引数：transform	行列情報
//引数：time		フレーム情報（１アニメーション内の今どこか）
	void DrawSkinAnime(Transform& transform, FbxTime time);

	//ボーン無しのモデルを描画
	//引数：transform	行列情報
	//引数：time		フレーム情報（１アニメーション内の今どこか）
	//引数：scene		Fbxファイルから読み込んだシーン情報
	void DrawMeshAnime(Transform& transform, FbxTime time, FbxScene* scene);

	//任意のボーンの位置を取得
	//引数：boneName	取得したいボーンの位置
	//引数：position	ワールド座標での位置【out】
	//戻値：見つかればtrue
	bool GetBonePosition(std::string boneName, XMFLOAT3* position);

	//スキンメッシュ情報を取得
	//戻値：スキンメッシュ情報
	FbxSkin* GetSkinInfo() { return pSkinInfo_; }

	//レイキャスト（レイを飛ばして当たり判定）
	//引数：data	必要なものをまとめたデータ
	void RayCast(RayCastData* data);

};

