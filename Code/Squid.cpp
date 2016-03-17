#include "Squid.h"
#include "Assets.h"
#include "World.h"
#include "Settings.h"

Squid::Squid(float x, float y)
{
	this->x = x;
	this->y = y;
	this->isRemoved = false;
	this->sprite = Sprite(Assets::squidImage, IntRect(0, 0, 50, 50));
	this->sprite.setPosition(this->x, this->y);
	this->sprite.setOrigin(25, 25);
	this->frame = 0;
	this->neverHitTurtle = true;
	this->invincible = false;
	this->bounds = FloatRect();

	this->velocity = Vector2f(0, -40);

	this->timer = Clock();
	this->hurtTimer = Clock();
}

void Squid::draw(RenderWindow& window)
{
	switch (this->frame)
	{
	case 0:
		this->sprite.setTextureRect(IntRect(0, 0, 50, 50));
		break;
	case 1:
		this->sprite.setTextureRect(IntRect(50, 0, 50, 50));
		break;
	case 2:
		this->sprite.setTextureRect(IntRect(100, 0, 50, 50));
		break;
	};

	window.draw(this->sprite);
}

void Squid::update(float delta)
{
	this->x += (this->velocity.x * delta);
	this->y += (this->velocity.y * delta);

	if (this->y < 0)
	{
		this->y = 1;
		this->velocity.y *= -4;
	}

	if (this->y > 650 && this->velocity.y > 0)
		this->isRemoved = true;

	if (!this->isRemoved)
	{
		if (this->getBounds().intersects(World::getTurtle()->getBounds()) && !World::getTurtle()->isInvincible())
		{
			if (this->hurtTimer.getElapsedTime().asSeconds() >= 3 || this->neverHitTurtle)
			{
				if (!Settings::muted)
					Assets::hurt.play();

				this->neverHitTurtle = false;
				this->hurtTimer.restart();
				World::removeLife();
				World::getTurtle()->hit();
			}
		}

		if (this->hurtTimer.getElapsedTime().asSeconds() >= 5 || this->neverHitTurtle)
		{
			this->invincible = false;
			this->sprite.setColor(Color::White);
		}

		if (this->hurtTimer.getElapsedTime().asSeconds() < 5 && !this->neverHitTurtle)
		{
			this->invincible = true;
			this->sprite.setColor(Color(200, 0, 0, 150));
		}
	}

	if (this->timer.getElapsedTime().asMilliseconds() >= 400)
	{
		this->timer.restart();
		this->frame++;

		if (this->frame >= 3)
			this->frame = 0;
	}

	switch (frame)
	{
	case 0:
		this->bounds = FloatRect(this->sprite.getPosition().x - 14, this->sprite.getPosition().y - 22, 28, 43);
		break;
	case 1:
		this->bounds = FloatRect(this->sprite.getPosition().x - 17, this->sprite.getPosition().y - 22, 34, 31);
		break;
	case 2:
		this->bounds = FloatRect(this->sprite.getPosition().x - 18, this->sprite.getPosition().y - 22, 36, 33);
		break;
	};

	this->sprite.setPosition(this->x, this->y);
}

bool Squid::removed()
{
	return isRemoved;
}

FloatRect Squid::getBounds()
{
	return this->bounds;
}

void Squid::kill()
{
	this->isRemoved = true;
	World::addToScore(10);

	if (!Settings::muted)
		Assets::explosion.play();
}

bool Squid::isInvincible()
{
	return this->invincible;
}

void Squid::hit()
{
	this->kill();
}