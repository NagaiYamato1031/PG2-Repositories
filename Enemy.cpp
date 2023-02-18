#include "Enemy.h"
#include <Novice.h>
#include <math.h>

#include "Bullet.h"

Enemy::Enemy(const Vector2& pos) {
	Initialize(pos);
}

Enemy::~Enemy() {

}


void Enemy::Initialize(const Vector2& pos) {
	position = pos;
	velocity = { 4,0 };
	radius = { 20,20 };
	isAlive = true;
}

void Enemy::Update() {
	if (!isAlive) {
		return;
	}
	if (position.x + velocity.x - radius.x < 0 || 1280 < position.x + velocity.x + radius.x) {
		velocity.x *= -1;
	}
	position.x += velocity.x;
}

void Enemy::Draw() {
	if (!isAlive) {
		return;
	}
	Vector2 temp = RenderPipeLine(position, kESRT, RPL);
	Novice::DrawEllipse(temp.x, temp.y, radius.x, radius.y, 0, RED, kFillModeSolid);
}

bool Enemy::CheckHitBullet(Bullet* bullet) {
	if (!isAlive || !bullet->GetisActive()) {
		return false;
	}
	Vector2 a = { position.x - bullet->GetPosition().x,position.y - bullet->GetPosition().y};
	float distance = sqrtf(a.x * a.x + a.y * a.y);
	if (distance < (this->radius.x + bullet->GetRadius().x)) {
		isAlive = false;
		bullet->Initialize();
		return true;
	}
	return false;
}