#pragma once

// 構造体
#pragma region Structure

// 2 次元ベクトルを表す
struct Vector2
{
	float x;
	float y;
};

/// <summary>
/// 拡縮、回転、移動の情報を持った構造体
/// </summary>
/// <param name="scale">拡縮</param>
/// <param name="rotate">回転</param>
/// <param name="translate">移動</param>
struct SRT
{
	// 拡縮
	Vector2 scale;
	// 回転
	float rotate;
	// 移動
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

// 2 x 2 の行列を表す
struct Matrix2x2
{
	float m[2][2];
};

// 3 x 3 の行列を表す
struct Matrix3x3
{
	float m[3][3];
};


/// <summary>
/// レンダリングパイプラインで行う行列の情報を持った構造体
/// </summary>
/// <param name="---">ワールド行列</param>
/// <param name="view">ビュー行列</param>
/// <param name="ortho">正射影行列</param>
/// <param name="view">ビューポート行列</param>
struct RenderingPipeLine
{
	// ワールド行列
	//Matrix3x3 world;
	// ビュー行列
	Matrix3x3 view;
	// 正射影行列
	Matrix3x3 ortho;
	// ビューポート行列
	Matrix3x3 viewport;
};


#pragma endregion

// 変数
#pragma region Variable

// 文字の高さ
static const int kRowHeight = 20;
// 文字の横幅
static const int kColumnWidth = 50;

// 拡縮回転移動が変わらない初期化用定数
static const SRT kESRT = {
	{1,1},
	0,
	{0,0}
};

// ゼロ行列
static const Matrix3x3 kZeroMatrix = {
	0,0,0,
	0,0,0,
	0,0,0
};

// ゼロ(1)行列
// ワールド行列として使える
static const Matrix3x3 kZeroOneMatrix = {
	0,0,0,
	0,0,0,
	0,0,1
};

// 単位行列
static const Matrix3x3 kEMatrix = {
	1,0,0,
	0,1,0,
	0,0,1
};

// カメラの大きさ
extern Vector2 MainCameraSize;
// カメラの位置
extern Vector2 MainCameraPosition;

// レンダリングパイプライン
extern RenderingPipeLine RPL;

#pragma endregion

// 関数
#pragma region Function


/// <summary>
///	2 x 2 行列を簡単に表示する
/// </summary>
/// <param name="x">x 座標</param>
/// <param name="y">y 座標</param>
/// <param name="matrix">行列</param>
void MatrixScreenPrintf(int x, int y, Matrix2x2 matrix);

/// <summary>
/// 3 x 3 行列を簡単に表示する
/// </summary>
/// <param name="x">x 座標</param>
/// <param name="y">y 座標</param>
/// <param name="matrix">行列</param>
void MatrixScreenPrintf(int x, int y, Matrix3x3 matrix);

/// <summary>
/// 1 x 2 行列(ベクトル)を簡単に表示する
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <param name=""></param>
void VectorScreenPrintf(int, int, Vector2);


// 行列の加算
Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 matrix2);
// ベクトルの加算
Vector2 Add(Vector2 vector1, Vector2 vector2);
Vector2 Multiply(float f, Vector2 vector);

// 行列の減算
Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2);

// 行列の積
Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2);

// 実数と行列の積
Matrix2x2 Multiply(float f, Matrix2x2 matrix);

// 行列の積
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);

// 実数と行列の積
Matrix3x3 Multiply(float f, Matrix3x3 matrix);


// ベクトルと行列の積
Vector2 Multiply(Vector2 vector, Matrix2x2 matrix);



/// <summary>
/// 拡縮行列の作成関数
/// </summary>
/// <param name="scale">変換する大きさ</param>
/// <returns>拡縮行列</returns>
Matrix2x2 MakeScaleMatrix2x2(Vector2 scale);


/// <summary>
/// 拡縮行列の作成関数
/// </summary>
/// <param name="scale">変換する大きさ</param>
/// <returns>拡縮行列</returns>
Matrix3x3 MakeScaleMatrix3x3(Vector2 scale);



