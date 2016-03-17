#pragma once
#include "Entity.h"
#include <SFML\Graphics.hpp>

using namespace sf;

class Squid : public Entity
{
public:
	Squid() {};
	Squid(float x, float y);
	virtual ~Squid() {};
	virtual void draw(RenderWindow& window) override;
	virtual void update(float delta) override;
	bool removed() override;
	FloatRect getBounds() override;
	virtual void kill();
	bool isInvincible();
	virtual void hit();
protected:
	Clock hurtTimer;
	bool neverHitTurtle;
	bool invincible;
};