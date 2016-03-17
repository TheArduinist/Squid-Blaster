#include "World.h"
#include "Assets.h"

vector<Wave*> World::waves = vector<Wave*>();
Turtle World::turtle = Turtle(300, 300);
vector<Fireball*> World::fireballs;
unsigned long World::points;
unsigned short World::lives;
bool World::lost;

void World::reset()
{
	waves = vector<Wave*>();
	turtle = Turtle(300, 300);
	fireballs = vector<Fireball*>();
	points = 0;
	lives = 3;
	lost = false;
}

void World::draw(RenderWindow& window)
{
	turtle.draw(window);
	
	for (unsigned int i = 0; i < waves.size(); ++i)
	{
		waves[i]->draw(window);
	}

	for (unsigned int i = 0; i < fireballs.size(); ++i)
	{
		fireballs[i]->draw(window);
	}
}

void World::update(float delta)
{
	if (!lost)
	{
		for (unsigned int i = 0; i < fireballs.size(); ++i)
		{
			if (fireballs[i]->removed())
			{
				fireballs.erase(fireballs.begin() + i);
			}
		}
			
		fireballs.shrink_to_fit();

		for (unsigned int i = 0; i < fireballs.size(); ++i)
		{
			fireballs[i]->update(delta);
		}

		for (unsigned int i = 0; i < waves.size(); ++i)
		{
			if (waves[i]->defeated())
			{
				waves.erase(waves.begin() + i);
			}
		}

		waves.shrink_to_fit();

		for (unsigned int i = 0; i < waves.size(); ++i)
		{
			waves[i]->update(delta);
		}

		turtle.update(delta);
	}
}

void World::addFireball(Fireball* fireball)
{
	fireballs.push_back(fireball);
}

void World::setTurtle(Turtle& turtle)
{
	World::turtle = turtle;
}

void World::addWaves(Wave* wave)
{
	waves.push_back(wave);
}

vector<Wave*> World::getWaves()
{
	return waves;
}

unsigned long World::getScore()
{
	return points;
}

void World::addToScore(unsigned long points)
{
	World::points += points;
}

unsigned short World::getLives()
{
	return lives;
}

void World::removeLife()
{
	lives -= 1;

	if (lives <= 0)
		lose();
}

void World::lose()
{
	lost = true;
}

Turtle* World::getTurtle()
{
	return &turtle;
}