/// <summary>
/// 回転行列の作成関数
/// </summary>
/// <param name="theta">変換する角度</param>
/// <returns>回転行列</returns>
Matrix2x2 MakeRotateMatrix2x2(float theta);

/// <summary>
/// 回転行列の作成関数
/// </summary>
/// <param name="theta">変換する角度</param>
/// <returns>回転行列</returns>
Matrix3x3 MakeRotateMatrix3x3(float theta);



/// <summary>
/// 平行移動行列の作成関数
/// </summary>
/// <param name="translate">変換する二次元ベクトル</param>
/// <returns>平行移動行列</returns>
Matrix3x3 MakeTranslateMatrix(Vector2 translate);


/// <summary>
/// 二次元ベクトルを同次座標として変換する
/// </summary>
/// <param name="vector">元の二次元ベクトル</param>
/// <param name="matrix">平行移動行列</param>
/// <returns>同次座標に変換された二次元ベクトル</returns>
Vector2 Transform(Vector2 vector, Matrix3x3 matrix);

/// <summary>
/// アフィン行列の作成関数
/// </summary>
/// <param name="scale">変換する大きさ</param>
/// <param name="rotate">変換する角度</param>
/// <param name="translate">変換する二次元ベクトル</param>
/// <returns>アフィン行列</returns>
Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate);
/// <summary>
/// アフィン行列の作成関数
/// </summary>
/// <param name="srt">拡縮回転移動</param>
/// <returns>アフィン行列</returns>
Matrix3x3 MakeAffineMatrix(SRT srt);

/// <summary>
/// ビュー行列の作成関数
/// </summary>
/// <returns>ビュー行列</returns>
Matrix3x3 MakeViewMatrix();
/// <summary>
/// ビュー行列の作成関数
/// </summary>
/// <param name="cameraPosition">カメラの座標</param>
/// <returns>ビュー行列</returns>
Matrix3x3 MakeViewMatrix(Vector2 cameraPosition);

/// <summary>
/// 正射影行列の作成関数
/// </summary>
/// <returns>カメラサイズを参照した正射影行列</returns>
Matrix3x3 MakeOrthoMatrix();
/// <summary>
/// 正射影行列の作成関数
/// </summary>
/// <param name="cameraSize">カメラの範囲</param>
/// <returns>カメラサイズを参照した正射影行列</returns>
Matrix3x3 MakeOrthoMatrix(Vector2 cameraSize);

/// <summary>
/// ビューポート行列の作成関数(画面全体)
/// </summary>
/// <returns>カメラサイズを参照したビューポート行列</returns>
Matrix3x3 MakeViewPortMatrix();
/// <summary>
/// ビューポート行列の作成関数(カメラそのままのサイズ)
/// 恐らく計算式が違うので正常に動作しない
/// </summary>
/// <param name="cameraSize">カメラの範囲</param>
/// <returns>カメラサイズを参照したビューポート行列</returns>
Matrix3x3 MakeViewPortMatrix(Vector2 cameraSize);
/// <summary>
/// ビューポート行列の作成関数(正規)
/// </summary>
/// <param name="position">描画する左上座標</param>
/// <param name="size">縦横の値</param>
/// <returns>カメラサイズを参照したビューポート行列</returns>
Matrix3x3 MakeViewPortMatrix(Vector2 position, Vector2 size);


Matrix3x3 MakeWvpVpMatrix(Matrix3x3 world, Matrix3x3 view, Matrix3x3 ortho, Matrix3x3 viewPort);
Matrix3x3 MakeWvpVpMatrix(Matrix3x3 world, RenderingPipeLine rpl);

