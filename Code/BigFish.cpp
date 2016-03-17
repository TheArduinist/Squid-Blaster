#include "BigFish.h"
#include "Assets.h"
#include "Settings.h"
#include "Turtle.h"
#include "World.h"

BigFish::BigFish(float x, float y, bool leave)
{
	this->x = x;
	this->y = y;
	this->isRemoved = false;
	this->frame = rand() % 2;
	this->velocity = Vector2f(0, -50);
	this->bounds = FloatRect();
	this->sprite = Sprite(Assets::bigFishImage);
	this->sprite.setOrigin(30, 30);
	this->sprite.setPosition(this->x, this->y);
	this->justTouched = false;
	this->leave = leave;

	this->timer = Clock();
	this->touchTimer = Clock();
}

void BigFish::draw(RenderWindow& window)
{
	switch (this->frame)
	{
	case 0:
		this->sprite.setTextureRect(IntRect(0, 0, 60, 60));
		break;
	case 1:
		this->sprite.setTextureRect(IntRect(60, 0, 60, 60));
		break;
	};

	window.draw(this->sprite);
}

void BigFish::update(float delta)
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

	if (this->y > 650)
		this->isRemoved = true;

	if (!this->isRemoved)
	{
		Turtle* turtle = World::getTurtle();

		if (turtle->getBounds().intersects(this->bounds) && !this->justTouched)
		{
			this->justTouched = true;
			this->touchTimer.restart();
		}

		if (!turtle->getBounds().intersects(this->bounds) && this->justTouched)
		{
			this->justTouched = false;
		}

		if (turtle->getBounds().intersects(this->bounds) && this->touchTimer.getElapsedTime().asSeconds() >= 3 && !turtle->power())
		{
			turtle->powerUp();
			this->isRemoved = true;
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