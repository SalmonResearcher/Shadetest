#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Sprite.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_{-1}
{
    Block.position_.x = 0;
    Block.position_.z = 0;
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    int num = 0;
    hModel_[num] = Model::Load("assets/Ground.fbx");
    assert(hModel_[num] >= 0);

    num++;

    //モデルデータのロード
    hModel_[num] = Model::Load("assets/Ball.fbx");
    assert(hModel_[num] >= 0);

    num++;

    hModel_[num] = Model::Load("assets/Arrow.fbx");
    assert(hModel_[num] >= 0);

    num++;

    //モデルデータのロード
    hModel_[num] = Model::Load("assets/Arrow.fbx");
    assert(hModel_[num] >= 0);

    num++;

    hModel_[num] = Model::Load("assets/Arrow.fbx");
    assert(hModel_[num] >= 0);




    pSprite = new Sprite;
    pSprite->Initialize();    
}
float speed = 1;
//更新

void Stage::Update()
{
    
    time++;
    
    float rotate = sin((DOUBLE)time /20);
    rotate = rotate / 5;
    Block.rotate_.y += speed;
    if (Input::IsKey(DIK_LEFT))
        speed = speed +0.2;

    Block.position_.y = rotate+1.2;
    
}

//描画
void Stage::Draw()
{
    int i = 0;
    Transform Ground_;
    Ground_.scale_ = { 20,20,20 };
    Model::SetTransform(hModel_[i], Ground_);
    Model::Draw(hModel_[i]);

    i++;

    Transform Ball_;
    Ball_.position_ = {4,Block.position_.y,0 };
    Ball_.rotate_ = Block.rotate_;
    Model::SetTransform(hModel_[i], Ball_);
    Model::Draw(hModel_[i]);

    i++;

    Transform ArrowX_;
    ArrowX_.position_ = { 0,0.5,0 };
    ArrowX_.rotate_ = {0,0,0};
    ArrowX_.scale_ = { 0.25,0.25,0.25 };
    Model::SetTransform(hModel_[i], ArrowX_);
    Model::Draw(hModel_[i]);

    i++;

    Transform ArrowY_;
    ArrowY_.position_ = { 0,0.5,0 };
    ArrowY_.rotate_ = { 0,0,90 };
    ArrowY_.scale_ = { 0.25,0.25,0.25 };
    Model::SetTransform(hModel_[i], ArrowY_);
    Model::Draw(hModel_[i]);

    i++;

    Transform ArrowZ_;
    ArrowZ_.position_ = { 0,0.5,0 };
    ArrowZ_.rotate_ = { 0,-90,0 };
    ArrowZ_.scale_ = { 0.25,0.25,0.25 };
    Model::SetTransform(hModel_[i], ArrowZ_);
    Model::Draw(hModel_[i]);




    //Transform Sprite_;
    //Sprite_.position_ = XMFLOAT3{ 0,0,0 };
    //Sprite_.scale_ = XMFLOAT3{ 0.1,0.1,0.1 };
    //pSprite->Draw(Sprite_);
}

//開放
void Stage::Release()
{
}