/// <summary>
/// レンダリングパイプラインを実行する関数
/// </summary>
/// <param name="vector">ローカル座標</param>
/// <param name="world">ワールド行列</param>
/// <param name="view">ビュー行列</param>
/// <param name="ortho">正射影行列</param>
/// <param name="viewport">ビューポート行列</param>
/// <returns>レンダリングパイプラインに通された座標</returns>
Vector2 RenderPipeLine(Vector2 vector, Matrix3x3 world, Matrix3x3 view, Matrix3x3 ortho, Matrix3x3 viewport);
/// <summary>
/// レンダリングパイプラインを実行する関数(カメラそのままのサイズ)
/// </summary>
/// <param name="vector">ローカル座標</param>
/// <param name="world">ワールド行列</param>
/// <returns>レンダリングパイプラインに通された座標</returns>
Vector2 RenderPipeLine(Vector2 vector, Matrix3x3 world);
/// <summary>
/// レンダリングパイプラインを実行する関数(extern変数 RPL を使うもの)
/// </summary>
/// <param name="vector">ローカル座標</param>
/// <returns>レンダリングパイプラインに通された座標</returns>
//Vector2 RenderPipeLine(Vector2 vector);
/// <summary>
/// レンダリングパイプラインを実行する関数(予測だと頻度多め)
/// </summary>
/// <param name="vector">ローカル座標</param>
/// <param name="rpl">レンダリングパイプラインで使う行列の情報を持った構造体</param>
/// <returns>レンダリングパイプラインに通された座標</returns>
Vector2 RenderPipeLine(Vector2 vector, SRT srt, RenderingPipeLine rpl);
/// <summary>
/// レンダリングパイプラインを実行する関数
/// </summary>
/// <param name="object">ローカル座標とSRTを持った変数</param>
/// <param name="rpl">行列の集まり</param>
/// <returns>レンダリングパイプラインに通された座標</returns>
Quad RenderPipeLine(Quad object, RenderingPipeLine rpl);
Quad RenderPipeLine(Quad object, SRT srt, RenderingPipeLine rpl);
/// <summary>
/// レンダリングパイプラインを実行する関数
/// </summary>
/// <param name="object">ローカル座標とSRTを持った変数</param>
/// <param name="rpl">行列の集まり</param>
/// <returns>レンダリングパイプラインに通された座標</returns>
Line RenderPipeLine(Line object, RenderingPipeLine rpl);
Line RenderPipeLine(Line object, SRT srt, RenderingPipeLine rpl);

/// <summary>
/// 2 x 2 逆行列作成関数
/// </summary>
/// <param name="matrix">2 x 2 行列</param>
/// <returns>2 x 2 逆行列</returns>
Matrix2x2 Inverse(Matrix2x2 matrix);

/// <summary>
/// 2 x 2 転置行列の作成関数
/// </summary>
/// <param name="matrix">2 x 2 行列</param>
/// <returns>2 x 2 転置行列</returns>
Matrix2x2 Transpose(Matrix2x2 matrix);


/// <summary>
/// 3 x 3 逆行列作成関数
/// </summary>
/// <param name="matrix">3 x 3 行列</param>
/// <returns>3 x 3 逆行列</returns>
Matrix3x3 Inverse(Matrix3x3 matrix);

/// <summary>
/// 3 x 3 転置行列の作成関数
/// </summary>
/// <param name="matrix">3 x 3 行列</param>
/// <returns>3 x 3 転置行列</returns>
Matrix3x3 Transpose(Matrix3x3 matrix);

/// <summary>
/// 線形補間する関数
/// </summary>
/// <param name="a">点 1</param>
/// <param name="b">点 1</param>
/// <param name="t">0 ～ 1</param>
/// <returns>二点の間の点</returns>
Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
/// <summary>
/// 2 次ベジエ曲線上の点を求める関数
/// </summary>
/// <param name="p0">点 0</param>
/// <param name="p1">点 1</param>
/// <param name="p2">点 2</param>
/// <param name="t">0 ～ 1</param>
/// <returns>点</returns>
Vector2 Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, float t);


#pragma endregion


