#pragma once
#include <SFML\Graphics.hpp>
#include "Squid.h"
#include "Fish.h"

using namespace std;
using namespace sf;

class Wave
{
public:
	Wave();
	Wave(float time);
	virtual ~Wave() {this->squids.clear(); this->fish.clear();};
	vector<Squid*> getSquids();
	virtual void update(float delta);
	void draw(RenderWindow& window);
	bool defeated();
protected:
	vector<Squid*> squids;
	vector<Fish*> fish;
	bool isDefeated;
};