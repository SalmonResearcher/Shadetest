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

	
}

//�X�V
void Controller::Update()
{
	XMVECTOR nowVec = XMLoadFloat3(&transform_.position_);
	XMVECTOR move = { 0,0,speed, 0 };
	XMMATRIX rotMat = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));


	if (Input::IsKey(DIK_Q))
	{
		transform_.rotate_.y += 1;
	}

	if (Input::IsKey(DIK_E))
	{
		transform_.rotate_.y -= 1;

	}
	if (Input::IsKey(DIK_A)) 
	{
		XMVECTOR a = XMVectorSet(0, 1, 0, 0);
		nowVec += XMVector3Cross(move, a);

	}
	if (Input::IsKey(DIK_D))
	{
		XMVECTOR a = XMVectorSet(0, 1, 0, 0);
		nowVec -= XMVector3Cross(move,a);
	}
	if (Input::IsKey(DIK_W))
	{
		nowVec += move;
		XMStoreFloat3(&transform_.position_, nowVec);
	}
	if (Input::IsKey(DIK_S))
	{
		nowVec -= move;
		XMStoreFloat3(&transform_.position_, nowVec);
	}

	XMStoreFloat3(&transform_.position_, nowVec);

	XMVECTOR vCam = { 0,5,-15,0 };
	Camera::SetTarget(transform_.position_);
	vCam = XMVector3TransformCoord(vCam, rotMat);
	XMStoreFloat3(&Cam.position_, nowVec + vCam);
	Camera::SetPosition(Cam.position_);

}

//�`��
void Controller::Draw()
{

}

//�J��
void Controller::Release()
{
}