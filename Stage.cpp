#include "Stage.h"
#include "Engine/Model.h"

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
}

//�X�V
void Stage::Update()
{
    Block.rotate_.y += 1;
    Block.position_.y =
}

//�`��
void Stage::Draw()
{


	Model::SetTransform(hModel_, Block);
    Model::Draw(hModel_);

}

//�J��
void Stage::Release()
{
}