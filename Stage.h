#pragma once
#include "Engine/GameObject.h"

struct CBUFF_STAGESCENE
{
    XMFLOAT4    lightPosition;
    XMFLOAT4    eyePos;
};

class Sprite;

//◆◆◆を管理するクラス
class Stage : public GameObject
{
    int hModel_[5];    //モデル番号
    Transform Block;
    Transform Light;
    int time;
    Sprite* pSprite = nullptr;
    ID3D11Buffer* pCBStageScene_;
    void IntConstantBuffer();
    XMFLOAT4 lightSourcePosition;

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

    void SetLightPosition(XMFLOAT4& _pos) { lightSourcePosition = _pos; }
    XMFLOAT4 GetLightPos() { return lightSourcePosition; }
};