#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <assert.h>
#include "Matrix.h"

// 変数
#pragma region Variable

Vector2 MainCameraSize = { 1280,720 };
Vector2 MainCameraPosition = { 0,0 };

//RenderingPipeLine RPL = {
//	kZeroOneMatrix,kZeroOneMatrix,
//	kZeroOneMatrix,kZeroOneMatrix
//};

RenderingPipeLine RPL = {
	kZeroOneMatrix,
	kZeroOneMatrix,kZeroOneMatrix
};

#pragma endregion


// 関数
#pragma region Function



void MatrixScreenPrintf(int x, int y, Matrix2x2 matrix) {
	for (int row = 0; row < 2; ++row) {
		for (int column = 0; column < 2; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth,
				y + row * kRowHeight, "%.02f", matrix.m[row][column]);
		}
	}
}

void MatrixScreenPrintf(int x, int y, Matrix3x3 matrix) {
	for (int row = 0; row < 3; ++row) {
		for (int column = 0; column < 3; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth,
				y + row * kRowHeight, "%.02f", matrix.m[row][column]);
		}
	}
}

void VectorScreenPrintf(int x, int y, Vector2 vector) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
}

Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	Matrix2x2 tmp;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
		{
			tmp.m[i][j] = matrix1.m[i][j] + matrix2.m[i][j];
		}
	}
	return tmp;
}

Vector2 Add(Vector2 vector1, Vector2 vector2) {
	Vector2 tmp;

	tmp.x = vector1.x + vector2.x;
	tmp.y = vector1.y + vector2.y;

	return tmp;
}

Vector2 Multiply(float f,Vector2 vector) {
	Vector2 tmp = vector;
	tmp.x *= f;
	tmp.y *= f;
	return tmp;
}

Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	Matrix2x2 tmp;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
		{
			tmp.m[i][j] = matrix1.m[i][j] - matrix2.m[i][j];
		}
	}
	return tmp;

}

Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	Matrix2x2 tmp;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
		{
			tmp.m[i][j] = matrix1.m[i][0] * matrix2.m[0][j] + matrix1.m[i][1] * matrix2.m[1][j];
		}
	}
	return tmp;
}

Matrix2x2 Multiply(float f, Matrix2x2 matrix2) {
	Matrix2x2 tmp;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
		{
			tmp.m[i][j] = f * matrix2.m[i][j];
		}
	}
	return tmp;
}

Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {
	Matrix3x3 tmp;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
		{
			tmp.m[i][j] = matrix1.m[i][0] * matrix2.m[0][j] + matrix1.m[i][1] * matrix2.m[1][j] + matrix1.m[i][2] * matrix2.m[2][j];
		}
	}
	return tmp;
}

Matrix3x3 Multiply(float f, Matrix3x3 matrix2) {
	Matrix3x3 tmp;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
		{
			tmp.m[i][j] = f * matrix2.m[i][j];
		}
	}
	return tmp;
}

Vector2 Multiply(Vector2 vector, Matrix2x2 matrix) {
	Vector2 tmp;
	tmp.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0];
	tmp.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1];
	return tmp;
}


Matrix2x2 MakeScaleMatrix2x2(Vector2 scale) {
	Matrix2x2 result = { scale.x,0,
						0,scale.y, };
	return result;
}

Matrix3x3 MakeScaleMatrix3x3(Vector2 scale) {
	Matrix3x3 result = { scale.x,0,0,
						0,scale.y,0,
						0,0,1 };
	return result;
}



Matrix2x2 MakeRotateMatrix2x2(float theta) {
	Matrix2x2 result = { cosf(theta),sinf(theta),
					-sinf(theta),cosf(theta) };
	return result;
}

Matrix3x3 MakeRotateMatrix3x3(float theta) {
	Matrix3x3 result = { cosf(theta),sinf(theta),0,
					-sinf(theta),cosf(theta),0,
					0,0,1 };
	return result;
}



Matrix3x3 MakeTranslateMatrix(Vector2 translate) {
	Matrix3x3 result = { 0 };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = 0;
		}
	}
	// 単位行列
	result.m[0][0] = 1;
	result.m[1][1] = 1;
	result.m[2][2] = 1;

	// ベクトルを単位行列に追加
	result.m[2][0] = translate.x;
	result.m[2][1] = translate.y;
	return result;

}


