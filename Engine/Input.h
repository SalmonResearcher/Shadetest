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

	//������Ă��邩
	bool IsKey(int keyCode);

	//�����ꂽ�u�Ԃ�
	bool IsKeyDown(int keyCode);

	//�����ꂽ��
	bool IsKeyUp(int keyCode);

	XMVECTOR GetMousePosition();

	XMFLOAT3 MoveMouseRange();

	void Release();
};