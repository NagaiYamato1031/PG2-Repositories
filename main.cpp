#include <Novice.h>
#include "main.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Matrix.h"


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// 初期設定
	MainCameraPosition = { kWindowWidth / 2.0f,kWindowHeight / 2.0f };
	MainCameraSize = { kWindowWidth,kWindowHeight };

	//RPL.world = kEMatrix;
	RPL.view = MakeViewMatrix(MainCameraPosition);
	RPL.ortho = MakeOrthoMatrix(MainCameraSize);
	RPL.viewport = MakeViewPortMatrix({ 0,0 }, { kWindowWidth,kWindowHeight });

	// 計算用



	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///



		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

int WtoS(int a) {
	return a * -1 + WORLD_BORDER;
}

float WtoS(float a) {
	return a * -1 + WORLD_BORDER;
}

float clamp(float a, int min, int max) {
	if (a < min) {
		return min;
	}
	if (max < a) {
		return max;
	}
	return a;
}

float clamp(float a, float min, float max) {
	if (a < min) {
		return min;
	}
	if (max < a) {
		return max;
	}
	return a;
}