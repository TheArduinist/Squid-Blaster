#pragma once
#include "Wave.h"
#include <SFML\Graphics.hpp>

class BossListener abstract
{
public:
	virtual void onDefeated() {}
};

class BossWave sealed : public Wave
{
public:
	BossWave();
	BossWave(int numBosses);
	~BossWave() {};
	void update(float delta) override;

	static void setListener(BossListener* listener);

private:
	float stateTime;
	bool canMakeBigFish;
	static BossListener* listener;
};