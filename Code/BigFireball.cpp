#include "BigFireball.h"
#include "Assets.h"
#include "World.h"
#include "Settings.h"
#include "GiantSquid.h"
#include <typeinfo>

BigFireball::BigFireball(float x, float y, TurtleDirection direction, bool enemy)
{
	this->x = x;
	this->y = y;
	this->isRemoved = false;
	this->frame = 0;
	this->sprite = Sprite(Assets::bigFireballImage, IntRect(0, 0, 112, 124));
	this->sprite.setPosition(this->x, this->y);
	this->sprite.setOrigin(56, 62);
	this->timer = Clock();
	this->isEnemy = enemy;

	this->velocity = Vector2f(0, 0);

	if (direction == LEFT)
	{
		this->velocity.x = -75;
		this->sprite.setRotation(0);
	}
	else if (direction == RIGHT)
	{
		this->velocity.x = 75;
		this->sprite.setRotation(180);
	}

	if (direction == UP)
	{
		this->velocity.y = -75;
		this->sprite.setRotation(90);
	}
	else if (direction == DOWN)
	{
		this->velocity.y = 75;
		this->sprite.setRotation(270);
	}
}

void BigFireball::draw(RenderWindow& window)
{
	switch (this->frame)
	{
	case 0:
		this->sprite.setTextureRect(IntRect(0, 0, 112, 124));
		break;
	case 1:
		this->sprite.setTextureRect(IntRect(112, 0, 112, 124));
		break;
	};

	window.draw(this->sprite);
}

void BigFireball::update(float delta)
{
	this->x += (this->velocity.x * delta);
	this->y += (this->velocity.y * delta);

	this->sprite.setPosition(this->x, this->y);

	if (this->x < -50 || this->x > 650 || this->y < -50 || this->y > 650)
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
				if (!s->removed() && !this->isRemoved && !this->isEnemy)
				{
					s->hit();
					if (typeid(*s) == typeid(GiantSquid))
					{
						s->kill();
						this->isRemoved = true;
					}
					break;
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