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

	//キーボードのキーが押されているか
	bool IsKey(int keyCode);

	//押された瞬間か
	bool IsKeyDown(int keyCode);

	//離されたか
	bool IsKeyUp(int keyCode);

	//マウスのボタンが押されているか
	bool IsMouseButton(int buttonCode);

	//マウスのボタンが押されたか
	bool IsMouseButtonDown(int buttonCode);

	//マウスのボタンが離されたか
	bool IsMouseButtonUp(int buttonCode);

	//マウスの位置を取得
	XMFLOAT3 GetMousePosition();

	//マウスカーソルの位置をセット
	void SetMousePosition(int x, int y);

	//そのフレームのマウスの移動量を取得
	//X,Y　マウスの移動量　Z,ホイールの回転量
	XMFLOAT3 GetMouseMove();

	void Release();
};