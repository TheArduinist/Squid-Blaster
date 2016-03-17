#include "Fireball.h"
#include "Assets.h"
#include "World.h"
#include "Settings.h"

const float Fireball::to_degrees = (1.0f / (float)M_PI) * 180.0f;
const float Fireball::to_radians = (1.0f / 180.0f) * (float)M_PI;

Fireball::Fireball(float x, float y, TurtleDirection direction, bool enemy)
{
	this->x = x;
	this->y = y;
	this->isRemoved = false;
	this->frame = 0;
	this->sprite = Sprite(Assets::fireballImage, IntRect(0, 0, 10, 11));
	this->sprite.setPosition(this->x, this->y);
	this->sprite.setOrigin(5, 5);
	this->timer = Clock();
	this->isEnemy = enemy;

	this->velocity = Vector2f(0, 0);

	if (direction == LEFT)
	{
		this->velocity.x = -95;
		this->sprite.setRotation(0);
	}
	else if (direction == RIGHT)
	{
		this->velocity.x = 95;
		this->sprite.setRotation(180);
	}

	if (direction == UP)
	{
		this->velocity.y = -95;
		this->sprite.setRotation(90);
	}
	else if (direction == DOWN)
	{
		this->velocity.y = 95;
		this->sprite.setRotation(270);
	}
}

Fireball::Fireball(float x, float y, const Vector2f& turtlePos, bool enemy)
{
	this->x = x;
	this->y = y;
	this->isRemoved = false;
	this->frame = 0;
	this->sprite = Sprite(Assets::fireballImage, IntRect(0, 0, 10, 11));
	this->sprite.setPosition(this->x, this->y);
	this->sprite.setOrigin(5, 5);
	this->timer = Clock();
	this->isEnemy = enemy;

	this->velocity = Vector2f(0, 0);

	float dx = this->x - turtlePos.x;
	float dy = this->y - turtlePos.y;

	float rot = atan2(dy, dx) * to_degrees;

	this->sprite.setRotation(rot);

	this->velocity.x = -95 * cos(rot * to_radians);
	this->velocity.y = -95 * sin(rot * to_radians);
}

void Fireball::draw(RenderWindow& window)
{
	switch (this->frame)
	{
	case 0:
		this->sprite.setTextureRect(IntRect(0, 0, 10, 11));
		break;
	case 1:
		this->sprite.setTextureRect(IntRect(10, 0, 10, 11));
		break;
	};

	window.draw(this->sprite);
}

void Fireball::update(float delta)
{
	this->x += (this->velocity.x * delta);
	this->y += (this->velocity.y * delta);

	this->sprite.setPosition(this->x, this->y);

	if (this->x < 0 || this->x > 600 || this->y < 0 || this->y > 600)
	{
		this->isRemoved = true;
	}

	if (!this->isRemoved)
	{
		vector<Wave*> waves = World::getWaves();

		vector<Squid*> squids = vector<Squid*>();

		for (unsigned int i = 0; i < waves.size(); ++i)
		{
			vector<Squid*> s = waves[i]->getSquids();
			for (unsigned int j = 0; j < s.size(); ++j)
			{
				Squid* squid = s[j];
				squids.push_back(squid);
			}
		}

		for (unsigned int i = 0; i < squids.size(); ++i)
		{
			Squid* s = squids[i];
			if (s->getBounds().intersects(this->getBounds()))
			{
				if (!s->removed() && !s->isInvincible() && !this->isRemoved && !this->isEnemy)
				{
					s->hit();
					this->isRemoved = true;
					break;
				}
			}
		}

		if (this->isEnemy)
		{
			if (World::getTurtle()->getBounds().intersects(this->getBounds()))
			{
				if (!World::getTurtle()->removed() && !World::getTurtle()->isInvincible() && !this->isRemoved)
				{
					if (this->getBounds().intersects(World::getTurtle()->getBounds()) && !World::getTurtle()->isInvincible())
					{
						if (!Settings::muted)
							Assets::hurt.play();

						World::removeLife();
						World::getTurtle()->hit();
					}

					this->isRemoved = true;
				}
			}
		}
	}

	if (this->timer.getElapsedTime().asMilliseconds() >= 150)
	{
		this->timer.restart();
		this->frame++;

		if (this->frame >= 2)
			this->frame = 0;
	}
}

bool Fireball::removed()
{
	return this->isRemoved;
}

FloatRect Fireball::getBounds()
{
	return this->sprite.getGlobalBounds();
}

void Fireball::setEnemy(bool enemy)
{
	this->isEnemy = enemy;
}