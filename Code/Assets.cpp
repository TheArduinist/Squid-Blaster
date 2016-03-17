#include "Assets.h"
#include "Settings.h"

Texture Assets::backgroundImage;
Texture Assets::fireballImage;
Texture Assets::heartImage;
Texture Assets::squidImage;
Texture Assets::turtleImage;
Texture Assets::fishImage;
Texture Assets::fireballIconImage;
Texture Assets::bigFireballImage;
Texture Assets::bigFishImage;
Texture Assets::giantSquidImage;

SoundBuffer Assets::hurtB;
SoundBuffer Assets::fireballShootB;
SoundBuffer Assets::selectB;	
SoundBuffer Assets::explosionB;
SoundBuffer Assets::extraAmmoB;
SoundBuffer Assets::timerB;
SoundBuffer Assets::loudShootB;
SoundBuffer Assets::hurtSquidB;
SoundBuffer Assets::giantSquidDieB;

Sound Assets::hurt;
Sound Assets::fireballShoot;
Sound Assets::select;	
Sound Assets::explosion;
Sound Assets::extraAmmo;
Sound Assets::timer;
Sound Assets::loudShoot;
Sound Assets::hurtSquid;
Sound Assets::giantSquidDie;

Music Assets::Reformat;
Music Assets::Video_Dungeon_Boss;
Music* Assets::currentMusic;

Font Assets::rosesAreFF0000;

void Assets::load()
{
	fireballImage = Texture();
	if (!fireballImage.loadFromFile("Art\\fireball.png"))
		exit(1);

	squidImage = Texture();
	if (!squidImage.loadFromFile("Art\\squid.png"))
		exit(1);

	turtleImage = Texture();
	if (!turtleImage.loadFromFile("Art\\turtle.png"))
		exit(1);

	heartImage = Texture();
	if (!heartImage.loadFromFile("Art\\heart.png"))
		exit(1);

	backgroundImage = Texture();
	if (!backgroundImage.loadFromFile("Art\\background.png"))
		exit(1);

	fishImage = Texture();
	if (!fishImage.loadFromFile("Art\\fish.png"))
		exit(1);

	fireballIconImage = Texture();
	if (!fireballIconImage.loadFromFile("Art\\fireball icon.png"))
		exit(1);

	bigFireballImage = Texture();
	if (!bigFireballImage.loadFromFile("Art\\big fireball.png"))
		exit(1);

	bigFishImage = Texture();
	if (!bigFishImage.loadFromFile("Art\\big fish.png"))
		exit(1);

	giantSquidImage = Texture();
	if (!giantSquidImage.loadFromFile("Art\\giant squid.png"))
		exit(1);

	hurtB = SoundBuffer();
	if (!hurtB.loadFromFile("Sounds\\hurt.wav"))
		exit(1);

	hurt.setBuffer(hurtB);
	hurt.setVolume(70);

	fireballShootB = SoundBuffer();
	if (!fireballShootB.loadFromFile("Sounds\\fireball shoot.wav"))
		exit(1);

	fireballShoot.setBuffer(fireballShootB);
	fireballShoot.setVolume(70);

	loudShootB = SoundBuffer();
	if (!loudShootB.loadFromFile("Sounds\\loud shoot.wav"))
		exit(1);

	loudShoot.setBuffer(loudShootB);
	loudShoot.setVolume(100);

	selectB = SoundBuffer();
	if (!selectB.loadFromFile("Sounds\\select.wav"))
		exit(1);

	select.setBuffer(selectB);
	select.setVolume(40);

	explosionB = SoundBuffer();
	if (!explosionB.loadFromFile("Sounds\\explosion.wav"))
		exit(1);

	explosion.setBuffer(explosionB);
	explosion.setVolume(70);

	extraAmmoB = SoundBuffer();
	if (!extraAmmoB.loadFromFile("Sounds\\extra ammo.wav"))
		exit(1);

	extraAmmo.setBuffer(extraAmmoB);
	extraAmmo.setVolume(70);

	timerB = SoundBuffer();
	if (!timerB.loadFromFile("Sounds\\timer.wav"))
		exit(1);

	timer.setBuffer(timerB);
	timer.setLoop(true);
	timer.setVolume(45);

	hurtSquidB = SoundBuffer();
	if (!hurtSquidB.loadFromFile("Sounds\\hurt squid.wav"))
		exit(1);

	hurtSquid.setBuffer(hurtSquidB);

	giantSquidDieB = SoundBuffer();
	if (!giantSquidDieB.loadFromFile("Sounds\\giant squid die.wav"))
		exit(1);

	giantSquidDie.setBuffer(giantSquidDieB);

	rosesAreFF0000 = Font();
	if (!rosesAreFF0000.loadFromFile("Fonts\\RosesareFF0000.ttf"))
		exit(1);

	if (!Reformat.openFromFile("Sounds\\Reformat.ogg"))
		exit(1);

	Reformat.setLoop(true);

	if (!Settings::muted)
		Reformat.setVolume(30);
	else
		Reformat.setVolume(0);

	if (!Video_Dungeon_Boss.openFromFile("Sounds\\Video_Dungeon_Boss.ogg"))
		exit(1);

	Video_Dungeon_Boss.setLoop(true);

	if (!Settings::muted)
		Video_Dungeon_Boss.setVolume(100);
	else
		Video_Dungeon_Boss.setVolume(0);

	currentMusic = &Reformat;
	Reformat.play();
}
