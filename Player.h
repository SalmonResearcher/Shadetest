#pragma once
#include "Engine/GameObject.h"


class Player :
    public GameObject
{
 private:
    Transform TransPlayer;
    Transform Cam;
    Transform Tar;

    XMFLOAT3 Camposition_ = { 0,5,-10 };

    int hModel_;
    const float speed = 0.125;
    short moveSpeed;
    short dash;
    
public:
    Player(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    XMFLOAT3 GetPlayerPos()
    {
        return transform_.position_;
    }
};

