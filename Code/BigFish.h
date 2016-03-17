#pragma once
#include "Fish.h"
#include <SFML\Graphics.hpp>

class BigFish sealed : public Fish
{
public:
	BigFish(float x, float y, bool leave);
	~BigFish() {};
	void update(float delta) override;
	void draw(RenderWindow& window) override;
private:
	Clock touchTimer;
	bool justTouched;
};