#pragma once
#include "Fireball.h"
#include <SFML\Graphics.hpp>

class BigFireball sealed : public Fireball
{
public:
	BigFireball(float x, float y, TurtleDirection direction, bool enemy = false);
	~BigFireball() {};
	void update(float delta) override;
	void draw(RenderWindow& window) override;
};