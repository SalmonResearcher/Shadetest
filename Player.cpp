#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Controller.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"),hModel_(-1)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("assets/Player.fbx");
	assert(hModel_ >= 0);

	Instantiate<Controller>(this);
}

void Player::Update()
{
	if (Input::IsKey(DIK_W))
	{
		TransPlayer.position_.z += 0.1f * dash;
	}

}

void Player::Draw()
{
	Model::SetTransform(hModel_,TransPlayer);
	Model::Draw(hModel_);
}

void Player::Release()
{
}
