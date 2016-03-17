#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

class Entity abstract
{
public:
	Entity() {};
	virtual ~Entity() {};
	virtual void draw(RenderWindow& window) abstract;
	virtual void update(float delta) abstract;
	virtual bool removed() abstract;
	virtual FloatRect getBounds() abstract;
protected:
	float x, y;
	Sprite sprite;
	int frame;
	Vector2f velocity;
	Clock timer;
	bool isRemoved;
	FloatRect bounds;
};