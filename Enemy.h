#pragma once
#include "Matrix.h"

class Bullet;

class Enemy
{
public:
	Enemy(const Vector2& pos);
	~Enemy();

	void Initialize(const Vector2& pos);
	void Update();
	void Draw();

	static bool isAlive;


	bool CheckHitBullet(Bullet* bullet);

private:

	Vector2 position;
	Vector2 velocity;
	Vector2 radius;


};

