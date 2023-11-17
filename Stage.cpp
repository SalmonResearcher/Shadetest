#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Sprite.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_(-1)
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
    //モデルデータのロード
    hModel_ = Model::Load("assets/BoxDefault.fbx");
    assert(hModel_ >= 0);

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

    Block.position_.y = rotate;
    
}

//描画
void Stage::Draw()
{
    Model::SetTransform(hModel_, Block);
    Model::Draw(hModel_);

    pSprite->Draw(transform_);
}

//開放
void Stage::Release()
{
}