#include "GiantSquid.h"
#include "Assets.h"
#include "Settings.h"
#include "World.h"
#include "Turtle.h"

GiantSquid::GiantSquid(float x, float y)
{
	this->x = x;
	this->y = y;
	this->isRemoved = false;
	this->sprite = Sprite(Assets::giantSquidImage, IntRect(0, 0, 250, 250));
	this->sprite.setPosition(this->x, this->y);
	this->sprite.setOrigin(125, 125);
	this->frame = 0;
	this->neverHitTurtle = true;
	this->invincible = false;
	this->bounds = FloatRect();
	this->lives = 10;
	this->stateTime = 0;

	this->velocity = Vector2f(-30, -30);

	this->timer = Clock();
	this->hurtTimer = Clock();
}

void GiantSquid::draw(RenderWindow& window)
{
	switch (this->frame)
	{
	case 0:
		this->sprite.setTextureRect(IntRect(0, 0, 250, 250));
		break;
	case 1:
		this->sprite.setTextureRect(IntRect(250, 0, 250, 250));
		break;
	case 2:
		this->sprite.setTextureRect(IntRect(500, 0, 250, 250));
		break;
	};

	window.draw(this->sprite);
}

void GiantSquid::update(float delta)
{
	this->stateTime += delta;

	this->x += (this->velocity.x * delta);
	this->y += (this->velocity.y * delta);

	if (this->y < 0)
	{
		this->y  = 1;
		this->velocity.y *= -1;
	}

	if (this->y > 600 && this->velocity.y > 0)
	{
		this->y = 599;
		this->velocity.y *= -1;
	}

	if (this->x > 600)
	{
		this->x = 599;
		this->velocity.x *= -1;
	}

	if (this->x < 0)
	{
		this->x = 1;
		this->velocity.x *= -1;
	}

	if (!this->isRemoved)
	{
		if (this->getBounds().intersects(World::getTurtle()->getBounds()) && !World::getTurtle()->isInvincible())
		{
			if (!Settings::muted)
				Assets::hurt.play();

			this->neverHitTurtle = false;
			this->hurtTimer.restart();
			World::removeLife();
			World::getTurtle()->hit();
		}

		if (this->hurtTimer.getElapsedTime().asSeconds() >= 10 || this->neverHitTurtle || !this->invincible)
		{
			this->invincible = false;
			this->sprite.setColor(Color::White);
		}

		if (this->hurtTimer.getElapsedTime().asSeconds() < 10 && !this->neverHitTurtle || this->invincible)
		{
			this->invincible = true;
			this->sprite.setColor(Color(200, 0, 0, 150));
		}

		if (this->stateTime >= 5)
		{
			this->stateTime = 0;
			World::addFireball(new Fireball(this->x, this->y - 50, World::getTurtle()->getPos(), true));
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
		this->bounds = FloatRect(this->sprite.getPosition().x - 70, this->sprite.getPosition().y - 110, 140, 215);
		break;
	case 1:
		this->bounds = FloatRect(this->sprite.getPosition().x - 85, this->sprite.getPosition().y - 110, 170, 155);
		break;
	case 2:
		this->bounds = FloatRect(this->sprite.getPosition().x - 90, this->sprite.getPosition().y - 110, 180, 165);
		break;
	};

	this->sprite.setPosition(this->x, this->y);
}

void GiantSquid::hit()
{
	this->lives--;

	if (!Settings::muted)
		Assets::hurtSquid.play();

	if (this->lives <= 0)
	{
		this->kill();
	}
}

void GiantSquid::kill()
{
	this->isRemoved = true;
	World::addToScore(1000);

	if (!Settings::muted)
		Assets::giantSquidDie.play();
}