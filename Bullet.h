#pragma once
#include "Matrix.h"

class Bullet
{
public:

	Bullet();
	~Bullet();

	void Initialize();
	void Update();
	void Draw();

	bool Shot(const Vector2& pos);


	Vector2 GetPosition() { return position; };
	Vector2 GetVelocity() { return velocity; };
	Vector2 GetRadius() { return  radius; };

	bool GetisActive() { return isActive; };



	void SetisActive(bool a) { isActive = a; };

private:

	Vector2 position;
	Vector2 velocity;
	Vector2 radius;

	bool isActive;

};

