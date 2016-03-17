#pragma once
#include "Entity.h"
#include <SFML\Graphics.hpp>

class Fish : public Entity
{
public:
	Fish() {};
	Fish(float x, float y, bool leave);
	virtual ~Fish() {};
	void draw(RenderWindow& window) override;
	virtual void update(float delta) override;
	bool removed() override;
	FloatRect getBounds() override;
protected:
	bool leave;
};