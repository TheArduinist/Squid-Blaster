#include "Fish.h"
#include "Assets.h"
#include "World.h"

Fish::Fish(float x, float y, bool leave)
{
	this->x = x;
	this->y = y;
	this->isRemoved = false;
	this->frame = rand() % 2;
	this->velocity = Vector2f(0, -55);
	this->bounds = FloatRect();
	this->sprite = Sprite(Assets::fishImage);
	this->sprite.setOrigin(15, 15);
	this->sprite.setPosition(this->x, this->y);
	this->leave = leave;

	this->timer = Clock();
}

void Fish::draw(RenderWindow& window)
{
	switch (this->frame)
	{
	case 0:
		this->sprite.setTextureRect(IntRect(0, 0, 30, 30));
		break;
	case 1:
		this->sprite.setTextureRect(IntRect(30, 0, 30, 30));
		break;
	};

	window.draw(this->sprite);
}

void Fish::update(float delta)
{
	this->x += (this->velocity.x * delta);
	this->y += (this->velocity.y * delta);

	this->sprite.setPosition(this->x, this->y);

	this->bounds = this->sprite.getGlobalBounds();

	if (this->y < 0)
	{
		this->velocity.y *= -1;
		this->y += 3;
		this->sprite.setRotation(180);
	}

	if (this->y > 600 && this->velocity.y > 0 && !this->leave)
	{
		this->velocity.y *= -1;
		this->y -= 3;
		this->sprite.setRotation(0);
	}

	if (this->y > 650 && this->velocity.y > 0)
		this->isRemoved = true;

	if (!this->isRemoved)
	{
		Turtle* turtle = World::getTurtle();

		if (turtle->getBounds().intersects(this->bounds))
		{
			this->isRemoved = true;
			turtle->addAmmo();
		}
	}

	if (this->timer.getElapsedTime().asMilliseconds() >= 350)
	{
		this->frame++;

		if (this->frame > 1)
			this->frame = 0;

		this->timer.restart();
	}
}

bool Fish::removed()
{
	return this->isRemoved;
}

FloatRect Fish::getBounds()
{
	return this->bounds;
}