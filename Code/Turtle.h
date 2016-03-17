#pragma once
#include "Entity.h"
#include <SFML\Graphics.hpp>

using namespace sf;

enum TurtleDirection { LEFT, RIGHT, UP, DOWN };

class Turtle sealed : public Entity
{
public:
	Turtle(float x, float y);
	~Turtle() {};
	void update(float delta) override;
	void draw(RenderWindow& window) override;
	bool removed() override;
	void shoot();
	void turn(TurtleDirection direction);
	FloatRect getBounds() override;
	void addAmmo();
	bool isInvincible();
	void hit();
	void powerUp();
	bool power();
	const Vector2f& getPos() const;
private:
	TurtleDirection direction;
	bool isMoving;
	bool justPressedSpace;
	int ammo;
	bool invincible;
	Clock hurtTimer;
	bool hasPower;
	Clock powerTimer;
	Vector2f pos;
};