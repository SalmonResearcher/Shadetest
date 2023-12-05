#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"),hModel_(-1)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("assets/Player.fbx");
	assert(hModel_ >= 0);

}

void Player::Update()
{
	if (Input::IsKey(DIK_W))
	{
		TransPlayer.position_.z += 0.1f * dash;
	}
	static XMFLOAT3 move = { 0,0,0 };
	static XMFLOAT3 nmove = { 0,0,0 };

	move.x += Input::GetMouseMove().x;
	move.y += Input::GetMouseMove().y;
	move.z += Input::GetMouseMove().z;
	//Debug::Log(move.y);


	nmove.x = move.y;
	nmove.y = move.x;

	//�}�E�X�ʒu�Œ�
	SetCursorPos(600, 400);

	nmove.x *= 0.1;
	nmove.y *= 0.1;

	if (nmove.x >= 69)
	{
		nmove.x = 69;
		move.y = 689;
	}

	if (nmove.x <= -20)
	{
		nmove.x = -20;
		move.y = -200;
	}

	transform_.rotate_ = nmove;

	//��]�s��
	XMMATRIX rotMatY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

	//rotateMatrix
	XMMATRIX rotMatX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

	//�ړ��x�N�g��
	XMVECTOR nowVec = XMLoadFloat3(&transform_.position_);
	XMVECTOR frontMove = XMVectorSet(0, 0, speed, 0);
	frontMove = XMVector3TransformCoord(frontMove, rotMatY);

	//�㉺���E��]
	XMVECTOR udMove = XMVectorSet(0, speed, 0, 0);
	udMove = XMVector3TransformCoord(udMove, rotMatY);
	XMVECTOR RLMove = XMVectorSet(speed, 0, 0, 0);
	RLMove = XMVector3TransformCoord(RLMove, rotMatY);



	//�J�����ړ�
	XMStoreFloat3(&transform_.position_, nowVec);

	//�J�����{��
	XMVECTOR vCam = { 0,0,-10,0 };

	//�J���������_
	Camera::SetTarget(transform_.position_);
	vCam = XMVector3TransformCoord(vCam, rotMatX * rotMatY);

	//�J�������W�ύX
	XMStoreFloat3(&Camposition_, nowVec + vCam);

	Camera::SetPosition(Camposition_);

}

void Player::Draw()
{
	Model::SetTransform(hModel_,TransPlayer);
	Model::Draw(hModel_);
}

void Player::Release()
{
}
