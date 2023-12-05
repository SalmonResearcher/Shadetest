#pragma once

#include <dInput.h>
#include <DirectXMath.h>
#include "Direct3D.h"

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

namespace Input
{
	void Initialize(HWND hWnd);

	//�X�V
	void Update();

	//�L�[�{�[�h�̃L�[��������Ă��邩
	bool IsKey(int keyCode);

	//�����ꂽ�u�Ԃ�
	bool IsKeyDown(int keyCode);

	//�����ꂽ��
	bool IsKeyUp(int keyCode);

	//�}�E�X�̃{�^����������Ă��邩
	bool IsMouseButton(int buttonCode);

	//�}�E�X�̃{�^���������ꂽ��
	bool IsMouseButtonDown(int buttonCode);

	//�}�E�X�̃{�^���������ꂽ��
	bool IsMouseButtonUp(int buttonCode);

	//�}�E�X�̈ʒu���擾
	XMFLOAT3 GetMousePosition();

	//�}�E�X�J�[�\���̈ʒu���Z�b�g
	void SetMousePosition(int x, int y);

	//���̃t���[���̃}�E�X�̈ړ��ʂ��擾
	//X,Y�@�}�E�X�̈ړ��ʁ@Z,�z�C�[���̉�]��
	XMFLOAT3 GetMouseMove();

	void Release();
};