#pragma once
#include "Matrix.h"


const char kWindowTitle[] = "LC1A_18_�i�K�C���}�g_�m�F�ۑ�";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;


// ���[���h���W�n�� Y ��
const int WORLD_BORDER = 0;

// ���W��ϊ�
int WtoS(int);
float WtoS(float);
// �l�AMIN�AMAX�Ŋۂ߂�
float clamp(float, int, int);
float clamp(float, float, float);
