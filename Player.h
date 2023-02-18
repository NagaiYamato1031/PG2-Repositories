#pragma once
#include "Matrix.h"

class Bullet;

class Player
{
public:
	Player();
	~Player();

	void Initialize();
	void Update(const char* keys, const char* preKeys);
	void Draw();

	Bullet** GetBullets() { return bullets; };
	Bullet* GetBullet(int index) { return bullets[index]; };

	static const int kBulletNums = 32;
private:

	Vector2 position;
	Vector2 velocity;
	Vector2 radius;

	Bullet* bullets[kBulletNums];

};

