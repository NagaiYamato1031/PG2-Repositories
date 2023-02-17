#pragma once

// �\����
#pragma region Structure

// 2 �����x�N�g����\��
struct Vector2
{
	float x;
	float y;
};

/// <summary>
/// �g�k�A��]�A�ړ��̏����������\����
/// </summary>
/// <param name="scale">�g�k</param>
/// <param name="rotate">��]</param>
/// <param name="translate">�ړ�</param>
struct SRT
{
	// �g�k
	Vector2 scale;
	// ��]
	float rotate;
	// �ړ�
	Vector2 translate;
};

struct Ball : SRT
{
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	float mass;
	float radius;
	unsigned int color;
};

struct Quad : SRT
{
	Vector2 leftTop;
	Vector2 rightTop;
	Vector2 leftBottom;
	Vector2 rightBottom;
};

struct Line : SRT
{
	Vector2 p0;
	Vector2 p1;
};

// 2 x 2 �̍s���\��
struct Matrix2x2
{
	float m[2][2];
};

// 3 x 3 �̍s���\��
struct Matrix3x3
{
	float m[3][3];
};


/// <summary>
/// �����_�����O�p�C�v���C���ōs���s��̏����������\����
/// </summary>
/// <param name="---">���[���h�s��</param>
/// <param name="view">�r���[�s��</param>
/// <param name="ortho">���ˉe�s��</param>
/// <param name="view">�r���[�|�[�g�s��</param>
struct RenderingPipeLine
{
	// ���[���h�s��
	//Matrix3x3 world;
	// �r���[�s��
	Matrix3x3 view;
	// ���ˉe�s��
	Matrix3x3 ortho;
	// �r���[�|�[�g�s��
	Matrix3x3 viewport;
};


#pragma endregion

// �ϐ�
#pragma region Variable

// �����̍���
static const int kRowHeight = 20;
// �����̉���
static const int kColumnWidth = 50;

// �g�k��]�ړ����ς��Ȃ��������p�萔
static const SRT kESRT = {
	{1,1},
	0,
	{0,0}
};

// �[���s��
static const Matrix3x3 kZeroMatrix = {
	0,0,0,
	0,0,0,
	0,0,0
};

// �[��(1)�s��
// ���[���h�s��Ƃ��Ďg����
static const Matrix3x3 kZeroOneMatrix = {
	0,0,0,
	0,0,0,
	0,0,1
};

// �P�ʍs��
static const Matrix3x3 kEMatrix = {
	1,0,0,
	0,1,0,
	0,0,1
};

// �J�����̑傫��
extern Vector2 MainCameraSize;
// �J�����̈ʒu
extern Vector2 MainCameraPosition;

// �����_�����O�p�C�v���C��
extern RenderingPipeLine RPL;

#pragma endregion

// �֐�
#pragma region Function


/// <summary>
///	2 x 2 �s����ȒP�ɕ\������
/// </summary>
/// <param name="x">x ���W</param>
/// <param name="y">y ���W</param>
/// <param name="matrix">�s��</param>
void MatrixScreenPrintf(int x, int y, Matrix2x2 matrix);

/// <summary>
/// 3 x 3 �s����ȒP�ɕ\������
/// </summary>
/// <param name="x">x ���W</param>
/// <param name="y">y ���W</param>
/// <param name="matrix">�s��</param>
void MatrixScreenPrintf(int x, int y, Matrix3x3 matrix);

/// <summary>
/// 1 x 2 �s��(�x�N�g��)���ȒP�ɕ\������
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <param name=""></param>
void VectorScreenPrintf(int, int, Vector2);


// �s��̉��Z
Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 matrix2);
// �x�N�g���̉��Z
Vector2 Add(Vector2 vector1, Vector2 vector2);
Vector2 Multiply(float f, Vector2 vector);

// �s��̌��Z
Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2);

// �s��̐�
Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2);

// �����ƍs��̐�
Matrix2x2 Multiply(float f, Matrix2x2 matrix);

// �s��̐�
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);

// �����ƍs��̐�
Matrix3x3 Multiply(float f, Matrix3x3 matrix);


// �x�N�g���ƍs��̐�
Vector2 Multiply(Vector2 vector, Matrix2x2 matrix);



/// <summary>
/// �g�k�s��̍쐬�֐�
/// </summary>
/// <param name="scale">�ϊ�����傫��</param>
/// <returns>�g�k�s��</returns>
Matrix2x2 MakeScaleMatrix2x2(Vector2 scale);


