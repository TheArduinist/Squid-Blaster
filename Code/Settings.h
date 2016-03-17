#pragma once
#include <fstream>
#include "Data.h"

using namespace std;

class Settings sealed
{
public:
	static void load();
	static void save();
	static bool muted;
	static unsigned long highscore;
	static unsigned long long bestTime;
};