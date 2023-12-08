#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Sprite.h"
#include "Engine/Camera.h"

namespace {
    const XMFLOAT4 DEF_LIGHT_POS;
}

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_{-1}
{
    Block.position_.x = 0;
    Block.position_.z = 0;
}

void Stage::IntConstantBuffer()
{
    D3D11_BUFFER_DESC cb;
    cb.ByteWidth = sizeof(CBUFF_STAGESCENE);
    cb.Usage = D3D11_USAGE_DEFAULT;
    cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cb.MiscFlags = 0;
    cb.StructureByteStride = 0;

    // コンスタントバッファの作成
    HRESULT hr;
    hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pCBStageScene_);
    if (FAILED(hr))
    {
        MessageBox(NULL, "コンスタントバッファの作成に失敗しました", "エラー", MB_OK);
    }
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    int num = 0;
    hModel_[num] = Model::Load("assets/Ground.fbx");
    assert(hModel_[num] >= 0);

    num++;
    hModel_[num] = Model::Load("assets/Ball0.fbx");
    assert(hModel_[num] >= 0);

    num++;
    hModel_[num] = Model::Load("assets/Arrow.fbx");
    assert(hModel_[num] >= 0);

    num++;
    hModel_[num] = Model::Load("assets/Arrow.fbx");
    assert(hModel_[num] >= 0);

    num++;
    hModel_[num] = Model::Load("assets/Arrow.fbx");
    assert(hModel_[num] >= 0);

    pSprite = new Sprite;
    pSprite->Initialize();  
    IntConstantBuffer();

}
float speed = 1;
//更新

void Stage::Update()
{
    
    time++;
    
    float rotate = sin((DOUBLE)time /20);
    rotate = rotate / 5;
    Block.rotate_.y += speed;
    if (Input::IsKey(DIK_LEFT))
        speed = speed +0.2;

    Block.position_.y = rotate+1.2;

   // XMFLOAT4 p = {0.0f,2.0f,-1.5f,0};
   // XMFLOAT4 margin{ p.x - 0.0f,p.y - 0.0f,p.z - 0.1f,p. };
    if (Input::IsKey(DIK_W))
    {
        XMFLOAT4 p = {0.0f,2.0f,-1.5f,0};
        XMFLOAT4 margin{ p.x - 0.0f,p.y - 0.0f,p.z + 0.1f,p.w -0.0};

        SetLightPosition(margin);
    }

    if (Input::IsKey(DIK_A))
    {
        XMFLOAT4 p = { 0.0f,2.0f,-1.5f,0 };
        XMFLOAT4 margin{ p.x - 0.1f,p.y - 0.0f,p.z - 0.0f,p.w - 0.0 };

        SetLightPosition(margin);
    }

    if (Input::IsKey(DIK_S))
    {
        XMFLOAT4 p = { 0.0f,2.0f,-1.5f,0 };
        XMFLOAT4 margin{ p.x - 0.0f,p.y - 0.0f,p.z - 0.1f,p.w - 0.0 };

        SetLightPosition(margin);
    }

    if (Input::IsKey(DIK_D))
    {
        XMFLOAT4 p = { 0.0f,2.0f,-1.5f,0 };
        XMFLOAT4 margin{ p.x + 0.1f,p.y - 0.0f,p.z - 0.0f,p.w - 0.0 };

        SetLightPosition(margin);
    }
    XMFLOAT4 tmp{ GetLightPos() };
    Light.position_ = { tmp.x,tmp.y,tmp.z };


    CBUFF_STAGESCENE cb;
    cb.lightPosition = lightSourcePosition;
    XMStoreFloat4(&cb.eyePos, Camera::GetEyePosition());

    Direct3D::pContext_->UpdateSubresource(pCBStageScene_, 0, NULL, &cb, 0, 0);
    Direct3D::pContext_->VSSetConstantBuffers(1, 1, &pCBStageScene_);
    Direct3D::pContext_->PSSetConstantBuffers(1, 1, &pCBStageScene_);
}

//描画
void Stage::Draw()
{
    int i = 0;
    Transform Ground_;
    Ground_.scale_ = { 20,20,20 };
    Model::SetTransform(hModel_[i], Ground_);
    Model::Draw(hModel_[i]);

    i++;

    Transform Ball_;
    Ball_.position_ = {4,Block.position_.y,0 };
    Ball_.rotate_ = Block.rotate_;
    Model::SetTransform(hModel_[i], Ball_);
    Model::Draw(hModel_[i]);

    i++;

    Transform ArrowX_;
    ArrowX_.position_ = { 0,0.5,0 };
    ArrowX_.rotate_ = {0,0,0};
    ArrowX_.scale_ = { 0.25,0.25,0.25 };
    Model::SetTransform(hModel_[i], ArrowX_);
    Model::Draw(hModel_[i]);

    i++;

    Transform ArrowY_;
    ArrowY_.position_ = { 0,0.5,0 };
    ArrowY_.rotate_ = { 0,0,90 };
    ArrowY_.scale_ = { 0.25,0.25,0.25 };
    Model::SetTransform(hModel_[i], ArrowY_);
    Model::Draw(hModel_[i]);

    i++;

    Transform ArrowZ_;
    ArrowZ_.position_ = { 0,0.5,0 };
    ArrowZ_.rotate_ = { 0,-90,0 };
    ArrowZ_.scale_ = { 0.25,0.25,0.25 };
    Model::SetTransform(hModel_[i], ArrowZ_);
    Model::Draw(hModel_[i]);




    //Transform Sprite_;
    //Sprite_.position_ = XMFLOAT3{ 0,0,0 };
    //Sprite_.scale_ = XMFLOAT3{ 0.1,0.1,0.1 };
    //pSprite->Draw(Sprite_);
}

//開放
void Stage::Release()
{
}