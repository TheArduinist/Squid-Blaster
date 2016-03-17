#include "Wave.h"
#include "BigFish.h"
#include "GiantSquid.h"
#include <stdlib.h>
#include <math.h>

Wave::Wave(float time)
{
	int numSquids = 1, numFish = 0;
	int time2 = static_cast<int>(time);
	this->squids = vector<Squid*>();
	this->fish = vector<Fish*>();
	float x = 0, y = 600, emptySpace = 0;
	this->isDefeated = false;
	bool filled = false;

	switch (rand() % 13)
	{
	case 0:
		x = 0;
		break;
	case 1:
		x = 50;
		break;
	case 2:
		x = 100;
		break;
	case 3:
		x = 150;
		break;
	case 4:
		x = 200;
		break;
	case 5:
		x = 250;
		break;
	case 6:
		x = 300;
		break;
	case 7:
		x = 350;
		break;
	case 8:
		x = 400;
		break;
	case 9:
		x = 450;
		break;
	case 10:
		x = 500;
		break;
	case 11:
		x = 550;
		break;
	case 12:
		x = 600;
		break;
	};

	switch (rand() % 13)
		{
		case 0:
			emptySpace = 600;
			break;
		case 1:
			emptySpace = 550;
			break;
		case 2:
			emptySpace = 500;
			break;
		case 3:
			emptySpace = 450;
			break;
		case 4:
			emptySpace = 400;
			break;
		case 5:
			emptySpace = 350;
			break;
		case 6:
			emptySpace = 300;
			break;
		case 7:
			emptySpace = 250;
			break;
		case 8:
			emptySpace = 200;
			break;
		case 9:
			emptySpace = 150;
			break;
		case 10:
			emptySpace = 100;
			break;
		case 11:
			emptySpace = 50;
			break;
		case 12:
			emptySpace = 0;
			break;
		};

	if (time2 >= 6)
	{
		numSquids = (rand() % (time2 / 6));

		if (numSquids < 5 * (time2 / 8))
			numSquids = 5 * (time2 / 8);
	}
	else
	{
		numSquids = 2;
	}

	numFish = (rand() % 10) + 1;

	if (numFish < 5)
		numFish = 5;

	for (int i = 0; i < numSquids; ++i)
	{
		if (x >= 650)
		{
			y += 10;
			x = 0;
		}

		if (x == emptySpace)
		{
			if (!filled)
			{
				int fillers = static_cast<int>(floor(time / 60.0f));
				for (int j = 0; j < fillers; ++j)
					this->squids.push_back(new Squid(x, y + (j * 10)));

				filled = true;
			}

			x += 50;
		}

		if (x >= 650)
		{
			y += 10;
			x = 0;
		}

		this->squids.push_back(new Squid(x, y));

		x += 50;
	}

	y = 600;

	for (int i = 0; i < numFish; ++i)
	{

	switch (rand() % 13)
	{
	case 0:
		x = 0;
		break;
	case 1:
		x = 50;
		break;
	case 2:
		x = 100;
		break;
	case 3:
		x = 150;
		break;
	case 4:
		x = 200;
		break;
	case 5:
		x = 250;
		break;
	case 6:
		x = 300;
		break;
	case 7:
		x = 350;
		break;
	case 8:
		x = 400;
		break;
	case 9:
		x = 450;
		break;
	case 10:
		x = 500;
		break;
	case 11:
		x = 550;
		break;
	case 12:
		x = 600;
		break;
	};
		y = static_cast<float>((rand() % 15) + 600);

		this->fish.push_back(new Fish(x, y, true));
	}

	int randNum = rand() % 8;
	if ((randNum == 0 || randNum == 7 || randNum == 4) && time2 >= 180)
	{
		switch (rand() % 13)
		{
		case 0:
			x = 0;
			break;
		case 1:
			x = 50;
			break;
		case 2:
			x = 100;
			break;
		case 3:
			x = 150;
			break;
		case 4:
			x = 200;
			break;
		case 5:
			x = 250;
			break;
		case 6:
			x = 300;
			break;
		case 7:
			x = 350;
			break;
		case 8:
			x = 400;
			break;
		case 9:
			x = 450;
			break;
		case 10:
			x = 500;
			break;
		case 11:
			x = 550;
			break;
		case 12:
			x = 600;
			break;
		};

		y = 615;

		this->fish.push_back(new BigFish(x, y, true));
	}
}

Wave::Wave()
{
	this->squids = vector<Squid*>();
	this->fish = vector<Fish*>();
	this->isDefeated = true;
}

void Wave::draw(RenderWindow& window)
{
	for (unsigned int i = 0; i < this->squids.size(); ++i)
	{
		this->squids[i]->draw(window);
	}

	for (unsigned int i = 0; i < this->fish.size(); ++i)
	{
		this->fish[i]->draw(window);
	}
}

void Wave::update(float delta)
{
	for (unsigned int i = 0; i < this->squids.size(); ++i)
	{
		if (this->squids[i]->removed())
		{
			this->squids.erase(this->squids.begin() + i);
		}
	}

	this->squids.shrink_to_fit();

	for (unsigned int i = 0; i < this->squids.size(); ++i)
	{
		this->squids[i]->update(delta);
	}

	for (unsigned int i = 0; i < this->fish.size(); ++i)
	{
		if (this->fish[i]->removed())
		{
			this->fish.erase(this->fish.begin() + i);
		}
	}

	this->fish.shrink_to_fit();

	if (this->squids.size() <= 0 && this->fish.size() <= 0)
		this->isDefeated = true;

	for (unsigned int i = 0; i < this->fish.size(); ++i)
	{
		this->fish[i]->update(delta);
	}
}

vector<Squid*> Wave::getSquids()
{
	return squids;
}

bool Wave::defeated()
{
	return this->isDefeated;
}