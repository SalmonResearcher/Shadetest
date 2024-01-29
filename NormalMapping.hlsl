//───────────────────────────────────────
 // テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D		g_texture : register(t0);	//テクスチャー
SamplerState	g_sampler : register(s0);	//サンプラー
Texture2D		normalTex : register(r1);	//ノーマルマップ

//───────────────────────────────────────
// コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer global
{
	float4x4	matWVP;			// ワールド・ビュー・プロジェクションの合成行列
	float4x4	matW;			// ワールド行列
	float4x4	matNormal;      // ノーマルのローカルへの変換行列から平行移動成分を取得したやつ
	float4		diffuseColor;	//マテリアルの色
	float4		ambientColor;	//環境光
	float4		specularColor;	//鏡面反射　ハイライトの係数
	float		shininess;		//ハイライトの広がりの大きさ
	int			isTextured;		//テクスチャーが貼られているかどうか
	int			isNormalMap;	//ノーマルマップがあるかどうか
};

cbuffer gmodel:register(b1)
{
	float4		lightPosition;		//光源の位置
	float4		eyePosition;		//カメラの位置
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos		: SV_POSITION;		//ピクセル位置
	float2 uv		: TEXCODE;			//UV座標
	float4 eyev		: POSITION;			//視線ベクトル	eye vector
	float4 Neyev	: POSITION1;		//ノーマルマップ用の接空間にへんかんしたベクトル
	float4 normal	: NORMAL;			//法線ベクトル
	float4 light	: POSITION2;		//ライトを接空間に変換したベクトル
	float4 color	: COLOR;	//ランバートモデルの拡散反射の色
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//ピクセルシェーダーへ渡す情報
	VS_OUT outData = (VS_OUT)0;

	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ
	outData.pos = mul(pos, matWVP);
	outData.uv = (float2)uv;

	float3 binormal = cross(normal, tangent);
	binormal = mul(binormal, matNormal);
	binormal = normalize(binormal);				//従法線ベクトルをローカル座標に変換した

	outData.normal = normalize(mul(normal.matNormal));
	outData.normal.w = 0;

	tangent = mul(tangent, matNormal);
	tangent = normalize(tangent);
	tangent.w = 0;

	float4 eye = normal(mul(pos, matW) - eyePosition);
	outData.eyev = eye;

	outData.Neyev.x = dot(eye, tangent);	//接空間の視線ベクトル
	outData.Neyev.y = dot(eye, binormal);	
	outData.Neyev.z = dot(eye, outData.normal);
	outData.Neyev.w = 0;

	//まとめて出力
	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	float4 lightSource = float4(1.0, 1.0, 1.0, 1.0);
	float4 diffuse;
	float4 ambient;
	float4 specular;

	if (isNormalmap)
	{
		float4 tmpNormal = normalTex.Sample(g_sampler, inData.uv) * 2.0f - 1.0f;

		tmpNormal = normalize(tmpNormal);
		tmpNormal.w = 0;

		float4 NL = clamp(dot(normalize(inData.light), tmpNormal), 0, 1);
		float4 reflection = reflect(normalize(inData.light), tmpNormal);
		float4 specular = pow(saturate(dot(reflection, normalize(inData.Neyev))), shininess) * specular;

		if (isTextured != 0)
		{
			diffuse = lightSource * g_texture.Sample(g_sampler, inData.uv) * NL;
			ambient = lightSource * g_texture.Sample(g_sampler, inData.uv) * ambientColor;
		}
		else
		{
			diffuse = lightSource * diffuseColor * NL;
			ambient = lightSource * diffuseColor * ambientColor;
		}
		return  NL;
	}
	else
	{
		float4 reflection = reflect(normalize(lightPosition), inData.normal);
		float4 specular = pow(saturate(dot(reflection, inData.eyev)), shininess) * specularColor;
		if (hasTexture == 0)
		{
			diffuse = lightSource * diffuseColor * inData.color;
			ambient = lightSource * diffuseColor * ambientColor;
		}
		else
		{
			diffuse = lightSource * g_texture.Sample(g_sampler, inData.uv) * inData.color;
			ambient = lightSource * g_texture.Sample(g_sampler, inData.uv) * ambientColor;
		}
		return diffuse + ambient + specular;
	}
}