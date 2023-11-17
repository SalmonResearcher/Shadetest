#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Sprite.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_(-1)
{
    Block.position_.x = 0;
    Block.position_.z = 0;
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("assets/BoxDefault.fbx");
    assert(hModel_ >= 0);

    pSprite = new Sprite;
    pSprite->Initialize();    
}
float speed = 1;
//�X�V

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

//�`��
void Stage::Draw()
{
    Model::SetTransform(hModel_, Block);
    Model::Draw(hModel_);

    pSprite->Draw(transform_);
}

//�J��
void Stage::Release()
{
}