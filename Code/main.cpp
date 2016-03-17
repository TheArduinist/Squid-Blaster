#include <SFML\Graphics.hpp>
#include "World.h"
#include "Wave.h"
#include "Fireball.h"
#include "Squid.h"
#include "Turtle.h"
#include "Assets.h"
#include "Settings.h"
#include "BossWave.h"

using namespace sf;
using namespace std;

const long bossInterval = 300;
long nextBoss = bossInterval;
long curTime = 0;

class MyListener sealed : public BossListener
{
public:
	virtual void onDefeated() override
	{
		nextBoss = curTime;
		nextBoss += bossInterval;
	}
};

int main()
{
	Settings::load();
	Assets::load();

	srand(static_cast<unsigned int>(time(nullptr)));

	RenderWindow window(VideoMode(600, 600), "Squid Blaster " + version, Style::Close | Style::Titlebar);
	window.setMouseCursorVisible(false);
	Clock clock = Clock();
	Clock gameTime = Clock();
	float delta = 0;
	Sprite background(Assets::backgroundImage);
	background.setPosition(0, 0);
	Sprite heart1 = Sprite(Assets::heartImage);
	heart1.setPosition(578, 0);
	Sprite heart2 = Sprite(Assets::heartImage);
	heart2.setPosition(552, 0);
	Sprite heart3 = Sprite(Assets::heartImage);
	heart3.setPosition(526, 0);
	bool madeWave = false;
	bool gotHighscore = false, gotBestTime = false, gotLastTime = false;
	float bestTimeSeconds = 0;
	bool justPressedR = false, justPressedM = false;
	Time lastTime = Time();
	BossWave* currentBossWave = new BossWave();
	Wave* currentWave = new Wave();
	int numBosses = 1;
	bool shouldMakeBoss = false;
	MyListener listener;

	BossWave::setListener(&listener);

	Color textColor = Color(0, 220, 0);

	Text points = Text("Points: ", Assets::rosesAreFF0000, 15);
	points.setPosition(5, 5);
	points.setColor(textColor);

	Text time = Text("Time: ", Assets::rosesAreFF0000, 15);
	time.setPosition(5, 35);
	time.setColor(textColor);

	Text gameOver = Text("GAME OVER", Assets::rosesAreFF0000, 40);
	gameOver.setPosition(170, 150);
	gameOver.setColor(textColor);

	Text credits = Text("\t\t\t\t\tCredits:\n\n \t\t\t\t\tMusic:\n \"Reformat\" Kevin MacLeod (incompetech.com)\n Licensed under Creative Commons: By Attribution 3.0\n http://creativecommons.org/licenses/by/3.0/\n\n \"Video Dungeon Boss\" Kevin MacLeod (incompetech.com)\n Licensed under Creative Commons: By Attribution 3.0\n http://creativecommons.org/licenses/by/3.0/\n\n \t\t\t\tEverything Else:\n Aleksandr Spackman", Assets::rosesAreFF0000, 15);
	credits.setPosition(30, 330);
	credits.setColor(textColor);

	Text highScore = Text("YOU GOT A HIGHSCORE!", Assets::rosesAreFF0000, 40);
	highScore.setPosition(20, 210);
	highScore.setColor(textColor);

	Text bestTimeAlert = Text("NEW BEST TIME!", Assets::rosesAreFF0000, 40);
	bestTimeAlert.setPosition(100, 270);
	bestTimeAlert.setColor(textColor);

	Text lastHighscore = Text("Highscore: ", Assets::rosesAreFF0000, 15);
	lastHighscore.setPosition(5, 20);
	lastHighscore.setColor(textColor);
	lastHighscore.setString("Highscore: " + std::to_string(static_cast<unsigned long long>(Settings::highscore)));
	
	Text bestTime = Text("Best Time: ", Assets::rosesAreFF0000, 15);
	bestTime.setPosition(5, 50);
	bestTime.setColor(textColor);

	Text debug = Text("Debug: ", Assets::rosesAreFF0000, 15);
	debug.setPosition(5, 65);
	debug.setColor(textColor);

	unsigned long long minutes = Settings::bestTime / 60, seconds = Settings::bestTime % 60;

	string secondsS = "00";

	if (seconds < 10)
	{
		secondsS = "0" + std::to_string(seconds);
	}
	else
	{
		secondsS = std::to_string(seconds);
	}

	bestTime.setString("Best Time: " + std::to_string(minutes) + ":" + secondsS);

	Image icon = Image();
	icon.loadFromFile("Art\\icon.png");
	window.setIcon(64, 64, icon.getPixelsPtr());

	World::reset();

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				if (gotHighscore || (!gotHighscore && World::getScore() > Settings::highscore))
					Settings::highscore = World::getScore();

				if (gotBestTime)
					Settings::bestTime = static_cast<unsigned long long>(lastTime.asSeconds());

				if (!gotBestTime && gameTime.getElapsedTime().asSeconds() > Settings::bestTime)
					Settings::bestTime = static_cast<unsigned long long>(gameTime.getElapsedTime().asSeconds());

				Settings::save();
				window.close();
			}
		}

		curTime = static_cast<long>(gameTime.getElapsedTime().asSeconds());

		if (Keyboard::isKeyPressed(Keyboard::R) && !justPressedR)
		{
			currentWave = new Wave();
			currentBossWave = new BossWave();
			numBosses = 1;

			if (World::getTurtle()->power())
			{
				Assets::timer.stop();
			}

			if (!Settings::muted)
			{
				Assets::currentMusic = &Assets::Reformat;
				Assets::currentMusic->play();
				Assets::select.play();
			}

			if (!gotLastTime)
			{
				lastTime = gameTime.restart();
				gotLastTime = true;
			}

			if (gotHighscore || World::getScore() > Settings::highscore)
			{
				Settings::highscore = World::getScore();
				Settings::save();
				gotHighscore = false;
			}

			if (gotBestTime || lastTime.asSeconds() > Settings::bestTime)
			{
				Settings::bestTime = static_cast<unsigned long long>(lastTime.asSeconds());
				Settings::save();
				gotBestTime = false;
			}

			lastHighscore.setString("Highscore: " + std::to_string(static_cast<unsigned long long>(Settings::highscore)));

			unsigned long long minutes = Settings::bestTime / 60, seconds = Settings::bestTime % 60;

			string secondsS = "00";

			if (seconds < 10)
			{
				secondsS = "0" + std::to_string(seconds);
			}
			else
			{
				secondsS = std::to_string(seconds);
			}

			bestTime.setString("Best Time: " + std::to_string(minutes) + ":" + secondsS);

			nextBoss = bossInterval;
			justPressedR = true;
			gotLastTime = false;
			World::reset();
			gameTime.restart();
			clock.restart();
			continue;
		}

		if (Keyboard::isKeyPressed(Keyboard::M) && !justPressedM)
		{
			Settings::muted = !Settings::muted;

			if (Settings::muted)
			{
				Assets::Reformat.setVolume(0);
				Assets::timer.setVolume(0);
				Assets::Video_Dungeon_Boss.setVolume(0);
			}
			else
			{
				Assets::Reformat.setVolume(30);
				Assets::timer.setVolume(45);
				Assets::Video_Dungeon_Boss.setVolume(100);
			}

			justPressedM = true;
		}

		if (!Keyboard::isKeyPressed(Keyboard::R) && justPressedR)
		{
			justPressedR = false;
		}

		if (!Keyboard::isKeyPressed(Keyboard::M) && justPressedM)
		{
			justPressedM = false;
		}

		if (!World::lost)
		{
			if (gameTime.getElapsedTime().asSeconds() > 1)
			{
				if (static_cast<int>(gameTime.getElapsedTime().asSeconds()) >= nextBoss && !madeWave)
				{
					shouldMakeBoss = true;
				}

				if (shouldMakeBoss && !madeWave && currentBossWave->defeated() && currentWave->defeated())
				{
					shouldMakeBoss = false;
					madeWave = true;
					Assets::currentMusic->pause();
					Assets::currentMusic = &Assets::Video_Dungeon_Boss;
					Assets::currentMusic->play();
					currentBossWave = new BossWave(numBosses);
					numBosses++;
					World::addWaves(currentBossWave);
				}

				if (!madeWave && currentBossWave->defeated() && currentWave->defeated())
				{
					madeWave = true;
					currentWave = new Wave(gameTime.getElapsedTime().asSeconds());
					World::addWaves(currentWave);
				}

				if (madeWave && (currentWave->defeated() && currentBossWave->defeated()))
				{
					madeWave = false;

					if (Assets::Video_Dungeon_Boss.getStatus() == SoundSource::Playing || Assets::Video_Dungeon_Boss.getStatus() == SoundSource::Paused)
					{
						Assets::Video_Dungeon_Boss.stop();
						Assets::currentMusic = &Assets::Reformat;

						if (!World::getTurtle()->power())
							Assets::currentMusic->play();
					}
				}
			}

			debug.setString("Debug: " + to_string((long long)nextBoss));
	
			int minutes = static_cast<int>(gameTime.getElapsedTime().asSeconds()) / 60;
			int seconds = static_cast<int>(gameTime.getElapsedTime().asSeconds()) % 60;

			string minutesS = "00";
			if (seconds < 10)
				minutesS = "0" + std::to_string(static_cast<unsigned long long>(seconds));
			else
				minutesS = std::to_string(static_cast<unsigned long long>(seconds));

			string s = std::to_string(static_cast<unsigned long long>(minutes)) + ":" + minutesS;

			points.setString("Points: " + std::to_string(static_cast<unsigned long long>(World::getScore())));
			time.setString("Time: " + s);

			delta = clock.restart().asSeconds();

			World::update(delta);

			window.clear(Color::Black);

			window.draw(background);
	
			switch (World::getLives())
			{
			case 1:
				window.draw(heart1);
				break;
			case 2:
				window.draw(heart1);
				window.draw(heart2);
				break;
			case 3:
				window.draw(heart1);
				window.draw(heart2);
				window.draw(heart3);
				break;
			};

			window.draw(points);
			window.draw(time);
			window.draw(lastHighscore);
			window.draw(bestTime);

			#if _DEBUG

			window.draw(debug);

			#endif

			World::draw(window);

			window.display();
		}
		else
		{
			Assets::timer.stop();

			if (Assets::Video_Dungeon_Boss.getStatus() == SoundSource::Playing && SoundSource::Paused)
			{
				Assets::Video_Dungeon_Boss.stop();
				Assets::currentMusic = &Assets::Reformat;
				Assets::currentMusic->play();
			}

			if (!gotLastTime)
			{
				lastTime = gameTime.restart();
				gotLastTime = true;
			}

			gameTime.restart();
			window.clear(Color::Black);
			window.draw(background);

			window.draw(gameOver);
			window.draw(credits);

			if (World::getScore() > Settings::highscore)
			{
				gotHighscore = true;
				window.draw(highScore);
			}

			if (lastTime.asSeconds() > Settings::bestTime)
			{
				gotBestTime = true;
				window.draw(bestTimeAlert);
			}

			window.display();
		}
	}

	delete currentBossWave;
	currentBossWave = nullptr;
	delete currentWave;
	currentWave = nullptr;

	return 0;
}