/// <summary>
/// �g�k�s��̍쐬�֐�
/// </summary>
/// <param name="scale">�ϊ�����傫��</param>
/// <returns>�g�k�s��</returns>
Matrix3x3 MakeScaleMatrix3x3(Vector2 scale);



/// <summary>
/// ��]�s��̍쐬�֐�
/// </summary>
/// <param name="theta">�ϊ�����p�x</param>
/// <returns>��]�s��</returns>
Matrix2x2 MakeRotateMatrix2x2(float theta);

/// <summary>
/// ��]�s��̍쐬�֐�
/// </summary>
/// <param name="theta">�ϊ�����p�x</param>
/// <returns>��]�s��</returns>
Matrix3x3 MakeRotateMatrix3x3(float theta);



/// <summary>
/// ���s�ړ��s��̍쐬�֐�
/// </summary>
/// <param name="translate">�ϊ�����񎟌��x�N�g��</param>
/// <returns>���s�ړ��s��</returns>
Matrix3x3 MakeTranslateMatrix(Vector2 translate);


/// <summary>
/// �񎟌��x�N�g���𓯎����W�Ƃ��ĕϊ�����
/// </summary>
/// <param name="vector">���̓񎟌��x�N�g��</param>
/// <param name="matrix">���s�ړ��s��</param>
/// <returns>�������W�ɕϊ����ꂽ�񎟌��x�N�g��</returns>
Vector2 Transform(Vector2 vector, Matrix3x3 matrix);

/// <summary>
/// �A�t�B���s��̍쐬�֐�
/// </summary>
/// <param name="scale">�ϊ�����傫��</param>
/// <param name="rotate">�ϊ�����p�x</param>
/// <param name="translate">�ϊ�����񎟌��x�N�g��</param>
/// <returns>�A�t�B���s��</returns>
Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate);
/// <summary>
/// �A�t�B���s��̍쐬�֐�
/// </summary>
/// <param name="srt">�g�k��]�ړ�</param>
/// <returns>�A�t�B���s��</returns>
Matrix3x3 MakeAffineMatrix(SRT srt);

/// <summary>
/// �r���[�s��̍쐬�֐�
/// </summary>
/// <returns>�r���[�s��</returns>
Matrix3x3 MakeViewMatrix();
/// <summary>
/// �r���[�s��̍쐬�֐�
/// </summary>
/// <param name="cameraPosition">�J�����̍��W</param>
/// <returns>�r���[�s��</returns>
Matrix3x3 MakeViewMatrix(Vector2 cameraPosition);

/// <summary>
/// ���ˉe�s��̍쐬�֐�
/// </summary>
/// <returns>�J�����T�C�Y���Q�Ƃ������ˉe�s��</returns>
Matrix3x3 MakeOrthoMatrix();
/// <summary>
/// ���ˉe�s��̍쐬�֐�
/// </summary>
/// <param name="cameraSize">�J�����͈̔�</param>
/// <returns>�J�����T�C�Y���Q�Ƃ������ˉe�s��</returns>
Matrix3x3 MakeOrthoMatrix(Vector2 cameraSize);

/// <summary>
/// �r���[�|�[�g�s��̍쐬�֐�(��ʑS��)
/// </summary>
/// <returns>�J�����T�C�Y���Q�Ƃ����r���[�|�[�g�s��</returns>
Matrix3x3 MakeViewPortMatrix();
/// <summary>
/// �r���[�|�[�g�s��̍쐬�֐�(�J�������̂܂܂̃T�C�Y)
/// ���炭�v�Z�����Ⴄ�̂Ő���ɓ��삵�Ȃ�
/// </summary>
/// <param name="cameraSize">�J�����͈̔�</param>
/// <returns>�J�����T�C�Y���Q�Ƃ����r���[�|�[�g�s��</returns>
Matrix3x3 MakeViewPortMatrix(Vector2 cameraSize);
/// <summary>
/// �r���[�|�[�g�s��̍쐬�֐�(���K)
/// </summary>
/// <param name="position">�`�悷�鍶����W</param>
/// <param name="size">�c���̒l</param>
/// <returns>�J�����T�C�Y���Q�Ƃ����r���[�|�[�g�s��</returns>
Matrix3x3 MakeViewPortMatrix(Vector2 position, Vector2 size);


Matrix3x3 MakeWvpVpMatrix(Matrix3x3 world, Matrix3x3 view, Matrix3x3 ortho, Matrix3x3 viewPort);
Matrix3x3 MakeWvpVpMatrix(Matrix3x3 world, RenderingPipeLine rpl);

