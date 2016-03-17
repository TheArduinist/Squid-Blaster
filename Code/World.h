#pragma once
#include <SFML\Graphics.hpp>
#include "Turtle.h"
#include "Wave.h"
#include "Fireball.h"

using namespace sf;
using namespace std;

class World sealed
{
public:
	static void reset();
	static void lose();
	static unsigned long getScore();
	static void addToScore(unsigned long points);
	static unsigned short getLives();
	static void removeLife();
	static void draw(RenderWindow& window);
	static void update(float delta);
	static void addWaves(Wave* wave);
	static void addFireball(Fireball* fireball);
	static void setTurtle(Turtle& turtle);
	static vector<Wave*> getWaves();
	static Turtle* getTurtle();
	static bool lost;
private:
	static vector<Wave*> waves;
	static vector<Fireball*> fireballs;
	static Turtle turtle;
	static unsigned long points;
	static unsigned short lives;
};