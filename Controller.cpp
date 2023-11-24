#include "Controller.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"

//�R���X�g���N�^
Controller::Controller(GameObject* parent)
	:GameObject(parent, "Controller")
{
}

//�f�X�g���N�^
Controller::~Controller()
{
}

//������
void Controller::Initialize()
{
	transform_.rotate_.x = -10;
	transform_.position_.z = -5;
}

//�X�V
void Controller::Update()
{
	//���������]�����܂�
	if (Input::IsKey(DIK_Q))
	{
		transform_.rotate_.y += 1;
	}

	if (Input::IsKey(DIK_E))
	{
		transform_.rotate_.y -= 1;
	}

	if (Input::IsKey(DIK_C))
	{
		//���ς�����ĂȂ�
		transform_.rotate_.x += 1;
		if (transform_.rotate_.x >= 69)
		{
			transform_.rotate_.x = 69;
		}
	}

	if (Input::IsKey(DIK_F))
	{
		//���ς��Ƃ��ĂȂ�
		transform_.rotate_.x -= 1;
		if (transform_.rotate_.x <= -20)
		{
			transform_.rotate_.x = -20;
		}
	}

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

	//�E�Ɉړ�
	if (Input::IsKey(DIK_A))
	{
		nowVec -= RLMove;
	}

	//���Ɉړ�
	if (Input::IsKey(DIK_D))
	{
		nowVec += RLMove;
	}

	//�O�i
	if (Input::IsKey(DIK_W))
	{
		nowVec += frontMove;
	}

	//���
	if (Input::IsKey(DIK_S))
	{
		nowVec -= frontMove;
	}

	//�㏸
	if (Input::IsKey(DIK_LCONTROL))
	{
		nowVec -= udMove;
	}
	//���~
	if (Input::IsKey(DIK_SPACE))
	{
		nowVec += udMove;
	}

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

//�`��
void Controller::Draw()
{
}

//�J��
void Controller::Release()
{
}