#include "Turtle.h"
#include "Assets.h"
#include "World.h"
#include "Settings.h"
#include "BigFireball.h"

Turtle::Turtle(float x, float y)
{
	this->x = x;
	this->y = y;
	this->frame = 0;
	this->isMoving = false;
	this->isRemoved = false;
	this->justPressedSpace = false;
	this->direction = DOWN;
	this->sprite = Sprite(Assets::turtleImage, IntRect(150, 0, 75, 75));
	this->sprite.setPosition(this->x, this->y);
	this->sprite.setOrigin(38, 38);
	this->sprite.setRotation(180);
	this->bounds = FloatRect();
	this->ammo = 10;
	this->invincible = false;
	this->hasPower = false;

	this->velocity = Vector2f(80, 0);

	this->timer = Clock();
	this->hurtTimer = Clock();
	this->powerTimer = Clock();
}

void Turtle::draw(RenderWindow& window)
{
	float x = 578, y = 25;
	for (int i = 0; i < this->ammo; ++i)
	{
		Sprite s = Sprite(Assets::fireballIconImage);
		s.setPosition(x, y);
		window.draw(s);
		x -= 26;
	}

	if (this->invincible)
	{
		this->sprite.setColor(Color(255, 255, 255, 200));
	}
	else
	{
		this->sprite.setColor(Color::White);
	}

	if (this->isMoving)
	{
		switch (this->frame)
		{
		case 0:
			this->sprite.setTextureRect(IntRect(0, 0, 75, 75));
			break;
		case 1:
			this->sprite.setTextureRect(IntRect(75, 0, 75, 75));
			break;
		}
	}
	else
	{
		this->sprite.setTextureRect(IntRect(150, 0, 75, 75));
	}

	window.draw(this->sprite);
}

void Turtle::update(float delta)
{
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		this->direction = LEFT;
		this->sprite.setRotation(270);
		this->isMoving = true;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		this->direction = UP;
		this->sprite.setRotation(0);
		this->isMoving = true;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		this->direction = RIGHT;
		this->sprite.setRotation(90);
		this->isMoving = true;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		this->direction = DOWN;
		this->sprite.setRotation(180);
		this->isMoving = true;
	}
	else
	{
		this->isMoving = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::Space) && !this->justPressedSpace)
	{
		this->justPressedSpace = true;
		this->shoot();
	}

	if (!Keyboard::isKeyPressed(Keyboard::Space) && this->justPressedSpace)
	{
		this->justPressedSpace = false;
	}

	if (this->invincible && this->hurtTimer.getElapsedTime().asSeconds() >= 3)
	{
		this->invincible = false;
	}

	if (this->hasPower && this->powerTimer.getElapsedTime().asSeconds() >= 5)
	{
		this->hasPower = false;
		Assets::timer.stop();
		Assets::currentMusic->play();
	}

	if (this->isMoving)
	{
		switch (this->direction)
		{
		case LEFT:
			this->x -= (this->velocity.x * delta);
			break;
		case UP:
			this->y -= (this->velocity.x * delta);
			break;
		case RIGHT:
			this->x += (this->velocity.x * delta);
			break;
		case DOWN:
			this->y += (this->velocity.x * delta);
			break;
		}
	}

	switch (this->direction)
	{
	case UP:
		this->bounds = FloatRect(this->sprite.getPosition().x - 21, this->sprite.getPosition().y - 31, 40, 52);
		break;
	case DOWN:
		this->bounds = FloatRect(this->sprite.getPosition().x - 19, this->sprite.getPosition().y - 21, 40, 52);
		break;
	case LEFT:
		this->bounds = FloatRect(this->sprite.getPosition().x - 31, this->sprite.getPosition().y - 19, 52, 40);
		break;
	case RIGHT:
		this->bounds = FloatRect(this->sprite.getPosition().x - 21, this->sprite.getPosition().y - 21, 52, 40);
	};

	if (this->x < 0)
		this->x = 600;

	if (this->x > 600)
		this->x = 0;

	if (this->y < 0)
		this->y = 600;

	if (this->y > 600)
		this->y = 0;

	this->sprite.setPosition(this->x, this->y);
	this->pos.x = this->x;
	this->pos.y = this->y;

	if (this->timer.getElapsedTime().asMilliseconds() >= 200)
	{
		this->timer.restart();
		this->frame++;

		if (this->frame >= 2)
			this->frame = 0;
	}
}

void Turtle::shoot()
{
	float x, y;

	if (this->ammo > 0)
	{
		switch (this->direction)
		{
		case LEFT:
			x = this->x - 38;
			y = this->y;
			break;
		case UP:
			x = this->x;
			y = this->y - 38;
			break;
		case RIGHT:
			x = this->x + 38;
			y = this->y;
			break;
		case DOWN:
			x = this->x;
			y = this->y + 38;
			break;
		};

		if (!this->hasPower)
		{
			World::addFireball(new Fireball(x, y, this->direction));

			if (!Settings::muted)
				Assets::fireballShoot.play();
		}
		else
		{
			World::addFireball(new BigFireball(x, y, this->direction));

			if (!Settings::muted)
			{
				Assets::loudShoot.play();
			}
		}

		this->ammo--;
	}
}

bool Turtle::removed()
{
	return isRemoved;
}

FloatRect Turtle::getBounds()
{
	return this->bounds;
}

void Turtle::addAmmo()
{
	if (!Settings::muted)
		Assets::extraAmmo.play();

	if (this->ammo < 10)
	{
		this->ammo++;
	}
	else
	{
		World::addToScore(5);
	}
}

bool Turtle::isInvincible()
{
	return this->invincible;
}

void Turtle::hit()
{
	this->hurtTimer.restart();
	this->invincible = true;
}

void Turtle::powerUp()
{
	this->powerTimer.restart();
	this->hasPower = true;

	if (!Settings::muted)
	{
		Assets::currentMusic->pause();
		Assets::timer.play();
	}
}

bool Turtle::power()
{
	return this->hasPower;
}

const Vector2f& Turtle::getPos() const
{
	return this->pos;
}