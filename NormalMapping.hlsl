//������������������������������������������������������������������������������
 // �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
//������������������������������������������������������������������������������
Texture2D		g_texture : register(t0);	//�e�N�X�`���[
SamplerState	g_sampler : register(s0);	//�T���v���[
Texture2D		normalTex : register(r1);	//�m�[�}���}�b�v

//������������������������������������������������������������������������������
// �R���X�^���g�o�b�t�@
// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
//������������������������������������������������������������������������������
cbuffer global
{
	float4x4	matWVP;			// ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4	matW;			// ���[���h�s��
	float4x4	matNormal;      // �m�[�}���̃��[�J���ւ̕ϊ��s�񂩂畽�s�ړ��������擾�������
	float4		diffuseColor;	//�}�e���A���̐F
	float4		ambientColor;	//����
	float4		specularColor;	//���ʔ��ˁ@�n�C���C�g�̌W��
	float		shininess;		//�n�C���C�g�̍L����̑傫��
	int			isTextured;		//�e�N�X�`���[���\���Ă��邩�ǂ���
	int			isNormalMap;	//�m�[�}���}�b�v�����邩�ǂ���
};

cbuffer gmodel:register(b1)
{
	float4		lightPosition;		//�����̈ʒu
	float4		eyePosition;		//�J�����̈ʒu
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUT
{
	float4 pos		: SV_POSITION;		//�s�N�Z���ʒu
	float2 uv		: TEXCODE;			//UV���W
	float4 eyev		: POSITION;			//�����x�N�g��	eye vector
	float4 Neyev	: POSITION1;		//�m�[�}���}�b�v�p�̐ڋ�Ԃɂւ񂩂񂵂��x�N�g��
	float4 normal	: NORMAL;			//�@���x�N�g��
	float4 light	: POSITION2;		//���C�g��ڋ�Ԃɕϊ������x�N�g��
	float4 color	: COLOR;	//�����o�[�g���f���̊g�U���˂̐F
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//�s�N�Z���V�F�[�_�[�֓n�����
	VS_OUT outData = (VS_OUT)0;

	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
	outData.pos = mul(pos, matWVP);
	outData.uv = (float2)uv;

	float3 binormal = cross(normal, tangent);
	binormal = mul(binormal, matNormal);
	binormal = normalize(binormal);				//�]�@���x�N�g�������[�J�����W�ɕϊ�����

	outData.normal = normalize(mul(normal.matNormal));
	outData.normal.w = 0;

	tangent = mul(tangent, matNormal);
	tangent = normalize(tangent);
	tangent.w = 0;

	float4 eye = normal(mul(pos, matW) - eyePosition);
	outData.eyev = eye;

	outData.Neyev.x = dot(eye, tangent);	//�ڋ�Ԃ̎����x�N�g��
	outData.Neyev.y = dot(eye, binormal);	
	outData.Neyev.z = dot(eye, outData.normal);
	outData.Neyev.w = 0;

	//�܂Ƃ߂ďo��
	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
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