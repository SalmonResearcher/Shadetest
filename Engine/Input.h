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

	//XV
	void Update();

	//‰Ÿ‚³‚ê‚Ä‚¢‚é‚©
	bool IsKey(int keyCode);

	//‰Ÿ‚³‚ê‚½uŠÔ‚©
	bool IsKeyDown(int keyCode);

	//—£‚³‚ê‚½‚©
	bool IsKeyUp(int keyCode);

	XMVECTOR GetMousePosition();

	XMFLOAT3 MoveMouseRange();

	void Release();
};