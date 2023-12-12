#pragma once
#include "Engine/GameObject.h"

struct CBUFF_STAGESCENE
{
    XMFLOAT4    lightPosition;
    XMFLOAT4    eyePos;
};

class Sprite;

//���������Ǘ�����N���X
class Stage : public GameObject
{
    int hModel_[5];    //���f���ԍ�
    Transform Block;
    Transform Light;
    int time;
    Sprite* pSprite = nullptr;
    ID3D11Buffer* pCBStageScene_;
    void IntConstantBuffer();
    XMFLOAT4 lightSourcePosition;

public:
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void SetLightPosition(XMFLOAT4& _pos) { lightSourcePosition = _pos; }
    XMFLOAT4 GetLightPos() { return lightSourcePosition; }
};