Vector2 Transform(Vector2 vector, Matrix3x3 matrix) {
	Vector2 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	// w はゼロになってはいけない
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	return result;
}


Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate) {
	Matrix3x3 result;
	result = Multiply(MakeScaleMatrix3x3(scale), MakeRotateMatrix3x3(rotate));
	result = Multiply(result, MakeTranslateMatrix(translate));
	return result;
}

Matrix3x3 MakeAffineMatrix(SRT srt) {
	Matrix3x3 result;
	result = Multiply(MakeScaleMatrix3x3(srt.scale), MakeRotateMatrix3x3(srt.rotate));
	result = Multiply(result, MakeTranslateMatrix(srt.translate));
	return result;
}

Matrix3x3 MakeViewMatrix() {
	Matrix3x3 result = {
		1,0,0,
		0,1,0,
		MainCameraPosition.x,MainCameraPosition.y,1
	};
	return result;
}

Matrix3x3 MakeViewMatrix(Vector2 cameraPosition) {
	Matrix3x3 result = {
		1,0,0,
		0,1,0,
		cameraPosition.x,cameraPosition.y,1
	};
	return Inverse(result);
}


Matrix3x3 MakeOrthoMatrix() {
	Matrix3x3 result = {
		2.0f / MainCameraSize.x,0,0,
		0,2.0f / MainCameraSize.y,0,
		0,0,1,
	};
	return result;

}

Matrix3x3 MakeOrthoMatrix(Vector2 cameraSize) {
	Matrix3x3 result = {
		2.0f / cameraSize.x,0,0,
		0,2.0f / cameraSize.y,0,
		0,0,1,
	};
	return result;

}

Matrix3x3 MakeViewPortMatrix() {
	Matrix3x3 result = {
		MainCameraSize.x / 2.0f,0,0,
		0,-MainCameraSize.y / 2.0f,0,
		-MainCameraSize.x / 2.0f + MainCameraSize.x / 2.0f,MainCameraSize.y / 2.0f + MainCameraSize.y / 2.0f,1
	};
	return result;
}

Matrix3x3 MakeViewPortMatrix(Vector2 cameraSize) {
	Matrix3x3 result = {
		cameraSize.x / 2.0f,0,0,
		0,-cameraSize.y / 2.0f,0,
		-cameraSize.x / 2.0f + cameraSize.x / 2.0f,cameraSize.y / 2.0f + cameraSize.y / 2.0f,1
	};
	return result;
}

Matrix3x3 MakeViewPortMatrix(Vector2 position,Vector2 size) {
	Matrix3x3 result = {
		size.x / 2.0f,0,0,
		0,-size.y / 2.0f,0,
		position.x + size.x / 2.0f,position.y + size.y / 2.0f,1
	};
	return result;
}

Matrix3x3 MakeWvpVpMatrix(Matrix3x3 world, Matrix3x3 view, Matrix3x3 ortho, Matrix3x3 viewport) {
	Matrix3x3 result = Multiply(world, view);
	result = Multiply(result, ortho);
	result = Multiply(result, viewport);
	return result;
}

Matrix3x3 MakeWvpVpMatrix(Matrix3x3 world, RenderingPipeLine rpl) {
	Matrix3x3 result = Multiply(world, rpl.view);
	result = Multiply(result, rpl.ortho);
	result = Multiply(result, rpl.viewport);
	return result;
}


Vector2 RenderPipeLine(Vector2 vector, Matrix3x3 world, Matrix3x3 view, Matrix3x3 ortho, Matrix3x3 viewport) {
	Vector2 result;
	result = Transform(vector, world);
	result = Transform(result, view);
	result = Transform(result, ortho);
	result = Transform(result, viewport);
	return result;
}

Vector2 RenderPipeLine(Vector2 vector,Matrix3x3 world) {
	Vector2 result;
	result = Transform(vector, world);
	result = Transform(result, MakeViewMatrix());
	result = Transform(result, MakeOrthoMatrix());
	result = Transform(result, MakeViewPortMatrix());
	return result;
}

//Vector2 RenderPipeLine(Vector2 vector) {
//	Vector2 result;
//	result = Transform(vector, RPL.world);
//	result = Transform(result, RPL.view);
//	result = Transform(result, RPL.ortho);
//	result = Transform(result, RPL.viewport);
//	return result;
//}
//
Vector2 RenderPipeLine(Vector2 vector, SRT srt,RenderingPipeLine rpl) {
	Vector2 result;
	result = Transform(vector, MakeAffineMatrix(srt));
	result = Transform(result, rpl.view);
	result = Transform(result, rpl.ortho);
	result = Transform(result, rpl.viewport);
	return result;
}

