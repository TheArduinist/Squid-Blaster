#pragma once
#include "Entity.h"
#include "Turtle.h"
#include <SFML\Graphics.hpp>

#define _USE_MATH_DEFINES

#include <math.h>

using namespace sf;

class Fireball : public Entity
{
public:
	Fireball() {};
	Fireball(float x, float y, TurtleDirection direction, bool enemy = false);
	Fireball(float x, float y, const Vector2f& turtlePos, bool enemy = false);
	virtual ~Fireball() {};
	void draw(RenderWindow& window) override;
	virtual void update(float delta) override;
	bool removed() override;
	FloatRect getBounds() override;
	virtual void setEnemy(bool enemy);

protected:
	bool isEnemy;

	static const float to_degrees;
	static const float to_radians;
};