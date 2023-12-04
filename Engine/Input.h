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

	//更新
	void Update();

	//押されているか
	bool IsKey(int keyCode);

	//押された瞬間か
	bool IsKeyDown(int keyCode);

	//離されたか
	bool IsKeyUp(int keyCode);

	XMVECTOR GetMousePosition();

	XMFLOAT3 MoveMouseRange();

	void Release();
};