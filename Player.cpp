#include "Player.h"
#include <Novice.h>

#include "Bullet.h"

Player::Player() {
	Initialize();
}

Player::~Player() {

}


void Player::Initialize() {
	position = { 100,100 };
	velocity = { 0,0 };
	radius = { 20,20 };
	for (int i = 0; i < kBulletNums; i++) {
		bullets[i] = new Bullet();
		bullets[i]->Initialize();
	}
}

void Player::Update(const char* keys, const char* preKeys) {
	float spd = 6;
	velocity = { 0,0 };
	if (keys[DIK_A]) {
		velocity.x -= spd;
	}
	if (keys[DIK_D]) {
		velocity.x += spd;
	}
	if (keys[DIK_W]) {
		velocity.y += spd;
	}
	if (keys[DIK_S]) {
		velocity.y -= spd;
	}

	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		for (int i = 0; i < kBulletNums; i++) {
			if (bullets[i]->Shot(position)) {
				break;
			}
		}
	}
	for (int i = 0; i < kBulletNums; i++) {
		bullets[i]->Update();
	}

	position.x += velocity.x;
	position.y += velocity.y;
}

void Player::Draw() {
	for (int i = 0; i < kBulletNums; i++) {
		bullets[i]->Draw();
	}

	Vector2 temp = RenderPipeLine(position, kESRT, RPL);
	Novice::DrawEllipse(temp.x, temp.y, radius.x, radius.y, 0, WHITE, kFillModeSolid);

}
