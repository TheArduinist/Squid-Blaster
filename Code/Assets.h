#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

using namespace sf;

class Assets sealed
{
public:
	static void load();
	static Texture fireballImage;
	static Texture squidImage;
	static Texture turtleImage;
	static Texture heartImage;
	static Texture backgroundImage;
	static Texture fishImage;
	static Texture fireballIconImage;
	static Texture bigFireballImage;
	static Texture bigFishImage;
	static Texture giantSquidImage;

	static Sound hurt;
	static Sound fireballShoot;
	static Sound select;
	static Sound explosion;
	static Sound extraAmmo;
	static Sound timer;
	static Sound loudShoot;
	static Sound hurtSquid;
	static Sound giantSquidDie;

	static Music Reformat;
	static Music Video_Dungeon_Boss;
	static Music* currentMusic;

	static Font rosesAreFF0000;

private:
	static SoundBuffer hurtB;
	static SoundBuffer fireballShootB;
	static SoundBuffer selectB;
	static SoundBuffer explosionB;
	static SoundBuffer extraAmmoB;
	static SoundBuffer timerB;
	static SoundBuffer loudShootB;
	static SoundBuffer hurtSquidB;
	static SoundBuffer giantSquidDieB;
};