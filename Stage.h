#pragma once
#include "Engine/GameObject.h"

class Sprite;

//◆◆◆を管理するクラス
class Stage : public GameObject
{
    int hModel_[5];    //モデル番号
    Transform Block;
    int time;
    Sprite* pSprite = nullptr;

public:
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};