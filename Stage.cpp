#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Sprite.h"

#include "Player.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_{-1}
{
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    Instantiate<Player>(this);
}

//�X�V
void Stage::Update()
{
}

//�`��
void Stage::Draw()
{
}

//�J��
void Stage::Release()
{
}