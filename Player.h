#pragma once
#include "Engine/GameObject.h"


class Player :
    public GameObject
{
private:
    int hModel_;
    Transform TransPlayer;

    short moveSpeed;
    short dash;
    
public:
    Player(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};