/// <summary>
/// �����_�����O�p�C�v���C�������s����֐�
/// </summary>
/// <param name="vector">���[�J�����W</param>
/// <param name="world">���[���h�s��</param>
/// <param name="view">�r���[�s��</param>
/// <param name="ortho">���ˉe�s��</param>
/// <param name="viewport">�r���[�|�[�g�s��</param>
/// <returns>�����_�����O�p�C�v���C���ɒʂ��ꂽ���W</returns>
Vector2 RenderPipeLine(Vector2 vector, Matrix3x3 world, Matrix3x3 view, Matrix3x3 ortho, Matrix3x3 viewport);
/// <summary>
/// �����_�����O�p�C�v���C�������s����֐�(�J�������̂܂܂̃T�C�Y)
/// </summary>
/// <param name="vector">���[�J�����W</param>
/// <param name="world">���[���h�s��</param>
/// <returns>�����_�����O�p�C�v���C���ɒʂ��ꂽ���W</returns>
Vector2 RenderPipeLine(Vector2 vector, Matrix3x3 world);
/// <summary>
/// �����_�����O�p�C�v���C�������s����֐�(extern�ϐ� RPL ���g������)
/// </summary>
/// <param name="vector">���[�J�����W</param>
/// <returns>�����_�����O�p�C�v���C���ɒʂ��ꂽ���W</returns>
//Vector2 RenderPipeLine(Vector2 vector);
/// <summary>
/// �����_�����O�p�C�v���C�������s����֐�(�\�����ƕp�x����)
/// </summary>
/// <param name="vector">���[�J�����W</param>
/// <param name="rpl">�����_�����O�p�C�v���C���Ŏg���s��̏����������\����</param>
/// <returns>�����_�����O�p�C�v���C���ɒʂ��ꂽ���W</returns>
Vector2 RenderPipeLine(Vector2 vector, SRT srt, RenderingPipeLine rpl);
/// <summary>
/// �����_�����O�p�C�v���C�������s����֐�
/// </summary>
/// <param name="object">���[�J�����W��SRT���������ϐ�</param>
/// <param name="rpl">�s��̏W�܂�</param>
/// <returns>�����_�����O�p�C�v���C���ɒʂ��ꂽ���W</returns>
Quad RenderPipeLine(Quad object, RenderingPipeLine rpl);
Quad RenderPipeLine(Quad object, SRT srt, RenderingPipeLine rpl);
/// <summary>
/// �����_�����O�p�C�v���C�������s����֐�
/// </summary>
/// <param name="object">���[�J�����W��SRT���������ϐ�</param>
/// <param name="rpl">�s��̏W�܂�</param>
/// <returns>�����_�����O�p�C�v���C���ɒʂ��ꂽ���W</returns>
Line RenderPipeLine(Line object, RenderingPipeLine rpl);
Line RenderPipeLine(Line object, SRT srt, RenderingPipeLine rpl);

/// <summary>
/// 2 x 2 �t�s��쐬�֐�
/// </summary>
/// <param name="matrix">2 x 2 �s��</param>
/// <returns>2 x 2 �t�s��</returns>
Matrix2x2 Inverse(Matrix2x2 matrix);

/// <summary>
/// 2 x 2 �]�u�s��̍쐬�֐�
/// </summary>
/// <param name="matrix">2 x 2 �s��</param>
/// <returns>2 x 2 �]�u�s��</returns>
Matrix2x2 Transpose(Matrix2x2 matrix);


/// <summary>
/// 3 x 3 �t�s��쐬�֐�
/// </summary>
/// <param name="matrix">3 x 3 �s��</param>
/// <returns>3 x 3 �t�s��</returns>
Matrix3x3 Inverse(Matrix3x3 matrix);

/// <summary>
/// 3 x 3 �]�u�s��̍쐬�֐�
/// </summary>
/// <param name="matrix">3 x 3 �s��</param>
/// <returns>3 x 3 �]�u�s��</returns>
Matrix3x3 Transpose(Matrix3x3 matrix);

/// <summary>
/// ���`��Ԃ���֐�
/// </summary>
/// <param name="a">�_ 1</param>
/// <param name="b">�_ 1</param>
/// <param name="t">0 �` 1</param>
/// <returns>��_�̊Ԃ̓_</returns>
Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
/// <summary>
/// 2 ���x�W�G�Ȑ���̓_�����߂�֐�
/// </summary>
/// <param name="p0">�_ 0</param>
/// <param name="p1">�_ 1</param>
/// <param name="p2">�_ 2</param>
/// <param name="t">0 �` 1</param>
/// <returns>�_</returns>
Vector2 Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, float t);


#pragma endregion


