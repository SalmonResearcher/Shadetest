#pragma once
//必要なインクルードを書く
#include <string>
#include <vector>
#include "fbx.h"

namespace Model
{
	struct ModelData
	{
		//ファイル名
		std::string filename_;

		//ロードしたモデルのアドレス
		Fbx* pfbx_;

		//移動行列
		Transform transform_;

		//アニメーションのレート
	};

	/// <summary>
	/// モデル読み込み
	/// </summary>
	/// <param name="fileName">ファイル名</param>
	/// <returns>モデルデータに割り当てられた番号</returns>
	int Load(std::string fileName);

	/// <summary>
	/// アニメーションのフレーム数をセット
	/// </summary>
	/// <param name="handle">設定したいモデル番号</param>
	/// <param name="startFrame">開始フレーム</param>
	/// <param name="endFrame">終了フレーム</param>
	/// <param name="animSpeed">アニメーション速度</param>
	void SetAnimFrame(int handle, int startFrame, int endFrame, float animSpeed);

	/// <summary>
	/// 現在のアニメーションのフレームを取得
	/// </summary>
	/// <param name="handle">アニメーションのフレームを取得したいモデル番号</param>
	/// <returns>アニメーションの現在のフレーム</returns>
	int GetAnimFrame(int handle);

	/// <summary>
	/// 任意のボーンの位置を取得
	/// </summary>
	/// <param name="handle">調べたいモデル番号</param>
	/// <param name="boneName">ボーンの位置</param>
	/// <returns>ボーンの位置（ワールド座標）</returns>
	XMFLOAT3 GetBonePosition(int handle, std::string boneName);

	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);
	void Release();
}

