#pragma once
#include "Matrix.h"


const char kWindowTitle[] = "LC1A_18_ナガイヤマト_確認課題";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;


// ワールド座標系の Y 軸
const int WORLD_BORDER = 0;

// 座標を変換
int WtoS(int);
float WtoS(float);
// 値、MIN、MAXで丸める
float clamp(float, int, int);
float clamp(float, float, float);
