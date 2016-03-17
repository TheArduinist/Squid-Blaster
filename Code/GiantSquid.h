#pragma once
#include "Squid.h"
#include <SFML\Graphics.hpp>

class GiantSquid sealed : public Squid
{
public:
	GiantSquid(float x, float y);
	~GiantSquid() {};
	void draw(RenderWindow& window) override;
	void update(float delta) override;
	void hit() override;
	void kill() override;
private:
	int lives;
	float stateTime;
};