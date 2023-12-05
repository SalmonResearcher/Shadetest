#include "Controller.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Player.h"

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

}



//�X�V
void Controller::Update()
{
	static XMFLOAT3 move = {0,0,0}; 
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
	Debug::Log("pos.x = "); Debug::Log(transform_.position_.x, true);
	Debug::Log("pos.y = "); Debug::Log(transform_.position_.y, true);
	Debug::Log("pos.z = "); Debug::Log(transform_.position_.z, true);


	/*//���������]�����܂�
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
	}*/

	//��]�s��
	XMMATRIX rotMatY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

	//rotateMatrix
	XMMATRIX rotMatX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

	//�ړ��x�N�g��
	XMVECTOR nowVec = XMLoadFloat3(&transform_.position_);
	//XMVECTOR frontMove = XMVectorSet(0, 0, speed, 0);
	//frontMove = XMVector3TransformCoord(frontMove, rotMatY);

	////�㉺���E��]
	//XMVECTOR udMove = XMVectorSet(0, speed, 0, 0);
	//udMove = XMVector3TransformCoord(udMove, rotMatY);
	//XMVECTOR RLMove = XMVectorSet(speed, 0, 0, 0);
	//RLMove = XMVector3TransformCoord(RLMove, rotMatY);



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