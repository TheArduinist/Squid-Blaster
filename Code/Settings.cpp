#include "Settings.h"

bool Settings::muted;
unsigned long Settings::highscore;
unsigned long long Settings::bestTime;

void Settings::load()
{
	ifstream file = ifstream("data." + version + ".dat", ifstream::in);

	file >> muted;
	file >> highscore;
	file >> bestTime;

	file.close();
}

void Settings::save()
{
	ofstream file = ofstream("data." + version + ".dat", ofstream::out | ofstream::trunc);

	file << muted;
	file << '\n';
	file << highscore;
	file << '\n';
	file << bestTime;

	file.close();
}