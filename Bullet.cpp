#include "Bullet.h"
#include <Novice.h>

Bullet::Bullet() {
	Initialize();
}

Bullet::~Bullet() {

}


void Bullet::Initialize() {
	position = { -1000,-1000 };
	velocity = { 0,4 };
	radius = { 10,10 };
	isActive = false;
}

void Bullet::Update() {
	if (!isActive) {
		return;
	}
	if (720 < position.y) {
		Initialize();
	}
	position.y += velocity.y;
}

void Bullet::Draw() {
	if (!isActive) {
		return;
	}
	Vector2 temp = RenderPipeLine(position, kESRT, RPL);
	Novice::DrawEllipse(temp.x, temp.y, radius.x, radius.y, 0, BLUE, kFillModeSolid);

}

bool Bullet::Shot(const Vector2& pos) {
	if (isActive) {
		return false;
	}
	position = pos;
	isActive = true;
	return true;
}