Quad RenderPipeLine(Quad object, RenderingPipeLine rpl) {
	Quad result;
	Matrix3x3 wvpVpMatrix = MakeWvpVpMatrix(MakeAffineMatrix(object), rpl);
	Vector2 temp;
	temp = Transform(object.leftTop, wvpVpMatrix);
	result.leftTop = temp;
	temp = Transform(object.rightTop, wvpVpMatrix);
	result.rightTop = temp;
	temp = Transform(object.leftBottom, wvpVpMatrix);
	result.leftBottom = temp;
	temp = Transform(object.rightBottom, wvpVpMatrix);
	result.rightBottom = temp;
	return result;

}

Quad RenderPipeLine(Quad object, SRT srt, RenderingPipeLine rpl) {
	Quad result;
	Matrix3x3 wvpVpMatrix = MakeWvpVpMatrix(MakeAffineMatrix(srt), rpl);
	Vector2 temp;
	temp = Transform(object.leftTop, wvpVpMatrix);
	result.leftTop = temp;
	temp = Transform(object.rightTop, wvpVpMatrix);
	result.rightTop = temp;
	temp = Transform(object.leftBottom, wvpVpMatrix);
	result.leftBottom = temp;
	temp = Transform(object.rightBottom, wvpVpMatrix);
	result.rightBottom = temp;
	return result;

}

Line RenderPipeLine(Line object, RenderingPipeLine rpl) {
	Line result;
	Matrix3x3 wvpVpMatrix = MakeWvpVpMatrix(MakeAffineMatrix(object), rpl);
	Vector2 temp;
	temp = Transform(object.p0, wvpVpMatrix);
	result.p0 = temp;
	temp = Transform(object.p1, wvpVpMatrix);
	result.p1 = temp;
	return result;
}

Line RenderPipeLine(Line object, SRT srt, RenderingPipeLine rpl) {
	Line result;
	Matrix3x3 wvpVpMatrix = MakeWvpVpMatrix(MakeAffineMatrix(srt), rpl);
	Vector2 temp;
	temp = Transform(object.p0, wvpVpMatrix);
	result.p0 = temp;
	temp = Transform(object.p1, wvpVpMatrix);
	result.p1 = temp;
	return result;
}


Matrix2x2 Inverse(Matrix2x2 matrix) {
	Matrix2x2 result;
	float determinant;
	determinant = matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0];
	assert(determinant != 0.0f);
	result.m[0][0] = matrix.m[1][1];
	result.m[0][1] = -matrix.m[0][1];
	result.m[1][0] = -matrix.m[1][0];
	result.m[1][1] = matrix.m[0][0];
	return Multiply(1 / determinant, result);
}

Matrix2x2 Transpose(Matrix2x2 matrix) {
	Matrix2x2 result;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			result.m[j][i] = matrix.m[i][j];
		}
	}
	return result;
}


Matrix3x3 Inverse(Matrix3x3 matrix) {
	Matrix3x3 result;
	float determinant;
	// | A | のやつ	
	determinant =
		matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] +
		matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] +
		matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] -
		matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] -
		matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] -
		matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1];
	assert(determinant != 0.0f);
	result.m[0][0] = matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1];
	result.m[0][1] = -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]);
	result.m[0][2] = matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1];
	result.m[1][0] = -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]);
	result.m[1][1] = matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0];
	result.m[1][2] = -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]);
	result.m[2][0] = matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0];
	result.m[2][1] = -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]);
	result.m[2][2] = matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0];
	return Multiply(1 / determinant, result);
}

Matrix3x3 Transpose(Matrix3x3 matrix) {
	Matrix3x3 result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[j][i] = matrix.m[i][j];
		}
	}
	return result;
}

Vector2 Lerp(const Vector2& a, const Vector2& b, float t) {
	return Add(Multiply(t, a), Multiply((1.0f - t), b));
}

Vector2 Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, float t) {
	Vector2 p0p1 = Lerp(p0, p1, t);
	Vector2 p1p2 = Lerp(p1, p2, t);
	Vector2 p = Lerp(p0p1, p1p2, t);
	return p;
}


#pragma endregion

