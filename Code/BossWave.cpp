#include "BossWave.h"
#include "GiantSquid.h"
#include "Fish.h"
#include "BigFish.h"
#include "Debug.h"

BossListener* BossWave::listener = nullptr;

BossWave::BossWave()
{
	this->squids = vector<Squid*>();
	this->fish = vector<Fish*>();
	this->stateTime = 0;
	this->canMakeBigFish = true;
	this->isDefeated = true;
}

BossWave::BossWave(int numBosses)
{
	this->squids = vector<Squid*>();
	this->fish = vector<Fish*>();
	this->stateTime = 0;
	this->canMakeBigFish = true;
	this->isDefeated = false;
	
	float x = 300, y = 650;

	for (int i = 0; i < numBosses; ++i)
	{
		this->squids.push_back(new GiantSquid(x, y));
		x += 100;

		if (x >= 600)
		{
			x = 0;
		}
	}

	this->fish.push_back(new Fish(static_cast<float>(rand() % 600), 650, false));
}

void BossWave::update(float delta)
{
	this->stateTime += delta;

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
			if (typeid(*this->fish[i]) == typeid(Fish))
			{
				this->fish.push_back(new Fish(static_cast<float>(rand() % 600), 650, false));
			}
			else if (typeid(*this->fish[i]) == typeid(BigFish))
			{
				this->canMakeBigFish = true;
			}

			this->fish.erase(this->fish.begin() + i);
		}
	}

	this->fish.shrink_to_fit();

	if (this->squids.size() <= 0)
	{
		this->isDefeated = true;

		if (BossWave::listener != nullptr)
			BossWave::listener->onDefeated();
	}

	if (stateTime >= 15 && this->canMakeBigFish)
	{
		stateTime = 0;
		if (rand() % 7 == 0)
		{
			this->fish.push_back(new BigFish(static_cast<float>(rand() % 600), 650, false));
			this->canMakeBigFish = false;
		}
	}

	for (unsigned int i = 0; i < this->fish.size(); ++i)
	{
		this->fish[i]->update(delta);
	}
}

void BossWave::setListener(BossListener* listener)
{
	BossWave::listener = listener;
}